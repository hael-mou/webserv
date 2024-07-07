/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ ServerCore header file ]                                             #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-28                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef __SERVERCORE_HPP__
# define __SERVERCORE_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "typedefs.hpp"
# include "Shared_ptr.hpp"

# include "SelectMultiplexer.hpp"
# include "Reactor.hpp"

# include "Directive.hpp"
# include "HttpFactory.hpp"

# include <exception>

/*******************************************************************************
    * ServerCore Class :
*******************************************************************************/
class ServerCore
{
public:
    typedef IEventHandler                       IEH;
    typedef std::vector<Directive::SharedPtr>   DirPtrVector;
    typedef utls::shared_ptr<ServerCore>        SharedPtr;

    ~ServerCore(void);

    static ServerCore::SharedPtr  getInstance(void);

    void    setup(Directive::SharedPtr aGlobalDir);
    void    run(void);
    void    stop(void);

private:
    IReactor::SharedPtr    mReactor;
    bool                   mIsRunning;
  
    ServerCore(void);

    void    _setupHttp(Directive::SharedPtr aGlobalDir);
};

#endif /* __SERVERCORE_HPP__ */
