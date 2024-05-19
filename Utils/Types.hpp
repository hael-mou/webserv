/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Types definition ]                                                   #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-16                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __TYPEDEFINITIONS_HPP__
# define   __TYPEDEFINITIONS_HPP__

//===[ Type Definitions ]====================================================
typedef int		Socketfd;

//===[ Mode Enum ]=============================================================
enum  Mode {
	Read,
	Write
};

//===[ HandlerState Enum ]====================================================
enum  HandlerState {
	END,
	CONTINUE
};

#endif /* __TYPEDEFINITIONS_HPP__ */