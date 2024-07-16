/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpSendHandler implementation file ]                                #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-12                                                   #
#                                                                              #
** ************************************************************************* **/

#include "HttpSendHandler.hpp"

/*******************************************************************************
	* Construction :
*******************************************************************************/

//===[ Constructor: SendHandler ]===============================================
http::SendHandler::SendHandler(IClient::SharedPtr aClient)
	: mTerminated(false),
	  mClient(aClient)
{
}

//===[ Destructor: SendHandler ]================================================
http::SendHandler::~SendHandler(void) {}

/*******************************************************************************
	* Public Methods :
*******************************************************************************/

//===[ getHandle: return Handler Handle ]========================================
const Handle& http::SendHandler::getHandle(void) const
{
	return (mClient->getSocket());
}

//===[ getMode: return Handler Mode ]============================================
IMultiplexer::Mode http::SendHandler::getMode(void) const
{
	return (IMultiplexer::Write);
}

//===[ handleEvent: return IEventHandlerQueue ]=================================

IEventHandler::IEventHandlerQueue http::SendHandler::handleEvent(void)
{
	// JUST FOR TEST
	std::string response = "HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nContent-length: 15\r\n\r\nHello client! " +  std::to_string(mClient->getSocket());

	IEventHandlerQueue eventHandlers;
	
	if  (mClient->send(response) == -1)
	{
		Logger::log("error", "HTTP: Failed to send !!", 2);
		mTerminated = true;
		return (eventHandlers);
	}
	mTerminated = true;
	return (eventHandlers);
}

//===[ isTerminated: return Handler Status ]====================================
bool http::SendHandler::isTerminated(void) const
{
	return (mTerminated);
}
