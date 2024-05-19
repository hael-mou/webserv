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

//==[ Includes : ]==============================================================
# include "IDemultiplexer.hpp"
# include "IEventHandler.hpp"
# include "IReactor.hpp"
# include <vector>
# include <map>
# include "SelectDemultiplexer.hpp"

//==[ Reactor class : ]=========================================================
class Reactor : public IReactor
{
public:	
	Reactor(void);
	virtual	~Reactor(void);

	void	registerHandler(Socketfd fd, IEventHandler* Handler);
	void	removeHandler(Socketfd fd);
	void	handleEvents(void);

private:
	typedef std::map<Socketfd, IEventHandler*>	EventMap;
	typedef std::vector<Socketfd>				readyFd;
	
	EventMap		handlers;
	IDemultiplexer*	demux;
};

#endif /* __REACTOR_HPP__ */