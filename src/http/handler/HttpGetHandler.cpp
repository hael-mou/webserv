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
http::GetHandler::GetHandler(IClient::SharedPtr aClient
                , IRequest::SharedPtr aRequest)
                : mClient(aClient), mRequest(aRequest) {}

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
        if (mRequest->getMatchedLocation().isAllowedMethod("GET") == false) {
            throw http::METHOD_NOT_ALLOWED;
        }
        mRessourcePath = _getRequestedPath();
        std::cout << "Matched path: " << mRessourcePath << std::endl;
        if (mRessourcePath.empty() || access(mRessourcePath.c_str(), F_OK)) {
            std::cout << "Enter here can't access to the path" << std::endl;
            throw http::NOT_FOUND;
        }
        IResponse::SharedPtr resourceResponse = _resourceHandler();

        // resourceResponse->display();
        eventHandlers.push(
            http::Factory::createSendHandler(mClient, resourceResponse)
        );
    }
    catch (const http::StatusCode& errorCode) {
        IResponse::SharedPtr errorResponse =
            mRequest->getMatchedServer().getErrorPage(errorCode);

        eventHandlers.push(
            http::Factory::createSendHandler(mClient, errorResponse)
        );
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
    return (mTerminated);
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
http::AResponse::SharedPtr

http::GetHandler::_resourceHandler(void)
{
    std::cout << httptools::isDirectory(mRessourcePath) << std::endl;
    if (httptools::isDirectory(mRessourcePath))
    {
        std::cout << "Is Directory" << std::endl;
        return (_handleDirectory());
    }
    std::cout << "IsFile" << std::endl;
    return (_handleFile());
}

// ===[ Method : Handle File ]===================================================
http::AResponse::SharedPtr
http::GetHandler::_handleFile(void)
{
    std::string extension = httptools::getExtension(mRessourcePath);
    const_string contentType = mRequest->getMatchedServer().getMimeType(extension);

    http::FileResponse* response = new http::FileResponse();
    response->setVersion(mRequest->getVersion());
    response->setHeader("Content-Type", contentType);
    response->setStatusCode(http::OK);
    response->setPath(mRessourcePath);
    response->setHeader("connection", mRequest->getHeader("connection")); // add to the all responses    return (response);
}

// === [ Method: _handleDirectory ] ==============================================
http::AResponse::SharedPtr
http::GetHandler::_handleDirectory(void)
{
    http::RawResponse* response = new http::RawResponse();
    if (mRessourcePath.back() != '/')
    {
        response->setStatusCode(http::MOVED_PERMANENTLY);
        response->setHeader("Location", mRequest->getUriPath() + "/");
        // response->display();
        return (response);
    }
    else
    {
        StringVector indexFiles = mRequest->getMatchedLocation().getIndexFiles();
        if (indexFiles.size() > 0)
        {
            for (StringVector::iterator it = indexFiles.begin(); it != indexFiles.end(); it++)
            {
                if (!access((mRessourcePath + *it).c_str(), F_OK))
                {
                    mRessourcePath += *it;
                    return(_handleFile()); 
                }
            }
            // throw(http::NOT_FOUND);
        }
        if (mRequest->getMatchedLocation().isAutoIndex())
        {
            DIR* dir = opendir(mRessourcePath.c_str());
            if (dir != NULL)
            {
                response->setStatusCode(http::OK);
                response->setHeader("Content-Type", "text/html");
                std::string autoIndexBody = _autoIndex(dir);
                response->setHeader("content-length", str::to_string(autoIndexBody.size()));
                response->setBody(autoIndexBody);
                // response->display();
                return (response);
            }
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

    closedir(dir);
    return autoindex;
}
