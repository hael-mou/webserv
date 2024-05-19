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

#ifndef   __IDEMULTIPLEXER_HPP__
#define    __IDEMULTIPLEXER_HPP__

//==[ Includes : ]==============================================================
# include "Types.hpp"
# include <vector>
 
//===[ IDemultiplexer Interface ]===============================================
class IDemultiplexer
{
public:
	virtual ~IDemultiplexer(void){};

	virtual std::vector<Socketfd>	select(long timeout = 20) = 0;
	virtual void 					registerSocket(Socketfd fd, Mode mode) = 0;
	virtual void					clearSets(void) = 0;
};

#endif /* __IDEMULTIPLEXER_HPP__ */