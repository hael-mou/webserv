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

/*********************************************************************************
    * Construction :
*******************************************************************************/

//===[ Constructor: Client ]================================================
http::Client::Client(Handle aSocket, const sockaddr_in& aAddr,
                     socklen_t aAddrLen)
{
    mSocket = aSocket;
    mInfo += _AddrtoString(aAddr.sin_addr.s_addr, aAddrLen);
    mInfo += ":" + std::to_string(ntohs(aAddr.sin_port));
}

//===[ Destructor: Client ]================================================
http::Client::~Client(void)
{
    close(mSocket);
}

/*******************************************************************************
    * Public Methods :
*******************************************************************************/

//===[ Method: getSocket ]====================================================
Handle http::Client::getSocket(void) const
{
    return (mSocket);
}

//===[ Method: getInfo ]======================================================
const std::string& http::Client::getInfo(void) const
{
    return (mInfo);
}

/*******************************************************************************
    * Private Methods :
*******************************************************************************/

//===[ Method: _AddrtoString ]===============================================
std::string
http::Client::_AddrtoString(const in_addr_t& addr, const socklen_t& addrLen)
{
    utls::shared_ptr<char> buffer = new char[addrLen];
    unsigned char *ip = (unsigned char *)&addr;
    snprintf(buffer.get(), sizeof(buffer), "%d.%d.%d.%d",
             ip[0], ip[1], ip[2], ip[3]);
    return (buffer.get());
}
