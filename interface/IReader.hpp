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
        virtual void     read(void) = 0;
        virtual void     write(const std::string& aBody) = 0;
        // virtual FILE*    getFile(void) = 0;
        // virtual off_t    getFilesize(void) = 0;
        // virtual off_t    getFilePos() = 0;
        // virtual char*    getPath() const = 0;

    protected:
            FILE*   mFile;
            char*   mPath;
    };
}

#endif	/* __IReader_HPP__ */
