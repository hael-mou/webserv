/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ IMultiplexer Interface ]                                            #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-18                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __IMULTIPLEXER_HPP__
#define    __IMULTIPLEXER_HPP__

/*******************************************************************************
	* Includes :
*******************************************************************************/
# include "ISocket.hpp"
# include <queue>

/*******************************************************************************
	* Imultiplexer Interface :
*******************************************************************************/
class IMultiplexer
{
public:
	typedef ISocket::Handle			Handle;
	typedef enum {Read, Write}		Mode;
	typedef std::queue<Handle>		HandleQueue;

	virtual ~IMultiplexer(void) {};

	virtual int			waitEvent(long long aTimeout_ms) = 0;
	virtual void		registerHandle(const Handle& aHandle,const Mode& aMode) = 0;
	virtual void		removeHandle(const Handle& aHandle, const Mode& aMode) = 0;
	virtual HandleQueue	getReadyHandles(void) const = 0;
};

#endif /* __IMULTIPLEXER_HPP__ */
