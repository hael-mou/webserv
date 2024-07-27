#include <cerrno>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
# include <sstream>
 
int main()
{

    std::string p = "k";
    std::stringstream sizeStream(p);
    size_t chunkSize;
    std::string last;
    sizeStream >> std::hex >> chunkSize >> last;
    std::cout << chunkSize << std::endl;
    std::cout << last << std::endl;

// errno can be set to any non-zero value by a library function call
        // regardless of whether there was an error, so it needs to be cleared
        // in order to check the error set by strtol
        // errno = 0;
        // long i = std::strtol(p, NULL ,16);
        // std::cout << "I --->" << i << std::endl;
        // perror("strtol");
}