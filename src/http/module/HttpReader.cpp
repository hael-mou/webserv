/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpReader Implementation ]                                         #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-22                                                   #
#                                                                              #
** ************************************************************************* **/

# include "HttpReader.hpp"
# include <iostream>

/*******************************************************************************
    * Construction :
*******************************************************************************/

http::Reader::Reader(const int aContentLength) : mContentLength(aContentLength)
{
    char myTemplate[] = "/tmp/http_XXXXXX"; // to be modife later and need suggestion mn 3nd Hamza
    mFile = mkstemp(myTemplate);
    if (mFile == -1)
    {
        perror("Error creating temporary file: ");
        exit(1);
    }
}

/*******************************************************************************
    * Destruction :
*******************************************************************************/
http::Reader::~Reader()
{
    // to se a solotion for unlinkage to remove the file from /tmp later 
    if (::close(mFile) == -1)
    {
        perror("Error deleting temporary file: ");
        exit(1);
    }
}


/*******************************************************************************
    * Public Method of HttpReader:
*******************************************************************************/

//===[ Method: read ]==========================================================
void http::Reader::read()
{
    int size = getSizeFile() + 1;
    char buffer[size];

    ::lseek(mFile, 0, SEEK_SET); // to reset the file pointer at the begeinin :)
    memset(buffer, 0, size);
    size_t bytes_read = ::read(mFile, buffer, size);
    if (bytes_read  > 0) {
        printf("Data read from file: %s\n", buffer);
    } else {
        perror("Error reading from file");
        close(mFile);
        throw(std::runtime_error("Failed to read from file"));
    }
}

#include "IRequest.hpp" // for thorwing ? 
void    http::Reader::write(std::string& aBody)
{
    // there is a problem when reading with nc or maybe telnet because both they send ,
    // a \r\n or \n at the end
    // when sending something ? how can i remove it ? and or just ignore it ?
    size_t bytes_written = ::write(mFile, aBody.c_str(), aBody.size());
    if (bytes_written != aBody.size())
    {
        throw std::runtime_error("Failed to write to file");
    }
    size_t file_size = getSizeFile();
    if (file_size > mContentLength)
    {
        throw(http::IRequest::PAYLOAD_TOO_LARGE);
    }
    aBody.clear();
}


//===[ Method: getSizeFile ]====================================================
size_t http::Reader::getSizeFile()
{
    struct stat st;
    if (fstat(mFile, &st) == -1)
    {
        perror("Error getting file status: ");
        throw(std::runtime_error("Failed to get file status"));
    }
    return (st.st_size); // hadi ghadi dir moxkil
}


//===[ Method: isComplete ]=====================================================
bool http::Reader::isComplete()
{
    return (getSizeFile() == mContentLength);
}

//===[ Method: getFile ]========================================================
int http::Reader::getFile() const
{
    return (mFile);
}