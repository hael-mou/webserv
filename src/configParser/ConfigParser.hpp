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
# include "Directive.hpp"
# include "ParserUtils.hpp"
# include "Shared_ptr.hpp"

# include <algorithm>
# include <exception>
# include <fstream>
# include <string>
# include <vector>

/*******************************************************************************
	* ConfigParser Class :
*******************************************************************************/
class	ConfigParser
{
public:
	class Exception;
	
	typedef std::pair<std::string, std::fstream*>	File;
	typedef std::vector<DirectivePart>				DirPartSet;
	typedef mem::shared_ptr<Directive>				Dir_ptr;

	ConfigParser(void);
	virtual ~ConfigParser(void);

	void	openFile(const std::string& aFileName, int aStartColumn = 0);
	mem::shared_ptr<Directive>	parse(void);

private:
	std::vector<File>	mFiles;
	std::vector<int>	mLevels;
	std::vector<int>	mStartColumn;
	std::vector<int>	mlineCount;

	void _processLine(std::string& aLine, Dir_ptr& aDir, DirPartSet& aDirParts);
	bool _isFileAlreadyOpen(const std::string& aFileName) const;
	int  _getLevel(const std::string& aLine);
	bool _isValidDirective(const DirPartSet &aDirParts, int aLevel) const;
	bool _includeDirective(const std::string& aLine, int aLevel);
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
