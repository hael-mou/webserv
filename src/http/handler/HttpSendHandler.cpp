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
{
	mTerminated = false;
	mClient = aClient;
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
# include <sys/socket.h>

IEventHandler::IEventHandlerQueue http::SendHandler::handleEvent(void)
{
	std::string response = "HTTP/1.1 200 OK\r\nContent-length: 13\r\n\r\n Hello World !";

	::send(mClient->getSocket(), response.c_str(), response.size(), 0);

	mTerminated = true;

	return (IEventHandlerQueue());
}

//===[ isTerminated: return Handler Status ]====================================
bool http::SendHandler::isTerminated(void) const
{
	return (mTerminated);
}