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

/** ************************************************************************ ***
#      * Construction :                                                        #
** ************************************************************************* **/

//===[ Constructor : ]==========================================================
Reactor::Reactor(void)
{
	demux = new SelectDemultiplexer();
}

//===[ Destructor : ]===========================================================
Reactor::~Reactor(void)
{
	while (handlers.empty() == false)
	{
		removeHandler(handlers.begin()->first);
	}
}

/** ****************************************************************************
#      * Methods :                                                             #
** ************************************************************************* **/

//===[ Register_Handler : ]=====================================================
void	Reactor::registerHandler(Socketfd handle, IEventHandler* Handler)
{
    if (Handler != NULL)
    {
        removeHandler(handle);
        handlers[handle] = Handler;
    }
}

//===[ Remove_Handler : ]========================================================
void	Reactor::removeHandler(Socketfd handle)
{
	EventMap::iterator it = handlers.find(handle);
	if (it != handlers.end())
	{
		delete (it->second);
		handlers.erase(it);
	}
}

//===[ Handle_Events : ]=========================================================
void Reactor::handleEvents(void)
{
	for (EventMap::iterator it = handlers.begin(); it != handlers.end(); ++it)
	{
		demux->registerSocket(it->first, it->second->getMode());
	}

	readyFd	readyFds = demux->select(20); // set timeout
	for (readyFd::iterator it = readyFds.begin(); it != readyFds.end();  ++it)
	{
		if (handlers[*it]->handleEvent() == 0)
			removeHandler(*it);
	}

	//timeout

	demux->clearSets();
}
