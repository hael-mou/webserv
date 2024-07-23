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
    char FilePath[] = TEMP_FILE_PATH;
    mPath = strdup(mktemp(FilePath));
    std::cout << "The Path of File is ********" << mPath << "**********" << std::endl;
    mFile = fopen(mPath, "w");
    if (mFile == NULL)
    {
        throw std::runtime_error("Can't create temporary file");
    }
}

/*******************************************************************************
    * Destruction :
*******************************************************************************/
http::Reader::~Reader()
{
    std::cout << "Deleting temporary file" << std::endl;
    std::cout << "The Path of File is ********" << mPath << "**********" << std::endl;
    fclose(mFile);
    if (remove(mPath) != 0)
    {
        perror("Error deleting temporary file: ");
        exit(1);
    }
    // unlink(mPath); // to search wath do with it
}


/*******************************************************************************
    * Public Method of HttpReader:
*******************************************************************************/

//===[ Method: read ]==========================================================
void http::Reader::read()
{
    mFile = fopen(mPath, "r");
    if (mFile == NULL)
    {
        throw std::runtime_error("Can't open file");
    }

    int size = getSizeFile() + 1;
    char buffer[size];

    memset(buffer, 0, size);
    size_t bytes_read = fread(buffer, 1, size, mFile);
    if (bytes_read  > 0) {
        printf("Data read from file: %s\n", buffer);
    } else {
        perror("Error reading from file");
        fclose(mFile);
    }
    fclose(mFile);
}

void    http::Reader::write(const std::string& aBody)
{
    if (fseek(mFile, 0, SEEK_END) != 0)
    {
        throw std::runtime_error("Can't seek file");
    }
    if (fwrite(aBody.c_str(), 1, aBody.size(), mFile) != aBody.size())
    {
        perror("Error writing to file: "); // to change that 
    }

    if (getSizeFile() > (size_t)mContentLength)
    {
        std::cout << "File size" << getSizeFile() << "-> " << mContentLength << std::endl;
        // close and remove
        std::cout << "file depasse la taille de l'en-tete" << std::endl;
    }
    if (fclose(mFile) != 0)
    {
        perror("Error closing file: ");
        exit(1); // to be removed later
    }
}


//===[ Method: getSizeFile ]====================================================
size_t http::Reader::getSizeFile()
{
    size_t pos = ftell(mFile);      // to conserve the current position of the file
    fseek(mFile, 0, SEEK_END);      // to move the pointer to the end of the file
    pos = ftell(mFile);             // to get the position of the pointer
    fseek(mFile, pos, SEEK_SET);    // to move the pointer back to the position
    rewind(mFile);
    return (pos);                   // return the size of the file
}

