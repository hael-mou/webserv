//  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣴⣶⣾⣿⣶⣶⣶⣶⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢠⡶⠻⠛⠟⠋⠉⠀⠈⠤⠴⠶⠶⢾⣿⣿⣿⣷⣦⠄⠀⠀⠀          𓐓  ConfigParser.hpp 𓐔           
//  ⠀⠀⠀⠀⠀⢀⠔⠋⠀⠀⠤⠒⠒⢲⠀⠀⠀⢀⣠⣤⣤⣬⣽⣿⣿⣿⣷⣄⠀⠀                                              
//  ⠀⠀⠀⣀⣎⢤⣶⣾⠅⠀⠀⢀⡤⠏⠀⠀⠀⠠⣄⣈⡙⠻⢿⣿⣿⣿⣿⣿⣦⠀  Student: oezzaou <oezzaou@student.1337.ma> 
//  ⢀⠔⠉⠀⠊⠿⠿⣿⠂⠠⠢⣤⠤⣤⣼⣿⣶⣶⣤⣝⣻⣷⣦⣍⡻⣿⣿⣿⣿⡀                                              
//  ⢾⣾⣆⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇                                              
//  ⠀⠈⢋⢹⠋⠉⠙⢦⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇     Created: 2024/05/15 11:58:00 by oezzaou
//  ⠀⠀⠀⠑⠀⠀⠀⠈⡇⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇     Updated: 2024/05/25 14:05:50 by oezzaou
//  ⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢀⣾⣿⣿⠿⠟⠛⠋⠛⢿⣿⣿⠻⣿⣿⣿⣿⡿⠀                                             
//  ⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⢠⣿⣟⣭⣤⣶⣦⣄⡀⠀⠀⠈⠻⠀⠘⣿⣿⣿⠇⠀                                            
//  ⠀⠀⠀⠀⠀⠱⠤⠊⠀⢀⣿⡿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⠏⠀⠀                             𓆩♕𓆪      
//  ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠘⢧⡀⠀⠀⠸⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠐⠋⠀⠀⠀                        𓄂 oussama ezzaou𓆃
//  ⠀⠀⠀⠀⠀⠘⠄⣀⡀⠸⠓⠀⠀⠀⠠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                              

#ifndef   __CONFIGPARSER_HPP__
# define   __CONFIGPARSER_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "ParserUtils.hpp"
# include "Shared_ptr.hpp"

# include "Directive.hpp"

# include <exception>
# include <fstream>

/*******************************************************************************
    * ConfigParser Class :
*******************************************************************************/
class	ConfigParser
{
public:
    class Exception;
    
    typedef Directive                               Dir;
    typedef std::string                             string;
    typedef std::vector<DirectivePart>              DirPartVect;
    typedef std::pair<std::string, std::fstream*>   FilePair;

    ConfigParser(void);
    ConfigParser(const_string& aConfigParser);
    virtual ~ConfigParser(void);

    void                 openFile(const_string& aFileName, int aStartColumn = 0);
    Directive::SharedPtr parse(void);

private:
    std::vector<FilePair>       mFiles;
    std::vector<int>            mLevels;
    std::vector<int>            mStartColumn;
    std::vector<int>            mlineCount;

    void _processLine(string& aLine, Dir::SharedPtr& aDir, DirPartVect& aDirParts);
    bool _isFileAlreadyOpen(const_string& aFileName) const;
    int  _getLevel(const_string& aLine);
    bool _isValidDirective(const DirPartVect &aDirParts, int aLevel) const;
    bool _includeDirective(const_string& aLine, int aLevel);
    void _CloseLastOpenFile(void);
};

/*******************************************************************************
    * ConfigParser Exception :
*******************************************************************************/
class	ConfigParser::Exception : public std::exception
{
public:
    Exception(std::string aMessage, std::string aLine);
    virtual ~Exception(void) throw();
    const char* what(void) const throw();

private:
    std::string mMessage;
};

#endif /* __CONFIGPARSER_HPP__ */
