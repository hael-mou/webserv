/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpClient implementation file ]                                     #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-06                                                   #
#                                                                              #
** ************************************************************************* **/

#include "HttpClient.hpp"

/*******************************************************************************
    * Construction :
*******************************************************************************/

//===[ Constructor: Client ]====================================================
http::Client::Client(Handle aSocket, const sockaddr_in& aAddr, socklen_t aAddrLen)
    : mSocket(aSocket), mLastActivityTime(time(NULL))
{
    mInfo += str::addrtoString(aAddr.sin_addr.s_addr, aAddrLen);
    mInfo += ":" + std::to_string(ntohs(aAddr.sin_port));
}

//===[ Destructor: Client ]================================================
http::Client::~Client(void)
{
    Logger::log("notice", "HTTP: Client '" + mInfo + "' disconnected", 2);
    close(mSocket);
}

/*******************************************************************************
    * Public Methods :
*******************************************************************************/

//===[ Method: updateActivityTime ]===========================================
void http::Client::updateActivityTime(void)
{
    mLastActivityTime = time(NULL);
}

//===[ Method: getSocket ]====================================================
const Handle& http::Client::getSocket(void) const
{
    return (mSocket);
}

//===[ Method: getInfo ]======================================================
const std::string& http::Client::getInfo(void) const
{
    return (mInfo);
}

//===[ Method: getLastActivityTime ]==========================================
time_t http::Client::getLastActivityTime(void) const
{
    return (mLastActivityTime);
}

//===[ Method: recv ]=========================================================
std::string http::Client::recv(void) const
{
    char buffer[1025];
	memset(buffer, 0, 1025); 
	int bytesReaded = ::recv(mSocket, buffer, 1024, 0);
	if (bytesReaded < 0) {
		throw(std::runtime_error("recv error"));
    }
    return (std::string(buffer));
}
