/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpGetHandler implementation file ]                                #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-17                                                   #
#                                                                              #
** ************************************************************************* **/

# include "HttpGetHandler.hpp"

/*******************************************************************************
    * Construction :
*******************************************************************************/

//===[ Constructor: GetdHandler ]===============================================
http::GetHandler::GetHandler(IClient::SharedPtr aClient,
                             IRequest::SharedPtr aRequest)
    : mClient(aClient),
      mRequest(aRequest)
{
}

//===[ Destructor: GetdHandler ]================================================
http::GetHandler::~GetHandler(void) {}

/*******************************************************************************
    * Public Methods :
*******************************************************************************/
//===[ handleEvent: return IEventHandlerQueue ]=================================
IEventHandler::IEventHandlerQueue http::GetHandler::handleEvent(void)
{
    IEventHandlerQueue eventHandlers;
    try {
        if (mRequest->getMatchedLocation().isAllowedMethod("GET") == false)
            throw http::METHOD_NOT_ALLOWED;

        mRessourcePath = _getRequestedPath();
        if (mRessourcePath.empty() || access(mRessourcePath.c_str(), F_OK))
        {
            (errno == ENOENT) ? throw http::NOT_FOUND : throw http::FORBIDDEN ;
        }
        eventHandlers.push(
            http::Factory::createSendHandler(mClient, _generateResponse())
        );
    }
    catch (const http::StatusCode& errorCode) {
        IResponse::SharedPtr
        response = mRequest->getMatchedServer().getErrorPage(errorCode);
        eventHandlers.push(http::Factory::createSendHandler(mClient, response));
    }
    return (eventHandlers);
}

//===[ getMode: return Handler Mode ]============================================
IMultiplexer::Mode http::GetHandler::getMode(void) const
{
    return (IMultiplexer::Write);
}
//===[ getHandle: return Handler Handle ]========================================
const Handle& http::GetHandler::getHandle(void) const
{
    return (mClient->getSocket());
}

// ==[ isTerminated: return Handler Status ]====================================
bool http::GetHandler::isTerminated(void) const
{
    return (false);
}

/** *************************************************************************** 
 * Private Methods :
*******************************************************************************/

std::string http::GetHandler::_getRequestedPath(void)
{
    const_string&   locationUri   = mRequest->getMatchedLocation().getUri();
    const_string&   locationRoot  = mRequest->getMatchedLocation().getRoot();
    std::string     requestUri    = mRequest->getUriPath();
    std::size_t locationUriLength = locationUri.length();

    bool        hasTrailingSlash  = locationUri[locationUriLength - 1] == '/';
    std::string path;
    if (hasTrailingSlash) {
        path = requestUri.substr(locationUriLength);
    }
    else {
        path = requestUri.substr(locationUriLength);
        path.erase(0, path.find_first_of('/') + 1);
    }
    return (locationRoot + path);
}

//===[ Method: _resourceHandler ]===============================================
http::AResponse::SharedPtr    http::GetHandler::_generateResponse(void)
{
    if (httptools::isDirectory(mRessourcePath)) {
        return (_handleDirectory());
    }
    return (_handleFile(mRessourcePath));
}

// ===[ Method : Handle File ]===================================================
http::AResponse::SharedPtr  http::GetHandler::_handleFile(const_string& aPath)
{
    std::string  extension = httptools::getExtension(aPath);
    const_string contentType = mRequest->getMatchedServer()
                                       .getMimeType(extension);

    http::FileResponse* response = new http::FileResponse();
    response->setSendTimeout(mRequest->getMatchedServer().getSendTimeout());
    response->setVersion(mRequest->getVersion());
    response->setHeader("Content-Type", contentType);
    response->setHeader("Connection", mRequest->getHeader("Connection"));
    response->setStatusCode(http::OK);
    response->setPath(aPath);
    return (response);
}

// === [ Method: _handleDirectory ] ==============================================
http::AResponse::SharedPtr  http::GetHandler::_handleDirectory(void)
{
    http::RawResponse* response = new http::RawResponse();
    if (mRessourcePath[mRessourcePath.length() - 1] != '/')
    {
        response->setStatusCode(http::MOVED_PERMANENTLY);
        response->setSendTimeout(mRequest->getMatchedServer().getSendTimeout());
        response->setVersion(mRequest->getVersion());
        response->setHeader("Location", mRequest->getUriPath() + "/");
        response->setHeader("Connection", mRequest->getHeader("Connection"));
        return (response);
    }

    StringVector indexFiles = mRequest->getMatchedLocation().getIndexFiles();
    if (!indexFiles.empty())
    {
        for (size_t index = 0; index < indexFiles.size(); index++)
        {
            if (!access((mRessourcePath + indexFiles[index]).c_str(), F_OK))
                 return(_handleFile(mRessourcePath + indexFiles[index])); 
        }
    }
    
    if (mRequest->getMatchedLocation().isAutoIndex())
    {
        DIR* dir = opendir(mRessourcePath.c_str());
        if (dir != NULL)
        {
            response->setStatusCode(http::OK);
            response->setSendTimeout(mRequest->getMatchedServer().getSendTimeout());
            response->setVersion(mRequest->getVersion());
            response->setBody(_autoIndex(dir));
            response->setHeader("Connection", mRequest->getHeader("Connection"));
            closedir(dir);
            return (response);
        }
    }

    throw(http::FORBIDDEN);
}

///===[ Method : _autoIndex ]====================================================
std::string http::GetHandler::_autoIndex(DIR *dir)
{
    std::string autoindex;
    std::string content;
    struct dirent *ent;

    autoindex += CUSTOM_AUTOINDEX_PAGE;
    str::replace(autoindex, "$(RESOURCE_PATH)", mRessourcePath);
    while ((ent = readdir(dir)) != NULL)
    {
        content += "<tr>";
        if (ent->d_type == DT_REG)
        {
            content += "<td><span class=\"icon file-icon\"></span><a href=\"" + std::string(ent->d_name) + "\">" + ent->d_name + "</a></td>";
        }
        else if (ent->d_type == DT_DIR)
        {
            content += "<td><span class=\"icon dir-icon\"></span><a href=\"" + std::string(ent->d_name) + "/\">" + ent->d_name + "/</a></td>";
        }
        content += "</tr>";
    }
    str::replace(autoindex, "$(CONTENT)", content);

    return autoindex;
}
