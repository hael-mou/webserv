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
# include "IRequest.hpp"
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

            void        write(std::string& aBody);
            void        read();
            size_t      getSizeFile();
            bool        isComplete();
            int        getFile(void) const;
        
        private: 
            size_t      mContentLength;
    };
}
# endif /* __HTTPREADER_HPP__ */