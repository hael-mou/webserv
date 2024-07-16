//  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣴⣶⣾⣿⣶⣶⣶⣶⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢠⡶⠻⠛⠟⠋⠉⠀⠈⠤⠴⠶⠶⢾⣿⣿⣿⣷⣦⠄⠀⠀⠀ 𓐓  HttpFactory.cpp 𓐔           
//  ⠀⠀⠀⠀⠀⢀⠔⠋⠀⠀⠤⠒⠒⢲⠀⠀⠀⢀⣠⣤⣤⣬⣽⣿⣿⣿⣷⣄⠀⠀                                              
//  ⠀⠀⠀⣀⣎⢤⣶⣾⠅⠀⠀⢀⡤⠏⠀⠀⠀⠠⣄⣈⡙⠻⢿⣿⣿⣿⣿⣿⣦⠀   Student: oussama <oezzaou@student.1337.ma> 
//  ⢀⠔⠉⠀⠊⠿⠿⣿⠂⠠⠢⣤⠤⣤⣼⣿⣶⣶⣤⣝⣻⣷⣦⣍⡻⣿⣿⣿⣿⡀                                              
//  ⢾⣾⣆⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇                                              
//  ⠀⠈⢋⢹⠋⠉⠙⢦⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇       Created: 2024/06/18 17:38:31 by oussama
//  ⠀⠀⠀⠑⠀⠀⠀⠈⡇⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇       Updated: 2024/06/29 15:06:20 by hael-mou
//  ⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢀⣾⣿⣿⠿⠟⠛⠋⠛⢿⣿⣿⠻⣿⣿⣿⣿⡿⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⢠⣿⣟⣭⣤⣶⣦⣄⡀⠀⠀⠈⠻⠀⠘⣿⣿⣿⠇⠀                                              
//  ⠀⠀⠀⠀⠀⠱⠤⠊⠀⢀⣿⡿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⠏⠀⠀                             𓆩♕𓆪      
//  ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠘⢧⡀⠀⠀⠸⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠐⠋⠀⠀⠀                     𓄂 oussama ezzaou𓆃  
//  ⠀⠀⠀⠀⠀⠘⠄⣀⡀⠸⠓⠀⠀⠀⠠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                              

#include "HttpFactory.hpp"

/*******************************************************************************
    * Module Factory :
*******************************************************************************/

//===[ Method: createCluster ]=================================================
ICluster* http::Factory::createCluster(Directive::SharedPtr aHttpDir)
{
    return (new http::Cluster(aHttpDir));
}

//===[ Method: createServer ]==================================================
http::IServer* http::Factory::createServer(Directive::SharedPtr aServerDir)
{
    return (new http::Server(aServerDir));
}

//===[ Method: createSocket ]==================================================
Handle http::Factory::createSocket(const_string& aListen)
{
    Handle socketHandle = -1;
    try {
        socketHandle = sock::createSocket(AF_INET, SOCK_STREAM, 0);
        StringVector hostPort = str::split(aListen, ':');

        sock::setReuseAddr(socketHandle);
        sock::setNonBlocking(socketHandle);
        sock::bind(socketHandle, hostPort[0], hostPort[1]);
        sock::startListening(socketHandle, SOMAXCONN);
        
        Logger::log("notice", "HTTP: Socket[" + std::to_string(socketHandle)
            + "] '" + aListen + "' created", 1);
        return (socketHandle);
    }
    catch (const std::exception& e)
    {
        Logger::log("error", e.what(), 2);
        return (close(socketHandle), -1);
    }
}

//===[ Method: createClient ]==================================================
http::IClient*  http::Factory::createClient(Handle aSocket,
                                            const sockaddr_in& aAddr,
                                            socklen_t aAddrLen)
{
    return (new http::Client(aSocket, aAddr, aAddrLen));
}

//===[ Method: createRequest ]=================================================
http::IRequest* http::Factory::createRequest(std::string& aReceivedData)
{
    if (aReceivedData.find("\r\n\r\n") != std::string::npos)
        return (new http::Request(aReceivedData));
    if (aReceivedData.find("\n\n") != std::string::npos)
        return (new http::Request(aReceivedData));
    return (NULL);
}

/*******************************************************************************
    *  Handlers Factory :
*******************************************************************************/

//===[ Method: createAcceptHandler ]============================================
IEventHandler* http::Factory::createAcceptHandler(Handle aSocket)
{
    return (new http::AcceptHandler(aSocket));
}

//===[ Method: createRecvHandler ]==============================================
IEventHandler* http::Factory::createRecvHandler(IClient::SharedPtr aClient)
{
    return (new http::RecvHandler(aClient));
}

//===[ Method: createSendHandler ]==============================================
IEventHandler* http::Factory::createSendHandler(IClient::SharedPtr aClient,
                                                IResponse::SharedPtr aResponse)
{
    return (new http::SendHandler(aClient, aResponse));
}
