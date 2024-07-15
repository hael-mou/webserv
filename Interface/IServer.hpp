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

# include "HttpErrorPage.hpp" //remove

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

        virtual bool                  isKeepAlive(void) const = 0;
		virtual bool 				  isMatch(const_string& aHost) const = 0;

		virtual const StringVector&   getListens(void) const = 0;
        virtual const StringVector&   getServerNames(void) const = 0;
        virtual time_t                getKeepAliveTimeout(void) const = 0;
        virtual unsigned long         getBodyBufferSize(void) const = 0;
        virtual unsigned long         getMaxBodySize(void) const = 0;
        virtual const std::string&    getMimeType(const_string aExtansion) const = 0;
        virtual const ErrorPages&     getErrorPages(void) const = 0;

	};
}

#endif	/* __ISERVER_HPP__ */