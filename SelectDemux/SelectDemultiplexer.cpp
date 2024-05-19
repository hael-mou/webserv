/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ SelectDemultiplexer implementation file ]                            #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-18                                                   #
#                                                                              #
** ************************************************************************* **/

#include "SelectDemultiplexer.hpp"

/** ************************************************************************ ***
#      * Construction :                                                        #
** ************************************************************************* **/

//===[ Constructor : ]==========================================================
SelectDemultiplexer::SelectDemultiplexer(void)
{
	clearSets();
}

//===[ Destructor : ]==========================================================
SelectDemultiplexer::~SelectDemultiplexer(void)
{
}

/** ****************************************************************************
#      * Methods :                                                             #
** ************************************************************************* **/

//===[ Select : ] ==============================================================
std::vector<Socketfd>	SelectDemultiplexer::select(long timeout)
{
    struct timeval timeVal;

    timeVal.tv_sec = timeout;
    timeVal.tv_usec = 0;

    if (::select(maxFd + 1, &readSet, &writeSet, NULL, &timeVal) <= 0)
        return (std::vector<Socketfd>());

    std::vector<Socketfd> readyDescriptors;
    for (int fd = 0; fd <= maxFd; ++fd)
    {
        if (FD_ISSET(fd, &readSet) || FD_ISSET(fd, &writeSet))
            readyDescriptors.push_back(fd);
    }
	clearSets();
    return (readyDescriptors);
}

//===[ registerSocket : ] ======================================================
void SelectDemultiplexer::registerSocket(const Socketfd socketFd, const Mode mode)
{
    maxFd = std::max(maxFd, socketFd);

    switch (mode) {
        case Read : FD_SET(socketFd, &readSet);
                    break;
        case Write: FD_SET(socketFd, &writeSet);
                    break;
    }
}
//===[ clearSets : ] ===========================================================
void	SelectDemultiplexer::clearSets(void)
{
	maxFd = 0;
	FD_ZERO(&readSet);
	FD_ZERO(&writeSet);
}
