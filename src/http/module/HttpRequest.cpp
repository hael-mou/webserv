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
    std::stringstream	bufferStream(aBuffer);
	std::string			line;

    std::getline(bufferStream, line);
	if (line.back() == '\r') line.pop_back();
    _setRequestLine(line);

    while (std::getline(bufferStream, line) && (line != "\r" && !line.empty()))
	{
        setHeader(line);
    }

    if (getHeader("host").empty()) {
        throw (http::IRequest::BAD_REQUEST);
    }

    aBuffer = bufferStream.str().substr(bufferStream.tellg());
}

//===[ Destructor: Request ]====================================================
http::Request::~Request(void) {}

/*******************************************************************************
    * Public Methods :
*******************************************************************************/

//===[ Method: setMatchedServer ]==============================================
void	http::Request::setMatchedServer(const ServerVector& aServerList)
{
	for (size_t i= 0; i < aServerList.size(); ++i)
	{
		if (aServerList[i]->isMatch(getHeader("host")))
			mMatchedServer = aServerList[i];
	}
}

//===[ Method: setHeader ]======================================================
void	http::Request::setHeader(std::string& aLine)
{
	if (aLine.back() == '\r')
		aLine.pop_back();
	if ( (aLine.find(':')) == std::string::npos) {
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
