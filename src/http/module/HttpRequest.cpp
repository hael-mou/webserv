/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpRequest implementation file ]                                    #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-09                                                   #
#                                                                              #
** ************************************************************************* **/

#include "HttpRequest.hpp"

/*******************************************************************************
    * Construction :
*******************************************************************************/

//===[ Constructor: Request ]===================================================
http::Request::Request(std::string& aBuffer)
{
    std::stringstream bufferStream(aBuffer);
    std::string line;

    std::getline(bufferStream, line);
    if (!line.empty() && line[line.length() - 1] == '\r')
        line.resize(line.length() - 1);
    _setRequestLine(line);

    while (std::getline(bufferStream, line) && line != "\r" && !line.empty())
    {
        setHeader(line);
    }

    if (getHeader("host").empty())
        throw http::IRequest::BAD_REQUEST;

    aBuffer = bufferStream.str().substr(bufferStream.tellg());
}

//===[ Destructor: Request ]====================================================
http::Request::~Request(void) {}

/*******************************************************************************
    * Public Methods :
*******************************************************************************/

//===[ Method: selectMatechedRoute ]============================================
void	http::Request::selectMatechedRoute(const ServerVector& aServerList)
{
    mMatchedServer = _selectMatchedServer(aServerList);
    mMatchedLocation = _selectMatchedLocation();
}

//===[ Method: setHeader ]======================================================
void	http::Request::setHeader(std::string& aLine)
{
    if (!aLine.empty() && aLine[aLine.length() - 1] == '\r')
         aLine.resize(aLine.length() - 1);
    if ( aLine.find(':') == std::string::npos) {
        throw(http::IRequest::BAD_REQUEST);
    }
    StringPair header = str::lineToPair(aLine, ':');
    
    for (size_t index = 0; index < header.first.size(); ++index)
    {
        if (httptools::isValidHeader(header.first[index]) == false)
            throw(http::IRequest::BAD_REQUEST);
    }

    header.first = str::toLower(header.first);
    mHeaders[header.first] = header.second;
}

//===[ Method: geMethod ]======================================================
std::string http::Request::getMethod(void) const
{
    return (mMethod);
}

//===[ Method: getUri ]========================================================
std::string	http::Request::getUriPath(void) const
{
    return (mUri);
}

//====[ Method: getVersion ]===================================================
std::string http::Request::getVersion(void) const
{
    return (mVersion);
}

//====[ Method: getUriQuery ]==================================================
StringMap http::Request::getUriQuery(void) const
{
    return 	(mQuery);
}

//====[ Method: getHeaders ]===================================================
std::string http::Request::getHeader(std::string const& key)
{
    return (mHeaders[key]);
}

//====[ Method: getHeaders ]===================================================
StringMap http::Request::getHeaders() const 
{
    return (mHeaders);
}

//====[ Method: getMatchedServer ]=============================================
const http::IServer& http::Request::getMatchedServer(void) const
{
    return (*mMatchedServer);
}

//===[ Method : getMatchedLocation ]===========================================
const http::Location& http::Request::getMatchedLocation(void) const
{
    return (*mMatchedLocation);
}

//====[ Method: display ]======================================================
void http::Request::display(void) const
{
    StringMap::const_iterator it;
    StringMap query = getUriQuery();
    StringMap headers = getHeaders();

    std::cout << getMethod() << " " << getUriPath() << " "
    << getVersion() << std::endl;

    std::cout << "**********************> Query :" << std::endl;
    for (it = query.begin(); it != query.end(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    std::cout << "**********************> Headers :" << std::endl;
    for (it = headers.begin(); it != headers.end(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }
}

/*******************************************************************************
    * Private Methods :
*******************************************************************************/

//===[ Method: _setRequestLine ]================================================
void	http::Request::_setRequestLine(const std::string& aLine)
{
    StringVector parts = str::split(aLine, ' ');
    if (parts.size() != 3)
        throw(http::IRequest::BAD_REQUEST);
    mMethod = parts[0];
    if (mMethod != "GET" && mMethod != "POST" && mMethod != "DELETE")
        throw (http::IRequest::NOT_IMPLEMENTED);
    mVersion = parts[2];
    if (mVersion != "HTTP/1.1")
        throw(http::IRequest::VERSION_NOT_SUPPORTED);
    mUri = _parseUri(parts[1]);
}

//====[ Method: parseUri ]======================================================
std::string& http::Request::_parseUri(std::string &aUri)
{
    for (size_t i = 0; i < aUri.size(); ++i)
    {
        if (!httptools::isSpecialChars(aUri[i]))
            throw (http::IRequest::BAD_REQUEST);
    }
    
    httptools::httpDecoder(aUri);
    _parseQuery(aUri);
    if (aUri.size() > 2048)
        throw(http::IRequest::URI_TOO_LONG);
    return (aUri);
}

//====[ Method: parseQuery ]====================================================
void http::Request::_parseQuery(std::string& aUri)
{
    std::string query;

    size_t fragmentPosition = aUri.find('#');
    if (fragmentPosition != std::string::npos)
    {
        size_t endPosition = aUri.find('?');
        aUri.erase(fragmentPosition, endPosition - fragmentPosition);
    }

    std::stringstream ss(aUri);
    getline(ss, aUri, '?');
    while (std::getline(ss, query, '&'))
    {
        if (query.empty())
            continue;

        size_t delimiterPosition = query.find('=');
        if (delimiterPosition == std::string::npos) {
            throw(http::IRequest::BAD_REQUEST);
        }

        std::string key = query.substr(0, delimiterPosition);
        mQuery[key] = query.substr(delimiterPosition + 1);
    }
}

//====[ Method: selectMatechedServer]==========================================
http::IServer::SharedPtr  
http::Request::_selectMatchedServer(const ServerVector& aServerList)
{
    for (size_t i= 0; i < aServerList.size(); ++i)
    {
        if (aServerList[i]->isMatch(getHeader("host")))
            mMatchedServer = aServerList[i];
    }
    if (!mMatchedServer)
        mMatchedServer = aServerList[0];
    return (mMatchedServer);
}

//===[ Method: _isInnerPath ]===================================================
bool http::Request::_isInnerPath(const std::string& uri, const std::string& requestUri)
{
    std::string remaining = requestUri.substr(uri.size());
    remaining.erase(0, remaining.find_first_not_of('/'));

    size_t firstSlashPos = remaining.find('/');
    if (firstSlashPos == std::string::npos)
        return (false);
    
    if (firstSlashPos == remaining.length() - 1)
        return (false);
    
    return (true);
}

//====[ Method: setMatchedLocation ]============================================
http::Location::SharedPtr    http::Request::_selectMatchedLocation()
{
    IServer::LocationMap locations  = mMatchedServer->getLocations();
    IServer::LocationMap::const_iterator it = locations.begin();
    std::string bestLocation;

    std::string x = mUri.substr(0, mUri.find_last_of('/') + 1);

    for (; it != locations.end(); ++it)
    {
        if (x.find(it->first) == 0 && it->first.length() > bestLocation.length())
        {
            std::string select = it->first;
            if (select[select.length() - 1] == '/' && !_isInnerPath(select, x))
                bestLocation = it->first;
            else if (select[select.length() - 1] != '/' || select.length() == 1)
                bestLocation = it->first;
        }
    }
    std::cout << "bestLocation: " << bestLocation << std::endl;
    if (bestLocation.empty() == true)
        throw(http::IRequest::NOT_FOUND);
    return (locations[bestLocation]);
}

