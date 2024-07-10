/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpServer header file ]                                             #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-06-02                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef	  __HTTPSERVER_HPP__
# define   __HTTPSERVER_HPP__
/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"
# include "Utils.hpp"

# include "Directive.hpp"
# include "IServer.hpp"

/*******************************************************************************
    * PorotocolFactory Class :
*******************************************************************************/
namespace http
{
	class Server : public IServer
	{
    public:
        Server(Directive::SharedPtr aServerDir);
        virtual ~Server(void);

		const StringVector getListen(void) const;
		const StringVector getName(void);

    private:
	    StringVector    mListen;
	    StringVector	mServerName;

        StringVector    _processListenDirective(const StringVector& aListenDir);
        StringVector    _processHostDirective(const StringVector& aHostDir);
    };
}

#endif /* __HTTPSERVER_HPP__ */