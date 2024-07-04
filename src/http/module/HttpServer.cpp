/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpServer implementation file ]                                     #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-06-02                                                   #
#                                                                              #
** ************************************************************************* **/

# include "HttpServer.hpp"
# include "HttpFactory.hpp"

/*******************************************************************************
	* Construction :
*******************************************************************************/

//===[ Constructor: Server ]===================================================
http::Server::Server(Directive::SharedPtr aServerDir)
{
	mListen = _processListenDirective(aServerDir->getTerminal("listen"));
	mServerName = _processHostDirective(aServerDir->getTerminal("server_name"));
}

//===[ Destructor: Server ]====================================================
http::Server::~Server(void) {}

/*******************************************************************************
	* Public Methods :
*******************************************************************************/

//===[ getListen: get the listen list ]=========================================
const StringVector http::Server::getListen(void) const
{
	return (mListen);
}

//===[ getName: get the server name ]===========================================
const StringVector http::Server::getName(void)
{
	return (mServerName);
}

/*******************************************************************************
	* Private Methods :
*******************************************************************************/

//===[ Method: process listen directive ]=======================================
StringVector
http::Server::_processListenDirective(const StringVector& aListenDir)
{
	StringVector listenSet;

	for (size_t index = 0; index < aListenDir.size(); ++index)
	{
		StringVector addressPort = utls::split(aListenDir[index], ':');
		if (addressPort.size() != 2)
		{
			Logger::log("WARNING", "HTTP: Listen directive ignored: "
				+ aListenDir[index], 2);
			continue ;
		}
		int port = atoi(addressPort[1].c_str());
		if (port <= 0 || port > 65535)
		{
			Logger::log("WARNING", "HTTP: Listen directive ignored: "
				+ aListenDir[index], 2);
			continue ;
		}
		std::string address = utls::strtrim(addressPort[0]);
		std::string portString = utls::strtrim(addressPort[1]);
		listenSet.push_back(address + ":" + portString);
	}
	if (listenSet.size() == 0)
	{
		listenSet.push_back("0.0.0.0:80");
	}
	return (listenSet);
}

//===[ Method: process host directive ]=========================================
StringVector
http::Server::_processHostDirective(const StringVector& hostDir)
{
    StringVector hostList;
    if (hostDir.size() == 1)
        hostList = utls::split(hostDir[0], ',');
    return (hostList);
}
