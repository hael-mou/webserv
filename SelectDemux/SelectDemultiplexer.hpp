/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ SelectDemultiplexer header file ]                                    #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-16                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __DEMULTIPLEXER_HPP__
#define    __DEMULTIPLEXER_HPP__

//===[ Includes ]===============================================================
# include "IDemultiplexer.hpp"
# include <sys/select.h>
# include <stddef.h>
# include <vector>

//===[ Demultiplexer class ]====================================================
class SelectDemultiplexer : public IDemultiplexer
{
public:
	SelectDemultiplexer(void);
	virtual ~SelectDemultiplexer();

	std::vector<Socketfd>	select(long timeout = 20);
	void 					registerSocket(Socketfd fd, Mode mode);
	void					clearSets(void);

private:
	int		maxFd;
	fd_set	readSet;
	fd_set	writeSet;
};

#endif /* __DEMULTIPLEXER_HPP__ */
