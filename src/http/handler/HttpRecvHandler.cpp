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
	: mTerminated(false), mClient(aClient)
{
	mServers =  http::Cluster::getServers(aClient->getSocket());
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
			mRequest->setMatchedServer(mServers);
			mRequest->display();
		// 	//mRequest->buildBody();
		// 	//eventHandlers += http::Factory::createSendHandler(mClient, mRequest);
		}
	}
	catch(const std::exception& aException)
	{
		Logger::log("error", aException.what(), 2);
		mTerminated = true;
	}
	catch(const http::IRequest::Error& aErrorCode)
    {
		Logger::log("error", std::to_string(aErrorCode), 2);
		// create error handler
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
	return (mTerminated);
}
