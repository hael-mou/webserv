/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Reactor header file ]                                                #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-16                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __REACTOR_HPP__
# define   __REACTOR_HPP__

/*******************************************************************************
	* Includes :
*******************************************************************************/
# include "IReactor.hpp"
# include "IMultiplexer.hpp"
# include <map>

/*******************************************************************************
	* Class Reactor :
*******************************************************************************/
class Reactor : public IReactor
{
public:
	typedef std::map<Handle, IEventHandler*>		HandlerMap;
	typedef IMultiplexer::HandleQueue				HandleQueue;
	typedef IEventHandler::HandlerQueue				HandlerQueue;

	Reactor(IMultiplexer* aMultiplexer);
	virtual ~Reactor(void);

	void  			registerHandler(const Handle& aHandle, IEventHandler* aHandler);
	void			registerQueueOfHandlers(HandlerQueue& aHandlers);
	IEventHandler*	unregisterHandler(const Handle& aHandle);
	void  			handleEvents(long long aTimeout_ms);

private:
	HandlerMap		mHandlers;
	IMultiplexer*	mMultiplexer;
};

#endif /* __REACTOR_HPP__ */
