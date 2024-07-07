/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpClient header file ]                                             #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-06                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef	  __HTTPCLIENT_HPP__
# define   __HTTPCLIENT_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "Logger.hpp"
# include "typedefs.hpp"
# include "Shared_ptr.hpp"

# include <netinet/in.h> 

/*******************************************************************************
    * Client Class :
*******************************************************************************/
namespace http
{
    class Client
    {
    public:
        typedef utls::shared_ptr<Client>    SharedPtr;

        Client(Handle aSocket, const sockaddr_in &aAddr, socklen_t aAddrLen);
        virtual ~Client(void);

        Handle                  getSocket(void) const;
        const std::string&      getInfo(void) const;

    private:
        Handle                  mSocket;
        std::string             mInfo;

        std::string _AddrtoString(const in_addr_t& addr, const socklen_t& addrLen);
    };
}

#endif /* __HTTPCLIENT_HPP__ */