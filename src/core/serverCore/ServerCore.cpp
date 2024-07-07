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

#include "ServerCore.hpp"

/*******************************************************************************
    * Construction :
*******************************************************************************/

//===[ Constructor: getInstance ]===============================================
ServerCore::SharedPtr  ServerCore::getInstance(void)
{
    static ServerCore::SharedPtr instance = new ServerCore();
    return (instance);
}

//===[ Constructor: ServerCore ]================================================
ServerCore::ServerCore(void)
    : mReactor(NULL)
{
    IMultiplexer* multiplexer = new SelectMultiplexer();
    mReactor = new Reactor(multiplexer);
}

//===[ Destructor: ServerCore ]=================================================
ServerCore::~ServerCore(void){}

/*******************************************************************************
    * Public Methods :
*******************************************************************************/

//===[ Method: init Start Servers Handler ]=====================================
void	ServerCore::setup(Directive::SharedPtr aGlobalDir)
{
    _setupHttp(aGlobalDir);
}

//===[ Method: run Start Servers Handler ]======================================
void	ServerCore::run(void)
{
    while (mIsRunning)
    {
        mReactor->handleEvents(1000000);
        mReactor->cleanupTerminatedHandlers();
    }
}

//===[ Method: stop all Servers ]===============================================
void	ServerCore::stop(void)
{
    mIsRunning = false;
}

/*******************************************************************************
    * Private Methods :
*******************************************************************************/

//===[ Method: setup Http Protocol ]============================================
void ServerCore::_setupHttp(Directive::SharedPtr aGlobalDir)
{
    try
    {
        DirPtrVector httpDir = aGlobalDir->getNonTerminal("http");
        if (httpDir.size() > 1)
            Logger::log("WARNING", "HTTP: Just first Http directive is used", 2);
        if (httpDir.size() == 0)
            return ;
        http::Cluster *cluster = http::Factory::createCluster(httpDir.front());
        IEH::IEventHandlerQueue Handlers = cluster->createHandlers();
        mReactor->registerEventHandler(Handlers);
        delete (cluster);
        mIsRunning = true;
    }
    catch(const std::exception& e)
    {
        Logger::log("ERROR", e.what(), 2);
    }
}
