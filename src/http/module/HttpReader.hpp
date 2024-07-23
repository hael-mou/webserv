/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpReader header file ]                                            #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-22                                                   #
#                                                                              #
** ************************************************************************* **/

# ifndef __HTTPREADER_HPP__
# define __HTTPREADER_HPP__


/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "Utils.hpp"

# include "IReader.hpp"
/*******************************************************************************
    * Class Reader :
*******************************************************************************/
namespace http
{
    class Reader : public IReader
    {
        public:
            Reader(const int aContentLength);
            ~Reader();

            void        write(const std::string& aBody);
            void        read();
            // FILE*       getFile();
            size_t      getSizeFile();
            // fpos_t      getFilePos();
            // char*       getPath() const;
        private: 
            int     mContentLength;
    };
}
# endif /* __HTTPREADER_HPP__ */