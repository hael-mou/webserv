/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Man Program File ]                                                 #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-03                                                   #
#                                                                              #
** ************************************************************************* **/

#include "HttpCluster.hpp"
#include "HttpFactory.hpp"

/*******************************************************************************
    * Construction :
*******************************************************************************/

//===[ Constructor: Cluster ]===================================================
http::Cluster::Cluster(Directive::SharedPtr httpDir)
{
    DirPtrVector serverDir = httpDir->getNonTerminal("server");
    if (serverDir.size() == 0)
        throw (Exception("HTTP: No server directive found"));
    for (size_t i = 0; i < serverDir.size(); ++i)
    {
        Server::SharedPtr server = http::Factory::createServer(serverDir[i]);
        StringVector listenSet = server->getListen();
        for (size_t index = 0; index < listenSet.size(); ++index)
        {
            std::string listen = listenSet[index];
            if (_isSocketReadyCreated(listen) == false)
            {
                Handle socket = 0;
                if ((socket = http::Factory::createSocket(listen)) == -1)
                    continue;
                mSockets[listen] = socket;
            }
            mServers[mSockets[listen]].push_back(server);
        }
    }
}

//===[ Destructor: Cluster ]====================================================
http::Cluster::~Cluster(void) {}

/*******************************************************************************
    * Public Methods :
*******************************************************************************/

//===[ QueueOfHandler: Cluster ]================================================
IEventHandler::IEventHandlerQueue  http::Cluster::createHandlers(void)
{
    IEH::IEventHandlerQueue Handlers;
    ServerMap::iterator it = mServers.begin();
	while (it != mServers.end())
	{
		// Handlers.push(
		// 	http::Factory::createAcceptHandler(it->first, it->second)
		// );
		++it;
	}
    return (Handlers);
}

/*******************************************************************************
    * Private Methods :
*******************************************************************************/

//===[ Method: Check if socket is created ]====================================
bool	http::Cluster::_isSocketReadyCreated(const_string& aListen) const
{
    return (mSockets.find(aListen) != mSockets.end());
}

/*********************************************************************************
    * ServerCore Exception :
*******************************************************************************/

//===[ Constructor: Exception ]=================================================
http::Cluster::Exception::Exception(std::string aMessage)
{
    mMessage = aMessage + "\n";
}

//===[ Destructor: Exception ]==================================================
http::Cluster::Exception::~Exception() throw() {};

//===[ Method: what ]===========================================================
const char* http::Cluster::Exception::what() const throw()
{
    return (mMessage.c_str());
}
