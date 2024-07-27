 /** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpChunkReader Header File ]                                       #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-22                                                   #
#                                                                              #
** ************************************************************************* **/

# ifndef __HTTPCHUNKREADER_HPP__
# define __HTTPCHUNKREADER_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "IReader.hpp"
# include "IRequest.hpp"

# include "Utils.hpp"
/*******************************************************************************
    * Class Reader :
*******************************************************************************/
namespace http
{
    class ChunkReader : public IReader
    {
        typedef void    (ChunkReader::*Process)(std::string& aLine);

        public:
            ChunkReader();
            ~ChunkReader();

            void        write(std::string& aBody);
            void        read();
            size_t      getSizeFile();
            bool        isComplete();
            int         getFile(void) const;
            
        
        private: 
    
            size_t      mLength;
            size_t      mChunkSize;
            bool        mTerminated;
            std::string mChunkBody;
            Process     mCurrentOperation;
        
            void        _processChunkSize(std::string& aLine);
            void        _processChunkBody(std::string& aLine);
            void        _writeChunkToFile();
            void        _resetChunkState();
    };
}
# endif /* __HTTPREADER_HPP__ */
