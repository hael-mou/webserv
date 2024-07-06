/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Logger implementation file ]                                         #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-04                                                   #
#                                                                              #
** ************************************************************************* **/

#include "Logger.hpp"

//=== [ print error in file ] ==================================================
void	Logger::log(const_string& level, const_string& message, int fd)
{
    std::string time = getcurrentTime();

    fd = (fd >= 0) ? fd : 1;
    std::string logMsg = "[" + time + "]: " + level + ": " + message + "\n";
    ::write(fd, logMsg.c_str(), logMsg.size());
}

//=== [ get current time ] =====================================================
std::string		Logger::getcurrentTime(void)
{
    time_t  now      = time(0);
    tm*     timeinfo = localtime(&now);
    char    timestamp[20];

    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    return (timestamp);
}
