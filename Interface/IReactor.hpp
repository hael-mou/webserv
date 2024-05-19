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

//==[ Includes : ]==============================================================
# include "Types.hpp"

//==[ forward declaration : ]===================================================
class	IEventHandler;

//==[ IReactor Interface : ]====================================================
class IReactor
{
public:
	virtual ~IReactor(void){};

	virtual	void  registerHandler(Socketfd fd, IEventHandler* Handler) = 0;
	virtual	void  removeHandler(Socketfd fd) = 0;
	virtual	void  handleEvents(void) = 0;
};

#endif	/* __IREACTOR_HPP__ */
