//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########< ConfigParser.hpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 11:58:00 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/21 14:05:50 by oezzaou

#ifndef   __CONFIGPARSER_HPP__
# define   __CONFIGPARSER_HPP__

/*******************************************************************************
	* Includes :
*******************************************************************************/
# include "Directive.hpp"
# include "ParserUtils.hpp"

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
	
	typedef std::pair<std::string, std::fstream*>	file;
	typedef std::vector<DirectivePart>				dirParts;
	typedef std::vector<Directive>					directive;


	ConfigParser(void);
	virtual ~ConfigParser(void);

	void openFile(const std::string& aFileName, int aStartColumn = 0);
	bool isFileAlreadyOpen(const std::string& aFileName) const;
	void CloseLastOpenFile(void);

	std::vector<Directive>	parse(void);

private:
	std::vector<file>	 mFiles;
	std::vector<int>	mLevels;
	std::vector<int>	mStartColumn;
	std::vector<int>	mlineCount;

	void _processLine(std::string&aLine, directive& aDirs, dirParts& aDirParts);
	int	 getLevel(const std::string& aLine);
	bool isValidDirective(const dirParts &aDirParts, int aLevel) const;
	bool includeDirective(const std::string& aLine, int aLevel);
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
