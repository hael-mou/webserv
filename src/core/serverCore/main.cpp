/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Main Program File ]                                                 #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-21                                                   #
#                                                                              #
** ************************************************************************* **/


/*******************************************************************************
    * Includes :
*******************************************************************************/
#include "ConfigParser.hpp"
#include "ServerCore.hpp"
# include "Logger.hpp"

#include <iostream>
#include <signal.h>

/*******************************************************************************
    * Signal Handler :
*******************************************************************************/
void	signalHandler(int aSignal)
{
    (void)aSignal;
    ServerCore::getInstance()->stop();
    Logger::log("INFO", "SERVERCORE: Servers stopped !", 1);
}

/*******************************************************************************
    * Main Program :
*******************************************************************************/
int		main(int argc, char *argv[])
{
    std::string	configFilePath = "config/default.conf";
    configFilePath = (argc == 2) ? argv[1] : configFilePath;

    try
    {
        ServerCore::SharedPtr serverCore = ServerCore::getInstance();
        {
            ConfigParser             parser(configFilePath);
            Directive::SharedPtr    globalDir = parser.parse();
            serverCore->setup(globalDir);
        }

        signal(SIGPIPE, SIG_IGN);
        signal(SIGINT, signalHandler);
        signal(SIGTERM, signalHandler);
        serverCore->run();
    }
    catch(const std::exception& e)
    {
        Logger::log("ERROR" ,e.what(), 2);
    }
}
