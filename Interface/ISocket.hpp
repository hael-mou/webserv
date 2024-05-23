/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ ISocket Interface ]                                                #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-18                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __ISOCKET_HPP__
#define    __ISOCKET_HPP__

/*******************************************************************************
	* Includes :
*******************************************************************************/
# include <string>

/******************************************************************************
	*  ISocket Interface :
*******************************************************************************/
class ISocket
{
public:
	typedef int				Handle;
	typedef std::string		Host;
	typedef std::string		Port;

	virtual ~ISocket(void) {};

	virtual const Handle&	getHandle(void) const = 0;
	virtual const Host&		getHost(void) const = 0;
	virtual const Port&		getPort(void) const = 0;
};

#endif	/* __ISOCKET_HPP__ */