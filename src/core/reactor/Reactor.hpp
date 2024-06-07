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
	typedef std::map<Handle, IEventHandler*>	EventHandlerMap;
	typedef IMultiplexer::HandleQueue			HandleQueue;

	Reactor(IMultiplexer* aMultiplexer);
	virtual ~Reactor(void);

	void			registerEventHandler(IEventHandler* aHandler);
	void			registerEventHandler(EventHandlerQueue& aHandlers);
	IEventHandler*	unregisterEventHandler(IEventHandler* aHandler);
	void			handleEvents(long long aTimeout_ms);
	void			cleanupTerminatedHandlers(void);

private:
	IMultiplexer*		mMultiplexer;
	EventHandlerMap		mEventHandlers;
};

#endif /* __REACTOR_HPP__ */
