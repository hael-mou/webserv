/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ ICluster Interface ]                                                #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-09                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef __ICLUSTER_HPP__
# define __ICLUSTER_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"

# include "IEventHandler.hpp"

/*******************************************************************************
    * ICluster Interface :
*******************************************************************************/
class ICluster
{
public:
    virtual ~ICluster(void) {};
    virtual IEventHandler::IEventHandlerQueue  createHandlers(void) = 0;
};

#endif /* __ICLUSTER_HPP__ */
