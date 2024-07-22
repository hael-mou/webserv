/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ IServer Interface ]                                                 #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-22                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __IREADER_HPP__
# define   __IREADER_HPP__


/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"


/*******************************************************************************
    * http::IReader Interface :
*******************************************************************************/

namespace http
{
    class IReader
    {
    public:
        typedef mem::shared_ptr<IReader>           SharedPtr;

        virtual ~IReader(void) {};

        virtual void            selectMatechedRoute(const ServerVector& aServers) = 0;
        virtual void            setHeader(std::string& aLine) = 0;

    };
}

#endif	/* __IReader_HPP__ */
