/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpChunkReader Implementation ]                                    #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-26                                                   #
#                                                                              #
** ************************************************************************* **/

# include "HttpChunkReader.hpp"
# include <iostream>

/*******************************************************************************
    * Construction :
*******************************************************************************/


/* [mkstemp] : 
Temporary Files: mkstemp creates a temporary file with a unique name. 
This file remains on the file system until explicitly deleted. If you don't unlink the file, 
it will persist on disk, potentially cluttering your file system with unnecessary files.
Unlinking: Calling unlink removes the file entry from the directory.
If the file is still open by some process (e.g., your program), 
it will not be immediately deleted from disk, but the space will be freed up once it’s no longer in use.
*/

http::ChunkReader::ChunkReader() : mLength(0), mChunkSize(0), mTerminated(false)
{
    errno = 0;
    httpTemplate = new char[sizeof("/tmp/http_XXXXXX")];    // to be modife later
    strcpy(httpTemplate, "/tmp/http_XXXXXX");               // to be modife later
    mFile = mkstemp(httpTemplate);
    if (mFile == -1)
    {
        throw(std::runtime_error("Failed to create temporary file to store chunked data"));
    }
    mCurrentOperation = &ChunkReader::_processChunkSize;
}

/*******************************************************************************
    * Destruction :
*******************************************************************************/
http::ChunkReader::~ChunkReader()
{
    if (close(mFile) == -1)
    {
        throw (std::runtime_error("Failed to close temporary file"));
    }
    if (unlink(httpTemplate) == -1)
    {
        throw (std::runtime_error("Failed to unlink temporary file"));
    }
    delete[] httpTemplate;
}


/*******************************************************************************
    * Public Method of HttpReader:
*******************************************************************************/

//===[ Method: read ]==========================================================
void http::ChunkReader::read() 
{
    size_t bytes_read;
    int size = getSizeFile() + 1;
    char buffer[size];

    memset(buffer, 0, size);
    ::lseek(mFile, 0, SEEK_SET); // to reset the file pointer at the begeinin :)

    bytes_read = ::read(mFile, buffer, size);
    if (bytes_read  >= 0)  // had equal khass i3adat nadar
    {
        printf("Data read from file: %s\n", buffer);
    } 
    else 
    {
        throw(std::runtime_error("Failed to read from file"));
    }
}

void    http::ChunkReader::write(std::string& aBody)
{
    std::stringstream ss(aBody);
    std::string     line;

    while (std::getline(ss, line))
    {
        (this->*mCurrentOperation)(line);
    }
    aBody.clear();
}

//===[ Method: getSizeFile ]====================================================
size_t http::ChunkReader::getSizeFile()
{
    struct stat st;

    if (fstat(mFile, &st) == -1)
    {
        perror("Error getting file status: ");
        throw(std::runtime_error("Failed to get file status"));
    }

    return (st.st_size);
}


//===[ Method: isComplete ]=====================================================
bool http::ChunkReader::isComplete()
{
    return (mTerminated);
}

//===[ Method: getFile ]========================================================
int http::ChunkReader::getFile() const
{
    return (mFile);
}

/*******************************************************************************
    * Private Method of HttpReader:
*******************************************************************************/

//===[ Method: ChunkSizeParser ]================================================
void    http::ChunkReader::_processChunkSize(std::string& aLine)
{
    if (aLine.back() == '\r')
            aLine.pop_back();
    if (aLine.empty())
        throw(http::IRequest::BAD_REQUEST);
    mChunkSize = std::strtol(aLine.c_str(), NULL, 16);      // hadi gal 7mza ghybdlha 
    if (mChunkSize < 0 || mChunkSize > 1024 || errno != 0)  // to be modified later [max 1024]
    {
        throw(http::IRequest::BAD_REQUEST);
    }
    mCurrentOperation = &ChunkReader::_processChunkBody;
}

//===[ Method: ChunkBodyParser ]================================================
void    http::ChunkReader::_processChunkBody(std::string& aLine)
{
    if (aLine.back() == '\r')
    {
        aLine.pop_back();
        if (aLine.empty() && mChunkSize == 0)
            mTerminated = true;
        else
            mCurrentOperation = &ChunkReader::_processChunkSize;
        return ;
    }
    else if (!aLine.empty())
    {
        mChunkBody += aLine;
        mLength += aLine.length();
    }
    if (mLength > mChunkSize)
    {
        throw (http::IRequest::BAD_REQUEST);
    }
    else if (mLength == mChunkSize)
    {
        _writeChunkToFile();
        _resetChunkState();
        mCurrentOperation = &ChunkReader::_processChunkSize;
    }
}

void http::ChunkReader::_writeChunkToFile()
{
    size_t bytesWritten = ::write(mFile, mChunkBody.c_str(), mChunkBody.length());
    if (bytesWritten != mChunkBody.length())
    {
        throw std::runtime_error("Failed to write to file");
    }
}

void http::ChunkReader::_resetChunkState()
{
    mChunkBody.clear();
    mLength = 0;
}
