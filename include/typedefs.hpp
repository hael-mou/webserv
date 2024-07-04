/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Shared_ptr header file ]                                             #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-06-26                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef  __TYPEDEFS_HPP__
# define  __TYPEDEFS_HPP__

//====[ Includes : ] ===========================================================
# include <string>
# include <vector>
# include <queue>
# include <map>

//===[ Stirng : ] ==============================================================
typedef const std::string						const_string;
typedef std::pair<std::string, std::string>		StringPair;
typedef std::vector<std::string>				StringVector;
typedef std::map<std::string, std::string>		StringMap;

//===[ Handle : ] ==============================================================
typedef int										Handle;
typedef std::string								Address;
typedef std::string								Port;

#endif /* __TYPEDEFS_HPP__ */