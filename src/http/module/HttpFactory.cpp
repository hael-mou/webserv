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
    * Public Methods :
*******************************************************************************/

//===[ Method: createCluster ]=================================================
http::Cluster*
http::Factory::createCluster(Directive::SharedPtr aHttpDir)
{
    return (new Cluster(aHttpDir));
}

//===[ Method: createServer ]==================================================
http::Server*
http::Factory::createServer(Directive::SharedPtr aServerDir)
{
    return (new Server(aServerDir));
}

//===[ Method: createSocket ]==================================================
Handle     http::Factory::createSocket(const_string& aListen)
{
    Handle  socketHandle = -1;

    try {
        socketHandle = ::socket(AF_INET, SOCK_STREAM, 0);
        if (socketHandle == -1) 
        {
            throw (std::runtime_error("Failed to create socket"));
        }
        
        StringVector hostPort = utls::split(aListen, ':');

        _setSocketOptions(socketHandle);
        _setNonBlocking(socketHandle);
        _bindSocket(socketHandle, hostPort[0], hostPort[1]);
        _startListening(socketHandle);

        Logger::log("INFO", "HTTP: Socket \"" + aListen + "\" created", 1);

    } catch (const std::exception& e)
    {
        Logger::log("ERROR", e.what(), 2);
        return (close(socketHandle), -1);
    }
    return (socketHandle);
}

/*******************************************************************************
    * Private Methods :
*******************************************************************************/

//===[ Method: setSocketOptions ]==============================================
void    http::Factory::_setSocketOptions(Handle aHandle)
{
    int opt = 1;
    if (setsockopt(aHandle, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        throw std::runtime_error("Failed to set socket options");
    }
}

//===[ Method: setNonBlocking ]================================================
void    http::Factory::_setNonBlocking(Handle aHandle)
{
    if (::fcntl(aHandle, F_SETFL, O_NONBLOCK) == -1)
    {
        throw std::runtime_error("Failed to set non-blocking");
    }
}

//===[ Method: bindSocket ]====================================================
void    http::Factory::_bindSocket(Handle aHandle,
                                   const_string& aHost,
                                   const_string& aPort)
{
    struct addrinfo     hints;
    struct addrinfo*    result;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(aHost.c_str(), aPort.c_str(), &hints, &result) != 0)
    {
        throw std::runtime_error("Failed to resolve host and port");
    }

    if (bind(aHandle, result->ai_addr, result->ai_addrlen) == -1)
    {
        freeaddrinfo(result);
        throw (std::runtime_error("Failed to bind socket"));
    }

    freeaddrinfo(result);
}

//===[ Method: startListening ]================================================
void    http::Factory::_startListening(Handle aHandle)
{
    if (listen(aHandle, SOMAXCONN) == -1)
    {
        throw std::runtime_error("Failed to start listening");
    }
}
