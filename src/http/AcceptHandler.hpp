/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ AcceptHandler header file ]                                          #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-06-06                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __HTTPACCEPTHANDLER_HPP__
# define   __HTTPACCEPTHANDLER_HPP__

/*******************************************************************************
	* Includes :
*******************************************************************************/
# include "IEventHandler.hpp"
# include <sys/socket.h>

/*******************************************************************************
	* Class AcceptHandler :
*******************************************************************************/
namespace http {
class AcceptHandler : public IEventHandler
{
public:
	AcceptHandler(const ISocket::Handle& aHandle);
	// virtual	~AcceptHandler(void);

	EventHandlerQueue			 handleEvent(void);
	const ISocket::Handle&		 getHandle(void) const;
	const IMultiplexer::Mode&	 getMode(void) const;
	bool						 isTerminated(void) const;

private:
	const ISocket::Handle		 mHandle;
};
}
#endif /* __HTTPACCEPTHANDLER_HPP__ */