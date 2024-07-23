/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpRecvHandler implementation file ]                               #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-09                                                   #
#                                                                              #
** ************************************************************************* **/

#include "HttpRecvHandler.hpp"

/*******************************************************************************
    * Construction :
*******************************************************************************/

//===[ Constructor: AcceptHandler ]============================================
http::RecvHandler::RecvHandler(IClient::SharedPtr aClient)
    : mClient(aClient)
{
    mTerminated = (aClient.get() == NULL) ? true : false;
}

//===[ Destructor: AcceptHandler ]=============================================
http::RecvHandler::~RecvHandler(void) {}

/*******************************************************************************
    * Public Methods :
*******************************************************************************/

//===[ Method: handle The Read Events ]========================================
IEventHandler::IEventHandlerQueue  http::RecvHandler::handleEvent(void)
{
    IEventHandlerQueue eventHandlers;

    try{
        if ((mReceivedData += mClient->recv()) == EmptyString)
        {
            return ((mTerminated = true),  eventHandlers);
        }
        mRequest = http::Factory::createRequest(mReceivedData);
        if (mRequest.get() != NULL)
        {
            const ServerVector& servers = Cluster::getServers(mClient->getSocket());
            mRequest->selectMatechedRoute(servers);
            // mRequest->buildBody();
            eventHandlers.push(
                http::Factory::createProcessHandler(mClient, mRequest)
            );
        }
        mClient->updateActivityTime();
    }
    catch(const std::exception& aException)
    {
        Logger::log("error", aException.what(), 2);
        mTerminated = true;
    }
    catch(const http::IRequest::Error& aErrorCode)
    {
        IResponse::SharedPtr errRes;
        errRes = _getMatchedServer().getErrorPage(aErrorCode);
        eventHandlers.push(http::Factory::createSendHandler(mClient, errRes));
    }

    return (eventHandlers);
}

//===[ Method: return Handler Mode ]============================================
IMultiplexer::Mode	http::RecvHandler::getMode(void) const
{
    return (IMultiplexer::Read);
}

//===[ Method: return Handler Handle ]==========================================
const Handle& http::RecvHandler::getHandle(void) const
{
    return (mClient->getSocket());
}

//===[ Method: check if Handler is Terminated ]=================================

bool http::RecvHandler::isTerminated(void) const
{
    const IServer& server = _getMatchedServer();

    if (mTerminated == true)
        return (true);
    bool   isDataReceived    = !mReceivedData.empty();
    time_t lastActivity      = mClient->getLastActivityTime();
    time_t keepAliveTimeout  = server.getKeepAliveTimeout();
    time_t readTimeout       = server.getReadTimeout();
    time_t currentTime       = time(NULL);

    return (isDataReceived ? (currentTime - lastActivity >= readTimeout)
                           : (currentTime - lastActivity >= keepAliveTimeout));
}

/*******************************************************************************
    * Private Methods :
*******************************************************************************/

//===[ Method: getMatchedServer ]==============================================
const http::IServer& http::RecvHandler::_getMatchedServer(void) const
{
    const std::vector<IServer::SharedPtr>&
    servers = Cluster::getServers(mClient->getSocket());

    if (mRequest) {
        return (mRequest->getMatchedServer());
    }
    if (servers.size() != 0) {
        return (*(servers[0]));
    }
    throw (std::runtime_error("HttpRecvHandler: No server found"));
}
