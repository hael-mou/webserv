/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ IEventHandler Interface ]                                           #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-16                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __IEVENTHANDLER_HPP__
# define   __IEVENTHANDLER_HPP__

/*******************************************************************************
	* Includes :
*******************************************************************************/
# include "ISocket.hpp"
# include "IMultiplexer.hpp"

/*******************************************************************************
	* IEventHandler Interface :
*******************************************************************************/
class IEventHandler
{
public:
	typedef ISocket::Handle					Handle;
	typedef IMultiplexer::Mode				Mode;
	typedef std::queue<IEventHandler*>		HandlerQueue;
	
	virtual ~IEventHandler(void) {};
	
	virtual const Handle&	getHandle(void) const = 0;
	virtual const Mode&		getMode(void) const = 0;
	virtual HandlerQueue	handleEvent(void) = 0;
};

#endif /* __IEVENTHANDLER_HPP__ */
