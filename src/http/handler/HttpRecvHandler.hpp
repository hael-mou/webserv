/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpRecvHandler header file ]                                       #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-09                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef __HTTPRECVHANDLER_HPP__
# define __HTTPRECVHANDLER_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"

# include "IEventHandler.hpp"
# include "IClient.hpp"
# include "IServer.hpp"
# include "IRequest.hpp"

# include "HttpFactory.hpp"
# include "HttpCluster.hpp"

# define EMPTY ""

/*******************************************************************************
    * class : RecvHandler :
*******************************************************************************/
namespace http
{
    class RecvHandler : public IEventHandler
    {
    public:
        typedef std::vector<mem::shared_ptr<http::IServer> >    ServerVector;

        RecvHandler(IClient::SharedPtr aClient, const ServerVector& aServers);
        virtual ~RecvHandler(void);
        
        const Handle&           getHandle(void) const;
        IMultiplexer::Mode      getMode(void) const;
        IEventHandlerQueue      handleEvent(void);
        bool                    isTerminated(void) const;
    
    private:
        bool                    mTerminated;
        IClient::SharedPtr      mClient;
        IRequest::sharedPtr     mRequest;
        std::string             mReceivedData;
        ServerVector            mServers;

        const IServer&          _getMatchedServer(void) const;
    };
};

#endif /* __HTTPRECVHANDLER_HPP__ */