/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpServer implementation file ]                                     #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-06-02                                                   #
#                                                                              #
** ************************************************************************* **/

# include "HttpServer.hpp"

/*******************************************************************************
    * Construction :
*******************************************************************************/

//===[ Constructor: Server ]===================================================
http::Server::Server(Directive::SharedPtr aServerDir)
{
    setListens(aServerDir->getTerminal("listen"));
    setServerNames(aServerDir->getTerminal("server_names"));
    setConnectionType(aServerDir->getTerminal("connection"));
    setKeepAliveTimeout(aServerDir->getTerminal("keepalive_timeout"));
    setBodyBufferSize(aServerDir->getTerminal("body_buffer_size"));
    setMaxBodySize(aServerDir->getTerminal("max_body_size"));
    setDefaultMimeType(aServerDir->getTerminal("default_type"));
    setMimeTypes(aServerDir->getTerminal("meme_type"));
    setServerRoot(aServerDir->getTerminal("root"));
    mErrorPages = ErrorPages(aServerDir->getTerminal("error_page"), mRoot);
    setLocations(aServerDir, aServerDir->getNonTerminal("location"));
}

//===[ Destructor: Server ]====================================================
http::Server::~Server(void) {}

/*******************************************************************************
    * Public Methods :
*******************************************************************************/

//===[ Method: check if server name match ]=====================================
bool  http::Server::isMatch(const_string& aHostName) const
{
    for (size_t index = 0; index < mServerName.size(); ++index)
    {
        if (aHostName == mServerName[index])
            return (true);
    }
    return (false);
}

//===[ Method: check if keep alive ]============================================
bool    http::Server::isKeepAlive(void) const
{
    return (mKeepAlive);
}

/*** * Setters :
*******************************************************************************/

//===[ Method: set listens ]====================================================
void    http::Server::setListens(const StringVector& aListens)
{
    for (size_t index = 0; index < aListens.size(); ++index)
    {
        StringPair addressPort = str::lineToPair(aListens[index], ':');
        int port =  integer::strToInt (addressPort.second);
        if (port <= 0 || port > 65535)
        {
            Logger::log("warning", "HTTP: Listen directive ignored: '"
                +  aListens[index] + "'", 2);
            continue ;
        }
        std::string address = str::strtrim(addressPort.first);
        std::string portString = str::strtrim(addressPort.second);
        mListens.push_back(address + ":" + portString);
    }
    if (mListens.size() == 0)
    {
        mListens.push_back(DEFAULT_LISTEN);
    }
}

//===[ Method: set server names ]===============================================
void    http::Server::setServerNames(const StringVector& aServerName)
{
    if (aServerName.size() == 1)
        mServerName = str::split(aServerName[0], ' ');
}

//===[ Method: set connection type ]============================================
void    http::Server::setConnectionType(const StringVector& aConnection)
{
    mKeepAlive = true;
    if (aConnection.size() == 1)
    {
        if (str::toLower(aConnection[0]) == "close")
            mKeepAlive = false;
        else {
            Logger::log("warning", "HTTP: Connection directive ignored: '"
                +  aConnection[0] + "'", 2);
        }
    }
}

//===[ Method: set keep alive timeout ]=========================================
void    http::Server::setKeepAliveTimeout(const StringVector& aTimeout)
{
    if (aTimeout.size() == 1)
    {
        if ((mKeepAliveTimeout = integer::strToInt(aTimeout[0])) > 5)
            return ;
        Logger::log("warning", "HTTP: Keepalive_timeout ignored: '"
            +  aTimeout[0] + "'", 2);
    }
    mKeepAliveTimeout = DEFAULT_TIMEOUT;
}

//===[ Method: set client body buffer size ]====================================
void http::Server::setBodyBufferSize(const StringVector& aBodyBufferSize)
{
    if (aBodyBufferSize.size() == 1)
    {
        if ((mBodyBufferSize = integer::strToInt(aBodyBufferSize[0])) > 0)
            return ;
        Logger::log("warning", "HTTP: Client body buffer size ignored: '"
            +  aBodyBufferSize[0] + "'", 2);
    }
    mBodyBufferSize = DEFAULT_BODY_BUFFER_SIZE;
}

//===[ Method: set client max body size ]=======================================
void http::Server::setMaxBodySize(const StringVector& aMaxBodySize)
{
    mMaxBodySize = 0;
    if (aMaxBodySize.size() == 1)
    {
        if ((mMaxBodySize = integer::strToInt(aMaxBodySize[0])) > 0)
            return ;
        Logger::log("warning", "HTTP: Client max body size ignored: '"
            +  aMaxBodySize[0] + "'", 2);
    }
}

//===[ Method: set Default MimeType ]===========================================
void    http::Server::setDefaultMimeType(const StringVector& aDefaultType)
{
    mMimeTypes["default"] = DEFAULT_MIME_TYPE;
    if (aDefaultType.size() == 1)
    {
        mMimeTypes["default"] = aDefaultType[0];
    }
}

//===[ Method: set Mime Types ]=================================================
void    http::Server::setMimeTypes(const StringVector& aMimeTypes)
{
    for (size_t index = 0; index < aMimeTypes.size(); ++index)
    {
        StringPair extansionType = str::lineToPair(aMimeTypes[index], ' ');
        mMimeTypes[extansionType.first] = str::strtrim(extansionType.second);
    }
}

//===[ Method: set Server Root ]================================================
void    http::Server::setServerRoot(const StringVector& aRoot)
{
    if (aRoot.size() == 1)
    {
        mRoot = aRoot[0];
        if (mRoot.back() == '/')
            mRoot.pop_back();
        return ;
    }
    mRoot = DEFAULT_SERVER_ROOT;
}

//===[ Method: set Location ]===================================================
void http::Server::setLocations(Directive::SharedPtr aServerDir,
                                Directive::DirPtrVector aLocation)
{
    for (size_t index = 0; index < aLocation.size(); ++index)
    {
        aLocation[index]->copyMatchingAttributes(aServerDir);
        try
        {
            Location* location = new Location(aLocation[index]);
            mLocations.insert(std::make_pair(location->getUri(), location));
        }
        catch(const std::exception& e)
        {
            Logger::log("warning", 
            "HTTP: unable to create location without specifying a URI.", 2);
        }
    }
}

/*** * getters :
*******************************************************************************/

//===[ Method: get listens ]====================================================
const StringVector&  http::Server::getListens(void) const
{
    return (mListens);
}

//===[ Method: get server names ]===============================================
const StringVector&  http::Server::getServerNames(void) const
{
    return (mServerName);
}

//===[ Method: get keep alive timeout ]=========================================
time_t  http::Server::getKeepAliveTimeout(void) const
{
    return (mKeepAliveTimeout);
}

//===[ Method: get client body buffer size ]====================================
unsigned long  http::Server::getBodyBufferSize(void) const
{
    return (mBodyBufferSize);
}

//===[ Method: get client max body size ]=======================================
unsigned long  http::Server::getMaxBodySize(void) const
{
    return (mMaxBodySize);
}

//===[ Method: get Mime Types ]=================================================
const std::string &http::Server::getMimeType(const_string aExtansion) const
{
    StringMap::const_iterator it = mMimeTypes.find(aExtansion);

    if (it != mMimeTypes.end())
        return (it->second);

    return (mMimeTypes.at("default"));
}

//===[ Method: get Error Pages ]================================================
const http::ErrorPages& http::Server::getErrorPages(void) const
{
    return (mErrorPages);
}

//===[ Method : Get Locations ]==================================================
const   http::Server::LocationMap& http::Server::getLocations(void) const
{
    return (mLocations);
}
