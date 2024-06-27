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

#include "ConfigParser.hpp"
#include "Shared_ptr.hpp"

#include <iostream>

int		main(int argc, char *argv[])
{
	std::string	configFilePath = "config/default.conf";
	configFilePath = (argc == 2) ? argv[1] : configFilePath;

	try
	{
		{
			ConfigParser	configParser;
			configParser.openFile(configFilePath);
			mem::shared_ptr<Directive> globalDir = configParser.parse();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
