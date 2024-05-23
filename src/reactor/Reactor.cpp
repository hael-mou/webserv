/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Reactor implementation ]                                            #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-16                                                   #
#                                                                              #
** ************************************************************************* **/

#include "Reactor.hpp"

/*******************************************************************************
	* Construction :
*******************************************************************************/

//===[ Constructor : ]========================================================
Reactor::Reactor(IMultiplexer *aMultiplexer) 
	: mMultiplexer(aMultiplexer)
{
	if (aMultiplexer == NULL)
		throw std::invalid_argument("Multiplexer is NULL");
}

//===[ Destructor : ]=========================================================
Reactor::~Reactor(void)
{
	HandlerMap::iterator it = mHandlers.begin();
	while (it != mHandlers.end())
	{
		delete (it->second);
		++it;
	}
	mHandlers.clear();
	delete (mMultiplexer);
}

/*******************************************************************************
	* Methods :
*******************************************************************************/

//===[ registerHandler : ]===================================================
void Reactor::registerHandler(const Handle& aHandle, IEventHandler* aHandler)
{
	if (aHandler != NULL)
	{
		mHandlers[aHandle] = aHandler;
		mMultiplexer->registerHandle(aHandle, aHandler->getMode());
	}
}

//===[ registerQueueOfHandlers : ]===========================================
void Reactor::registerQueueOfHandlers(HandlerQueue& aHandlers)
{
	while (aHandlers.empty() == false)
	{
		IEventHandler*	handler = aHandlers.front();
		registerHandler(handler->getHandle(), handler);
		aHandlers.pop();
	}
}

//===[ unregisterHandler : ]=================================================
IEventHandler* Reactor::unregisterHandler(const Handle& aHandle)
{
	HandlerMap::iterator handlerIt = mHandlers.find(aHandle);
	if (handlerIt == mHandlers.end())
	{
		IEventHandler*	handler = handlerIt->second;
		mMultiplexer->removeHandle(aHandle, handler->getMode());
		mHandlers.erase(handlerIt);
		return (handler);
	}
	return (NULL);
}

//===[ handleEvents : ]=======================================================
void Reactor::handleEvents(long long aTimeout_ms)
{
	if ( mMultiplexer->waitEvent(aTimeout_ms) > 0 )
	{
		HandleQueue readyToHandles = mMultiplexer->getReadyHandles();
		while (readyToHandles.empty() == false)
		{
			Handle			handle = readyToHandles.front();
			HandlerQueue 	NewHandlers = mHandlers[handle]->handleEvent();
			registerQueueOfHandlers(NewHandlers);
			readyToHandles.pop();
		}
	}
	// tiemout and remove end handlers
}