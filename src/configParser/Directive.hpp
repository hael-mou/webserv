/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Directive header file ]                                              #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-25                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef  __DIRECTIVE_HPP__
# define  __DIRECTIVE_HPP__

/*******************************************************************************
	* Includes :
*******************************************************************************/
# include "ParserUtils.hpp"
# include "Dictionary.hpp"
# include "Shared_ptr.hpp"

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
	typedef mem::shared_ptr<Directive>				SharedDir_ptr;

	Directive(void);
	Directive(DirPartsIter& aBegin, DirPartsIter aEnd);
	virtual ~Directive(void);

	void	push(DirPartsIter& aBegin, DirPartsIter aEnd);
	std::vector<std::string>	getTerminal(const std::string& aKey) const;
	std::vector<SharedDir_ptr>  getNonTerminal(const std::string& aKey) const;

private:
	static int 										sCurrentLevel;
	static std::vector<std::string> 				sHosts;

	std::map<string, std::vector<SharedDir_ptr> >	mNonTerminal;
	std::map<string, std::vector<string> >			mTerminal;

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
