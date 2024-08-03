/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpFileResponse header file ]                                       #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-18                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __HttpFileResponse_HPP__
# define   __HttpFileResponse_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"
# include "Utils.hpp"

# include "HttpAResponse.hpp"
# include "HttpException.hpp"

# include <iostream>
# include <fstream>

/*******************************************************************************
    * Defines :
*******************************************************************************/
# define READ_BUFFER_SIZE  10240

/*******************************************************************************
    * FileResponse Class :
*******************************************************************************/
namespace http
{
    class FileResponse : public AResponse
    {
    public:
        FileResponse(void);
        virtual ~FileResponse(void);

        void            setPath(const string& aFilePath);
        string          toRaw(void);
        void            removeBytesSent(size_t aBytesSent);
        bool            eof(void) const;
        void            display(void) const;
    
    private:
        string		    mFilePath;
        std::fstream	mFileStream;
        string		    mReadBuffer;
        bool			misConverted;

        string		_readFromFile(size_t aSize);
        string		_fileSize(void);

    };
}

#endif	/* __HttpFileResponse_HPP__ */