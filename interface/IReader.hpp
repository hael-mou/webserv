/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ IReader Interface ]                                                 #
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


#define TEMP_FILE_PATH "/tmp/body_XXXXXX"
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
    
        virtual void        read(void) = 0;
        virtual void        write(std::string& aBody) = 0;
        virtual size_t      getSizeFile(void) = 0;
        virtual bool        isComplete(void) = 0;
        virtual int         getFile(void) const = 0;

    protected:
        int     mFile;
        char    *httpTemplate;
    };
}

#endif	/* __IReader_HPP__ */
