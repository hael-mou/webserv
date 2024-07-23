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

#include "HttpFileResponse.hpp"

/*******************************************************************************
    * Construction :
********************************************************************************/

//=== [ Constructor: FileResponse ] ============================================
http::FileResponse::FileResponse(void)
    : mFilePath(""),
      misConverted(false)
{
}

//=== [ Destructor: FileResponse ] =============================================
http::FileResponse::~FileResponse(void) {}

/*******************************************************************************
    * Public Methods :
*******************************************************************************/

//===[ setPath: set file path ]================================================
void http::FileResponse::setPath(const_string& aFilePath)
{
    mFilePath = aFilePath;
    mFileStream.open(aFilePath.c_str(), std::ios::in);
    if (!mFileStream.is_open() && errno == ENOENT)
        throw (http::NOT_FOUND);
    if (!mFileStream.is_open() && errno != ENOENT)
        throw (http::FORBIDDEN);
    setHeader("Content-Length", _fileSize());
}

//===[ toRaw: convert file to raw ]=============================================
std::string http::FileResponse::toRaw(void)
{
    if (misConverted == false)
    {
        mReadBuffer = AResponse::toRaw();
        misConverted = true;
    }

    if (mReadBuffer.empty())
       mReadBuffer = _readFromFile(1024);
    
    return (mReadBuffer);
}

//===[ removeBytesSent: remove bytes sent ]=====================================
void http::FileResponse::removeBytesSent(size_t aBytesSent)
{
    mReadBuffer.erase(0, aBytesSent);
}

//===[ eof: end of file ]======================================================
bool http::FileResponse::eof(void) const
{
    return (misConverted && mFileStream.eof());
}

//===[ display: display file ]=================================================
void http::FileResponse::display(void) const
{
    AResponse::display();
    std::cout << "file: "  << mFilePath << std::endl;
    std::cout << "\n=================" << std::endl;
}

//===[ _readFromFile: read file ]==============================================
std::string http::FileResponse::_readFromFile(size_t aSize)
{
    std::string buffer;
    char        readBuffer[aSize];

    mFileStream.read(readBuffer, aSize);
    buffer.assign(readBuffer, mFileStream.gcount());
    return (buffer);
}

//===[ _fileSize: get file size ]==============================================
std::string http::FileResponse::_fileSize(void)
{
    long size = 0;
    mFileStream.seekg(0, std::ios::end);
    size = mFileStream.tellg();
    mFileStream.seekg(0, std::ios::beg);

    return (str::to_string(size));
}