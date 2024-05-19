/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ IDemultiplexer Interface ]                                          #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-18                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __HANDLER_HPP__
#define   __HANDLER_HPP__

//==[ Includes : ]==============================================================
# include "Types.hpp"
# include "IDemultiplexer.hpp"
# include "SelectDemultiplexer.hpp"
# include "IEventHandler.hpp"
# include "IReactor.hpp"
# include "Reactor.hpp"


//==[ Handler class : ]=========================================================
class Handler : public IEventHandler
{
	public:
		Handler(Socketfd fd);
		virtual HandlerState	handleEvent(void);
		virtual Mode			getMode(void);

	private:
		Socketfd	server_fd;
		Mode		mode;
};

#endif	/* __HANDLER_HPP__ */