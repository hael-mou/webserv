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
        throw (std::invalid_argument("Multiplexer is NULL"));
}

//===[ Destructor : ]=========================================================
Reactor::~Reactor(void)
{
    EventHandlerMap::iterator handlerIt = mEventHandlers.begin();
    while (handlerIt != mEventHandlers.end())
    {
        delete (handlerIt->second);
        ++handlerIt;
    }
    mEventHandlers.clear();
    delete  (mMultiplexer);
}

/*******************************************************************************
    * public Methods :
*******************************************************************************/

//===[ Method : register new event handler ]====================================
void Reactor::registerEventHandler(IEventHandler* aHandler)
{
    if (aHandler != NULL)
	{
        Handle Handle = aHandler->getHandle();
		mEventHandlers[Handle] = aHandler;
		mMultiplexer->registerHandle(Handle, aHandler->getMode());
	}
}

//===[ Method : register queue of event handlers ]==============================
void Reactor::registerEventHandler(EventHandlerQueue &aHandlers)
{
	while (aHandlers.empty() == false)
	{
		registerEventHandler(aHandlers.front());
		aHandlers.pop();
	}
}

//===[ Method : unregister event handler ]=====================================
IEventHandler* Reactor::unregisterEventHandler(IEventHandler* aHandler)
{
    if (aHandler != NULL) {
        const Handle& handle = aHandler->getHandle();
        mMultiplexer->removeHandle(handle, aHandler->getMode());
        mEventHandlers.erase(handle);
    }
    return (aHandler);
}

//===[ Method : remove all ended event handlers ]==============================
void Reactor::cleanupTerminatedHandlers(void)
{
    EventHandlerMap::iterator handlerIt = mEventHandlers.begin();
    while (handlerIt != mEventHandlers.end())
    {
        IEventHandler* handler = handlerIt->second;
        if (handler->isTerminated() == true) {
            mMultiplexer->removeHandle(handler->getHandle(),handler->getMode());
            handlerIt = mEventHandlers.erase(handlerIt);
            delete (handler);
        }
        else
            ++handlerIt;
    }
}

//===[ Method : handle events ]================================================
void Reactor::handleEvents(long long aTimeout_ms)
{
    HandleQueue readyHandles = mMultiplexer->waitEvent(aTimeout_ms);
    while (readyHandles.empty() == false)
    {
        Handle            handle = readyHandles.front();
        EventHandlerQueue newHandlers = mEventHandlers[handle]->handleEvent();
        registerEventHandler(newHandlers);
        readyHandles.pop();
    }
    cleanupTerminatedHandlers();
}
