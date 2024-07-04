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

# include "IEventHandler.hpp"
# include "Directive.hpp"
# include "HttpFactory.hpp"

# include <exception>

/*******************************************************************************
    * ServerCore Class :
*******************************************************************************/
class ServerCore
{
public:
    class Exception;

    typedef IEventHandler                       IEH;
    typedef std::vector<Directive::SharedPtr>   DirPtrVector;

    ServerCore(void);
    virtual ~ServerCore(void);

    void    setup(Directive::SharedPtr aGlobalDir);
    void    run(void);

private:
    // IReactor*    mReactor;

    void    _setupHttp(Directive::SharedPtr aGlobalDir);
};

#endif /* __SERVERCORE_HPP__ */