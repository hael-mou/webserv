/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Logger header file ]                                                 #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-04                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __LOGGER_HPP__
# define   __LOGGER_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "Shared_ptr.hpp"
# include "typedefs.hpp"

# include <ctime>
# include <unistd.h>

/*******************************************************************************
    * Logger :
*******************************************************************************/
namespace Logger
{
    void         log(const_string& level, const_string& message, int fd = 1);
    std::string  getcurrentTime(void);
};

#endif /* __LOGGER_HPP__ */

// { DEBUG, INFO, WARNING, ERROR, CRITICAL }; 
  