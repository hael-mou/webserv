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
http::RecvHandler::RecvHandler(IClient::SharedPtr aClient,
                               const ServerVector& aServers)
    : mTerminated(false),
      mClient(aClient), 
      mServers(aServers)
{
}

//===[ Destructor: AcceptHandler ]=============================================
http::RecvHandler::~RecvHandler(void) {}

/*******************************************************************************
    * Public Methods of Interface: IEventHandler
*******************************************************************************/

//===[ Method: handle The Read Events ]========================================
IEventHandler::IEventHandlerQueue  http::RecvHandler::handleEvent(void)
{
    IEventHandlerQueue eventHandlers;

    try{
        if ((mReceivedData += mClient->recv()) == EMPTY)
        {
            return ((mTerminated = true),  eventHandlers);
        }
        mRequest = http::Factory::createRequest(mReceivedData);
        if (mRequest.get() != NULL)
        {
           // mRequest->setMatchedServer(mServers);
           // mRequst->selectMatechedServer(mServers);
            // mRequest->display();
        // 	//mRequest->buildBody();
        // 	eventHandlers.push(
            //     http::Factory::createProcessHandler(mClient, mRequest)
            // );
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
        //const IServer& server = _getMatchedServer();
        // IResponse* response = server->getErrorPage(aErrorCode);
        // eventHandlers.push(
        //     http::Factory::createSendHandler(mClient, response)
        // );
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
    
    time_t lastActivity = mClient->getLastActivityTime();
    time_t timeout      = server.getKeepAliveTimeout();
    if (time(NULL) - lastActivity >= timeout)
        return (true);

    return (mTerminated);
}

/*******************************************************************************
    * Private Methods :
*******************************************************************************/

//===[ Method: getMatchedServer ]==============================================
const http::IServer& http::RecvHandler::_getMatchedServer(void) const
{
    if (mRequest)
        return (mRequest->getMatchedServer());

    if (mServers.size() != 0)
        return (*(mServers[0]));

    throw (std::runtime_error("HttpRecvHandler: No server found"));
}
