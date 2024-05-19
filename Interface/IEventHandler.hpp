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

//==[ Includes : ]==============================================================
# include "Types.hpp"

//==[ IEventHandler Interface : ]===============================================
class IEventHandler
{
public:
	virtual ~IEventHandler(void){};

	virtual HandlerState	handleEvent(void) = 0;
	virtual Mode			getMode(void) = 0;
};

#endif /* __IEVENTHANDLER_HPP__ */