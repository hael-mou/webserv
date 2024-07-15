/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ IRequest Interface ]                                                 #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-18                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef	  __IREQUEST_HPP__
# define   __IREQUEST_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"

# include "IServer.hpp"

/*******************************************************************************
    * http::IRequest Interface :
*******************************************************************************/

namespace http
{
    class IRequest
    {
    public:
        typedef mem::shared_ptr<IRequest>           sharedPtr;
        typedef std::vector<IServer::SharedPtr>     ServerVector;

        enum Error
        {
            BAD_REQUEST = 400,
            PAYLOAD_TOO_LARGE = 413,
            URI_TOO_LONG = 414,
            NOT_IMPLEMENTED = 501,
            VERSION_NOT_SUPPORTED = 505
        };

        virtual ~IRequest(void) {};

        virtual void            setMatchedServer(const ServerVector& aServers) = 0;
        virtual void            setHeader(std::string& aLine) = 0;

        virtual std::string     getVersion(void) const = 0;
        virtual std::string		getMethod(void) const = 0;
        virtual std::string		getUriPath(void) const = 0;
        virtual StringMap		getUriQuery(void) const = 0;
        virtual StringMap 		getHeaders(void) const = 0;
        virtual std::string		getHeader(std::string const& key) = 0;
        virtual const IServer&  getMatchedServer(void) const = 0;
        virtual void            display(void) const = 0;
    };
}

#endif	/* __IREQUEST_HPP__ */