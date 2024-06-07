/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ AcceptHandler header file ]                                          #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-06-06                                                   #
#                                                                              #
** ************************************************************************* **/

#include "AcceptHandler.hpp"

/*******************************************************************************
	* Construction :
*******************************************************************************/

//===[ Constructor : ]==========================================================
http::AcceptHandler::AcceptHandler(const ISocket::Handle &aHandle)
	: mHandle(aHandle)
{
}

/*******************************************************************************
	* Public Methods :
*******************************************************************************/


//===[ Method : Handle event ]=================================================
IEventHandler::EventHandlerQueue http::AcceptHandler::handleEvent(void)
{
	IEventHandler::EventHandlerQueue eventHandlers;
	while (true)
	{
		int clientSocket = ::accept(mHandle, nullptr, nullptr);
		if (clientSocket == -1)
			break;
		eventHandlers.push(new AcceptHandler(clientSocket));
	}
	return eventHandlers;
}

//===[ Method : Get handle ]===================================================
const IEventHandler::Handle& http::AcceptHandler::getHandle(void) const
{
	return (mHandle);
}

//===[ Method : Get mode ]=====================================================
const IEventHandler::Mode& http::AcceptHandler::getMode(void) const
{
	return (IMultiplexer::Read);
}

bool http::AcceptHandler::isTerminated(void) const
{
	return (false);
}
