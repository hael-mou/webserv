//  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣴⣶⣾⣿⣶⣶⣶⣶⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢠⡶⠻⠛⠟⠋⠉⠀⠈⠤⠴⠶⠶⢾⣿⣿⣿⣷⣦⠄⠀⠀⠀          𓐓  Utils.hpp 𓐔           
//  ⠀⠀⠀⠀⠀⢀⠔⠋⠀⠀⠤⠒⠒⢲⠀⠀⠀⢀⣠⣤⣤⣬⣽⣿⣿⣿⣷⣄⠀⠀                                              
//  ⠀⠀⠀⣀⣎⢤⣶⣾⠅⠀⠀⢀⡤⠏⠀⠀⠀⠠⣄⣈⡙⠻⢿⣿⣿⣿⣿⣿⣦⠀  Student: oezzaou <oezzaou@student.1337.ma> 
//  ⢀⠔⠉⠀⠊⠿⠿⣿⠂⠠⠢⣤⠤⣤⣼⣿⣶⣶⣤⣝⣻⣷⣦⣍⡻⣿⣿⣿⣿⡀                                              
//  ⢾⣾⣆⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇                                              
//  ⠀⠈⢋⢹⠋⠉⠙⢦⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇     Created: 2024/05/15 11:58:00 by oezzaou
//  ⠀⠀⠀⠑⠀⠀⠀⠈⡇⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇     Updated: 2024/05/30 14:05:50 by hael-mou
//  ⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢀⣾⣿⣿⠿⠟⠛⠋⠛⢿⣿⣿⠻⣿⣿⣿⣿⡿⠀                                             
//  ⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⢠⣿⣟⣭⣤⣶⣦⣄⡀⠀⠀⠈⠻⠀⠘⣿⣿⣿⠇⠀                                            
//  ⠀⠀⠀⠀⠀⠱⠤⠊⠀⢀⣿⡿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⠏⠀⠀                             𓆩♕𓆪      
//  ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠘⢧⡀⠀⠀⠸⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠐⠋⠀⠀⠀                        𓄂 oussama ezzaou𓆃
//  ⠀⠀⠀⠀⠀⠘⠄⣀⡀⠸⠓⠀⠀⠀⠠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                              

#ifndef   __UTILS_HPP__
# define   __UTILS_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"

# include <netinet/in.h> 
# include <unistd.h>
# include <sstream>
# include <string>
# include <ctime>

# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <netdb.h>

/*******************************************************************************
    * string Utils :
*******************************************************************************/
namespace str
{
    std::string    strtrim(const_string& str);
    std::string    toLower(const_string& str);
    StringPair     lineToPair(const_string& line, const char sep);
    StringVector   split(const_string str, const char sep);
    std::string    addrtoString(const in_addr_t& addr, const socklen_t& addrLen);
    std::string&   replace(std::string& str, const_string& from, const_string& to);

    template <typename T>
    std::string    to_string(const T& number)
    {
        std::ostringstream oss;
        oss << number;
        return oss.str();
    }

};

/*******************************************************************************
    * integer Utils :
*******************************************************************************/
namespace integer
{
    int     strToInt(const_string& str);   
};

/*******************************************************************************
    * Logger Utils :
*******************************************************************************/
namespace Logger
{
    void         log(const_string& level, const_string& message, int fd = 1);
    std::string  getcurrentTime(void);
};

/*******************************************************************************
    * Socket Utils :
*******************************************************************************/
namespace sock
{
    Handle  createSocket(int family, int type, int protocol);
    void    bind(Handle socket, const_string& host, const_string& port);
    void    startListening(Handle socket, int backlog = 10);
    void    setReuseAddr(Handle& socket);
    void    setNonBlocking(Handle& socket);

}

/*******************************************************************************
 * Http Utils :
********************************************************************************/
namespace httptools
{
    bool    isSpecialChars(const char &c);
    bool    isValidHeader(const char &c);
    void    httpDecoder(std::string &str);


    enum HttpSpecialChars{
    Dot                 = '.',
    Dash                =  '-',
    Plus                = '+',
    Comma               = ',',
    Slash               = '/',
    Colon               = ':',
    Space               = ' ',
    Equals              = '=',
    Asterisk            = '*',
    Ampersand           = '&',
    Underscore          ='_',
    QuestionMark        = '?',
    ExclamationMark     = '!',
    LeftCurlyBracket    = '{',
    LeftSquareBracket   = '[',
    RightCurlyBracket   = '}',
    RightSquareBracket  = ']',
    };
}

#endif /* __UTILS_HPP__ */
