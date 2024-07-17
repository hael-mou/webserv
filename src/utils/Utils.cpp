//  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣴⣶⣾⣿⣶⣶⣶⣶⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢠⡶⠻⠛⠟⠋⠉⠀⠈⠤⠴⠶⠶⢾⣿⣿⣿⣷⣦⠄⠀⠀⠀          𓐓  Utils.cpp 𓐔           
//  ⠀⠀⠀⠀⠀⢀⠔⠋⠀⠀⠤⠒⠒⢲⠀⠀⠀⢀⣠⣤⣤⣬⣽⣿⣿⣿⣷⣄⠀⠀                                              
//  ⠀⠀⠀⣀⣎⢤⣶⣾⠅⠀⠀⢀⡤⠏⠀⠀⠀⠠⣄⣈⡙⠻⢿⣿⣿⣿⣿⣿⣦⠀  Student: oezzaou <oezzaou@student.1337.ma> 
//  ⢀⠔⠉⠀⠊⠿⠿⣿⠂⠠⠢⣤⠤⣤⣼⣿⣶⣶⣤⣝⣻⣷⣦⣍⡻⣿⣿⣿⣿⡀                                              
//  ⢾⣾⣆⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇                                              
//  ⠀⠈⢋⢹⠋⠉⠙⢦⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇     Created: 2024/05/15 11:58:00 by oezzaou
//  ⠀⠀⠀⠑⠀⠀⠀⠈⡇⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇     Updated: 2024/05/21 14:05:50 by oezzaou
//  ⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢀⣾⣿⣿⠿⠟⠛⠋⠛⢿⣿⣿⠻⣿⣿⣿⣿⡿⠀                                             
//  ⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⢠⣿⣟⣭⣤⣶⣦⣄⡀⠀⠀⠈⠻⠀⠘⣿⣿⣿⠇⠀                                            
//  ⠀⠀⠀⠀⠀⠱⠤⠊⠀⢀⣿⡿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⠏⠀⠀                             𓆩♕𓆪      
//  ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠘⢧⡀⠀⠀⠸⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠐⠋⠀⠀⠀                        𓄂 oussama ezzaou𓆃
//  ⠀⠀⠀⠀⠀⠘⠄⣀⡀⠸⠓⠀⠀⠀⠠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                              

#include "Utils.hpp"

/*******************************************************************************
    * String Utils :
*******************************************************************************/

//===[ strtrim : ]============================================================
std::string str::strtrim(const_string& input)
{
    size_t start = input.find_first_not_of(' ');
    if (std::string::npos == start)
        return (std::string());
    size_t end = input.find_last_not_of(' ');
    return (input.substr(start, end - start + 1));
}

//===[ lineToPair : ]=========================================================
StringPair str::lineToPair(const_string& line, const char sep)
{
    StringPair          pair;
    std::stringstream   ss(line);
    getline(ss, pair.first, sep);
    getline(ss, pair.second);
    return (std::make_pair(strtrim(pair.first), strtrim(pair.second)));
}

//===[ split : ]==============================================================
std::vector<std::string> str::split(const_string str, const char sep)
{
    std::vector<std::string>    arr;
    std::stringstream           ss(str);
    std::string                 buff;

    while (getline(ss, buff, sep))
    {
        if (buff.empty() == false)
        {
            arr.push_back(buff);
        }
    }
    return (arr);
}

//===[ stirngTolower : ]=======================================================
std::string str::toLower(const_string &str)
{
    std::string result = str;
    for (size_t i = 0; i < result.length(); ++i) {
        result[i] = std::tolower(result[i]);
    }
    return (result);
}

//===[ address to string : ]===================================================
std::string str::addrtoString(const in_addr_t& addr, const socklen_t& addrLen)
{
    char* buffer = new char[addrLen];
    unsigned char* ip = (unsigned char*)&addr;
    
    snprintf(buffer, addrLen, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    std::string result(buffer);
    delete[] buffer;

    return (result);
}

//===[ replace : ]==============================================================
std::string& str::replace(std::string& str,
                          const_string& from,
                          const_string& to)
{
    if (from.empty())
        return (str);
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return (str);
}

/*******************************************************************************
    * integer Utils :
*******************************************************************************/

//===[ strToInt : ]=============================================================
int integer::strToInt(const_string& str)
{
    if (str.empty() == true)
        return (0);

    for (size_t index = 0; index < str.length(); ++index)
    {
        if (::isdigit(str[index]) == false)
            return (0);
    }

    return (atoi(str.c_str()));
}

/*******************************************************************************
    * Logger Utils :
*******************************************************************************/

//=== [ print error in file ] ==================================================
void	Logger::log(const_string& level, const_string& message, int fd)
{
    std::string time = getcurrentTime();

    fd = (fd >= 0) ? fd : 1;
    std::string logMsg = time + " - [" + level + "] " + message + "\n";
    ::write(fd, logMsg.c_str(), logMsg.size());
}

//=== [ get current time ] =====================================================
std::string		Logger::getcurrentTime(void)
{
    time_t  now      = time(0);
    tm*     timeinfo = localtime(&now);
    char    timestamp[20];

    strftime(timestamp, sizeof(timestamp), "%Y/%m/%d %H:%M:%S", timeinfo);
    return (timestamp);
}

/*******************************************************************************
    * Socket Utils :
*******************************************************************************/

//=== [ create socket ] ========================================================
Handle sock::createSocket(int family, int type, int protocol)
{
    Handle socketHandle = -1;
    socketHandle = ::socket(family, type, protocol);
    if (socketHandle < 0)
        throw std::runtime_error("SOCKET: Failed to create socket");
    return (socketHandle);
}

//=== [ bind ] =================================================================
void    sock::bind(Handle socket, const_string& host, const_string& port)
{
    struct addrinfo     hints;
    struct addrinfo*    result;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host.c_str(), port.c_str(), &hints, &result) != 0)
    {
        throw std::runtime_error("SOCKET: Failed to resolve host/port");
    }

    if (bind(socket, result->ai_addr, result->ai_addrlen) == -1)
    {
        freeaddrinfo(result);
        throw (std::runtime_error("SOCKET: Failed to bind socket"));
    }

    freeaddrinfo(result);
}

//=== [ start listening ] ======================================================
void    sock::startListening(Handle socket, int backlog)
{
    if (::listen(socket, backlog) == -1)
    {
        throw std::runtime_error("SOCKET: Failed to start listening");
    }
}

//=== [ set reuse address ] ====================================================
void    sock::setReuseAddr(Handle& socket)
{
    int reuse = 1;
    if (::setsockopt(socket, SOL_SOCKET, SO_REUSEADDR,
            &reuse, sizeof(reuse)) < 0)
    {
        throw std::runtime_error("SOCKET: setReuseAddr setsockopt() failed");
    }
}

//=== [ set non blocking ] =====================================================
void    sock::setNonBlocking(Handle& socket)
{
    if (::fcntl(socket, F_SETFL, O_NONBLOCK) < 0)
    {
        throw std::runtime_error("SOCKET: setNonBlocking fcntl() failed");
    }
}

/*******************************************************************************
 * HTTP Utils
*******************************************************************************/

//=== [ isValidHeader ] ========================================================
bool    httptools::isValidHeader(const char &c)
{
    if (!(::isalnum(c) || c == '-' || c == '_' ))
        return (false);
    return (true);
}

//=== [ isSpecialChar ] ========================================================
bool    httptools::isSpecialChars(const char &c)
{
    if (!(::isalnum(c) || HttpSpecialChars(c)))
        return (false);
    return (true);
}

//===[ httpDecoder: ]===========================================================
void    httptools::httpDecoder(std::string &str)
{
	std::size_t percentSignPosition;
	while ((percentSignPosition = str.find('%')) != std::string::npos)
	{
		std::string hexadecimalValue = str.substr(percentSignPosition + 1, 2);
		char character = static_cast<char>(std::strtol(hexadecimalValue.c_str()
            ,NULL, 16));
		str.replace(percentSignPosition, 3, 1, character);				
	}
}