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
#include <iostream>

int		main(void)
{
	try
	{
		ConfigParser	configParser;
		configParser.openFile("config/default.conf");
		configParser.parse();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
