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
	typedef ISocket::Handle					Handle;
	typedef IEventHandler::HandlerQueue		HandlerQueue;

	virtual ~IReactor(void) {};

	virtual void  			registerHandler(const Handle& aHandle, IEventHandler* aHandler) = 0;
	virtual void			registerQueueOfHandlers(HandlerQueue& aHandlers) = 0;
	virtual IEventHandler*	unregisterHandler(const Handle& aHandle) = 0;
	virtual void  			handleEvents(long long aTimeout_ms) = 0;
};

#endif	/* __IREACTOR_HPP__ */
