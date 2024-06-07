/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ IReactor Interface ]                                                #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-18                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __IREACTOR_HPP__
# define   __IREACTOR_HPP__

/*******************************************************************************
	* Includes :
*******************************************************************************/
# include "ISocket.hpp"
# include "IEventHandler.hpp"

/*******************************************************************************
	* IReactor Interface :
*******************************************************************************/
class IReactor
{
public:
	typedef ISocket::Handle						Handle;
	typedef IEventHandler::EventHandlerQueue	EventHandlerQueue;

	virtual ~IReactor(void) {};
	
	virtual void			registerEventHandler(IEventHandler* aHandler) = 0;
	virtual void			registerEventHandler(EventHandlerQueue& aHandlers) = 0;
	virtual IEventHandler*	unregisterEventHandler(IEventHandler* aHandler) = 0;
	virtual void			handleEvents(long long aTimeout_ms) = 0;
};

#endif	/* __IREACTOR_HPP__ */
