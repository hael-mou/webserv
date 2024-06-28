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

class	DirectivePart
{
public:
	typedef std::string								String;
	typedef enum { Terminal = 0, NonTerminal=1 }	Type;

	DirectivePart(const std::string& aLine, const std::string& aFile,
		int aNline, int aLevel);
	
	Type		mType;
	String 		mFile;
	String		mKey;
	String		mRest;
	int			mLevel;
	int			mNline;
};

/*******************************************************************************
	* Directive Class :
*******************************************************************************/ 
class	Directive
{
public:
	class Exception;

	typedef std::string								String;
	typedef mem::shared_ptr<Directive>				SharedPtr;
	typedef std::vector<DirectivePart>::iterator	DirPartVectIt;

	Directive(void);
	Directive(DirPartVectIt& aBegin, DirPartVectIt aEnd);
	virtual ~Directive(void);

	void  push(DirPartVectIt& aBegin, DirPartVectIt aEnd);
	std::vector<String>  getTerminal(const String& aKey) const;
	std::vector<Directive::SharedPtr>  getNonTerminal(const String& aKey) const;

private:
	static int						sCurrentLevel;
	static std::vector<String> 		sHosts;

	std::map<String, std::vector<Directive::SharedPtr> >	mNonTerminal;
	std::map<String, std::vector<String> >					mTerminal;

	void  _processTerminalDirective(DirPartVectIt& adirIt);
	void  _processNonTerminalDirective(DirPartVectIt& adirIt, DirPartVectIt aEnd);
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
