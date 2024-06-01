//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########   < Directive.hpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 12:54:33 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/19 17:08:02 by oezzaou

#ifndef  __DIRECTIVE_HPP__
# define  __DIRECTIVE_HPP__

/*******************************************************************************
	* Includes :
*******************************************************************************/
# include "ParserUtils.hpp"
# include "Dictionary.hpp"

# include <string>
# include <vector>
# include <map>

/*******************************************************************************
	* DirectivePart struct :
*******************************************************************************/ 
typedef enum { Terminal = 0, NonTerminal=1 }	DirectiveType;

struct	DirectivePart
{
	DirectivePart(const std::string& aLine, const std::string& aFile,
		int aNline, int aLevel);
	
	DirectiveType		mType;
	std::string 		mFile;
	std::string			mKey;
	std::string			mRest;
	int					mLevel;
	int					mNline;
};

/*******************************************************************************
	* Directive Class :
*******************************************************************************/ 
class	Directive
{
public:
	class Exception;

	typedef std::string								string;
	typedef std::vector<DirectivePart>::iterator	DirPartsIter;

	Directive(DirPartsIter& aBegin, DirPartsIter aEnd);
	virtual ~Directive(void);

private:
	std::map<string, std::vector<Directive> >	mNonTerminal;
	std::map<string, std::vector<string> >		mTerminal;
	static int 									sCurrentLevel;
	static std::vector<std::string> 			sHosts;

	void _processNonTerminalDirective(DirPartsIter& adirIt, DirPartsIter aEnd);
	void _processTerminalDirective(DirPartsIter& adirIt);
};

/*******************************************************************************
	* Exception Class :
*******************************************************************************/ 
class Directive::Exception : public std::exception
{
public:
	Exception(const std::string& aMessage, const std::string& aFile, int aNline);
	virtual ~Exception(void) throw();

	const char* what(void) const throw();
private:
	std::string	mMessage;
};

#endif /* __DIRECTIVE_HPP__ */
