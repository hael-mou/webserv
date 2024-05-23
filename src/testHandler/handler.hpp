/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ WebServer Main File ]                                               #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-21                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __HANDLER_HPP__
# define   __HANDLER_HPP__

# include "IEventHandler.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

class Handler : public IEventHandler
{
public:
	typedef IEventHandler::HandlerQueue		HandlerQueue;
	typedef IEventHandler::Handle			Handle;
	typedef IEventHandler::Mode				Mode;

	Handler(int);
	virtual ~Handler(void);
	
	const Handle&	getHandle(void) const;
	const Mode&		getMode(void) const;
	HandlerQueue	handleEvent(void);

private:
	Handle		mHandle;
	Mode		mMode;
};


#endif /* __HANDLER_HPP__ */