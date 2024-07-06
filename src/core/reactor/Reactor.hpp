/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Reactor header file ]                                                #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-16                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __REACTOR_HPP__
# define   __REACTOR_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "typedefs.hpp"
# include "Shared_ptr.hpp"

# include "IReactor.hpp"
# include "IMultiplexer.hpp"

/*******************************************************************************
    * Class Reactor :
*******************************************************************************/
class Reactor : public IReactor
{
public:
    typedef IEventHandler                       IEH;
    typedef IMultiplexer                        IMux;
    typedef std::map<Handle, IEH::SharedPtr>	IEventHandlerMap;

    Reactor(IMultiplexer* aMultiplexer);
    virtual ~Reactor(void);

    void              registerEventHandler(IEH::SharedPtr aHandler);
    void              handleEvents(long long aTimeout_ms);
    void              registerEventHandler(IEventHandlerQueue& aHandlers);
    IEH::SharedPtr    unregisterEventHandler(IEH::SharedPtr aHandler);
    void              cleanupTerminatedHandlers(void);

private:
    IMux::SharedPtr   mMultiplexer;
    IEventHandlerMap  mEventHandlers;
};

#endif /* __REACTOR_HPP__ */
