/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpCgiHandler implementation file ]                                #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-29                                                   #
#                                                                              #
** ************************************************************************* **/

# include "HttpCgiHandler.hpp"

/*******************************************************************************
    * Construction :
*******************************************************************************/

//===[ Constructor: CgidHandler ]===============================================
http::CgiHandler::CgiHandler(IClient::SharedPtr aClient,
                             IRequest::SharedPtr aRequest)
    : mClient(aClient),
      mRequest(aRequest)
{
    // mTerminated = (mClient && mRequest) ? false : true;

    // if (mTerminated)
    //     return ;

    mOutPath = file::generateTempFileName(http::tmpDir(""));
    mOutFd   = file::createFile(mOutPath);
    if (mOutFd == -1) {
        std::string msg = "Can't create temporary file";
        throw (http::Exception(msg, http::INTERNAL_SERVER_ERROR));
    }
    mCurrentOperation = &CgiHandler::_setupCgi;
}

//===[ Destructor: CgidHandler ]================================================
http::CgiHandler::~CgiHandler(void)
{
    file::closeFile(mOutFd); 
}

/*******************************************************************************
    * Public Methods :
*******************************************************************************/

//===[ handleEvent: return IEventHandlerQueue ]=================================
IEventHandler::IEventHandlerQueue http::CgiHandler::handleEvent(void)
{
    IEventHandlerQueue eventHandlers;

    try
    {
        eventHandlers = (this->*mCurrentOperation)();
    }
    catch(http::Exception& aException)
    {
        aException.setClientInfo(mClient->getInfo());
        string msg = aException.what();
        Logger::log("error  ", "HTTP: "+ msg , 2);

        IResponse::SharedPtr errRes = mRequest->getMatchedServer()
                                      .getErrorPage(aException.getStatusCode());
        eventHandlers.push(http::Factory::createSendHandler(mClient, errRes));
    }

    return (eventHandlers);
}

//===[ CgiMode: return Handler Mode ]============================================
IMultiplexer::Mode http::CgiHandler::getMode(void) const
{
    return (IMultiplexer::Write);
}
//===[ CgiHandle: return Handler Handle ]========================================
const Handle& http::CgiHandler::getHandle(void) const
{
    return (mClient->getSocket());
}

// ==[ isTerminated: return Handler Status ]====================================
bool http::CgiHandler::isTerminated(void) const
{
    return (false);
}

/** *************************************************************************** 
    * Process Methods :
*******************************************************************************/

//===[ Method: buildCgi ]=======================================================
IEventHandler::IEventHandlerQueue http::CgiHandler::_setupCgi(void)
{
    _checkUploadPermission();
    _createCgiProcess();

    if (mCgiProcess == 0)
    {
        const char* args[2];
        std::string path = _getAbsoluteCgiPath();
        args[0] = path.c_str();
        args[1] = NULL;

        _setupCgiIo();

        int er = chdir(path.substr(0, path.find_last_of("/") + 1).c_str());
        if (er == -1) {
            std::exit(EXIT_FAILURE);
        }

        ::execve(path.c_str(), const_cast<char* const*>(args), NULL);
        std::exit(EXIT_FAILURE);
    }

    mCgiLastActiveTime = time(NULL);
    mCurrentOperation  = &CgiHandler::_waitCgiToFinish;
    return (_waitCgiToFinish());
}

//===[ Method: WaitCgiToFinish ]===============================================
IEventHandler::IEventHandlerQueue http::CgiHandler::_waitCgiToFinish(void)
{
    // timeout 
    time_t cgiTimeout  = mRequest->getMatchedServer().getCgiTimeout();
    time_t currentTime = time(NULL);

    if (currentTime - mCgiLastActiveTime >= cgiTimeout)
    {
        _cleanHandler();
        throw (http::Exception("cgi timeout", http::INTERNAL_SERVER_ERROR));
    }

    return (IEventHandlerQueue());
}


/** *************************************************************************** 
    * Private Methods :
*******************************************************************************/

//===[ Method: _CleanHandler ]==================================================
void http::CgiHandler::_cleanHandler(void)
{
    file::closeFile(mOutFd);
    file::removeFile(mOutPath);
}

//===[ Method: _checkUploadPermission ]=========================================
void http::CgiHandler::_checkUploadPermission(void)
{
    const Location&  location = mRequest->getMatchedLocation();
    const string&    upload = location.getUpload();
    const string&    contentType = mRequest->getHeader("Content-Type");
    const bool       isPostMethod = (mRequest->getMethod() == "POST");
    const bool       isMultipartForm = (contentType.find("multipart/form-data") != string::npos);
    const bool       isXUpload = (contentType == "x-upload");

    if (isPostMethod && (isMultipartForm || isXUpload) && upload.empty())
    {
        _cleanHandler();
        throw http::Exception("upload not allowed", http::FORBIDDEN);
    }
}

//===[ Method: _createCgiProcess ]==============================================
void http::CgiHandler::_createCgiProcess(void)
{
    mCgiProcess = fork();
    if (mCgiProcess == -1) {
        _cleanHandler();
        throw (http::Exception("fork failed", http::INTERNAL_SERVER_ERROR));
    }
}

//===[ Method: _setupCgiIo ]====================================================
void http::CgiHandler::_setupCgiIo()
{
    int stdoutFd = dup2(mOutFd, STDOUT_FILENO);
    if (stdoutFd == -1) {
        _cleanHandler();
        throw http::Exception("Failed to dup2 stdout", http::INTERNAL_SERVER_ERROR);
    }

    if (mRequest->hasBody()) {
        const std::string& bodyPath = mRequest->getBodyPath();
        int inputFd = open(bodyPath.c_str(), O_RDONLY);
        if (inputFd == -1) {
            _cleanHandler();
            throw http::Exception("Failed to open input file",
                                  http::INTERNAL_SERVER_ERROR);
        }
        int stdinFd = dup2(inputFd, STDIN_FILENO);
        if (stdinFd == -1) {
            _cleanHandler();
            throw http::Exception("Failed to dup2 stdin",
                                  http::INTERNAL_SERVER_ERROR);
        }
        close(inputFd);
    }
}

//===[ Method: _getAbsoluteCgiPath ]============================================
string http::CgiHandler::_getAbsoluteCgiPath(void) const
{
    const string&   locationUri   = mRequest->getMatchedLocation().getUri();
    const string&   locationRoot  = mRequest->getMatchedLocation().getRoot();
    std::string     requestUri    = mRequest->getUriPath();

    return (locationRoot + http::getRelativePath(requestUri, locationUri));
}
