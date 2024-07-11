/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ IServer Interface ]                                                 #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-18                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __ISERVER_HPP__
# define   __ISERVER_HPP__

/*******************************************************************************
	* Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"

/*******************************************************************************
	* http::IServer Interface :
*******************************************************************************/

namespace http
{
	class IServer
	{
	public:
		typedef mem::shared_ptr<IServer>    SharedPtr;

		virtual	~IServer(void) {};

		virtual const StringVector getListen(void) const = 0;
		virtual const StringVector getName(void) = 0;
		virtual bool isMatch(const_string& aHost) const = 0;
	};
}

#endif	/* __ISERVER_HPP__ */