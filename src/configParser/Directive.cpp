/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Directive Implementation file ]                                      #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-25                                                   #
#                                                                              #
** ************************************************************************* **/

#include "Directive.hpp"

/*******************************************************************************
    * Static Variables :
*******************************************************************************/
int Directive::sCurrentLevel = 0;
std::vector<std::string> Directive::sHosts(1, "global");

/*******************************************************************************
    * construction :
*******************************************************************************/

//===[ Constructor: DirectivePart ]=============================================
DirectivePart::DirectivePart(const std::string& aLine,
                             const std::string& aFile,
                             int aLineNumber,
                             int aLevel)
{
    size_t colonPos = prs::strtrim(aLine).find(':');
    if (colonPos == 0 || colonPos == std::string::npos) {
        throw (Directive::Exception("Syntax_Error",
                                    aFile,
                                    aLineNumber));
    }
    prs::keyValuePair	kv = prs::lineToPair(aLine, ':');
    mType   = kv.second.empty() ? NonTerminal : Terminal;
    mFile   = aFile;
    mKey    = kv.first;
    mRest   = kv.second;
    mNline  = aLineNumber;
    mLevel  = aLevel;
}

//===[ Constructor: Directive Default ] ========================================
Directive::Directive(void) {}

//===[ Constructor: Directive ] ================================================
Directive::Directive(DirPartsIter& aDirectiveIter, DirPartsIter aDirectiveEnd)
{
    while (aDirectiveIter != aDirectiveEnd || sCurrentLevel != 0)
    {	
        if (aDirectiveIter == aDirectiveEnd
            || aDirectiveIter->mLevel < sCurrentLevel)
            return ;
        if (aDirectiveIter->mLevel != sCurrentLevel) {
            throw (Directive::Exception("Line_Not_Aligned",
                                        aDirectiveIter->mFile,
                                        aDirectiveIter->mNline));
        }
        if (aDirectiveIter->mType == NonTerminal)
            _processNonTerminalDirective(aDirectiveIter, aDirectiveEnd);
        else if (aDirectiveIter->mType == Terminal)
            _processTerminalDirective(aDirectiveIter);
    }
}

//===[ Destructor: ] ===========================================================
Directive::~Directive(void){}

/*******************************************************************************
    * Public methods :
*******************************************************************************/

//===[ Method: create & push to current directive ]=============================
void Directive::push(DirPartsIter &aDirectiveIter, DirPartsIter aDirectiveEnd)
{
    if (aDirectiveIter->mType == NonTerminal)
        _processNonTerminalDirective(aDirectiveIter, aDirectiveEnd);
    else if (aDirectiveIter->mType == Terminal)
        _processTerminalDirective(aDirectiveIter);
}

//===[ Method: get terminal directive ]========================================
std::vector<std::string>
Directive::getTerminal(const std::string& directiveKey) const
{
    std::map<std::string, std::vector<std::string> >::const_iterator it;

    it = mTerminal.find(directiveKey);
    if (it == mTerminal.end())
        return (std::vector<std::string>());
    return (it->second);
}

//===[ Method: get non terminal directive ]====================================
std::vector<Directive::SharedDir_ptr>
Directive::getNonTerminal(const std::string& directiveKey) const
{
    std::map<std::string, std::vector<SharedDir_ptr> >::const_iterator it;
    it = mNonTerminal.find(directiveKey);
    if (it == mNonTerminal.end())
        return (std::vector<SharedDir_ptr>());
    return (it->second);
}

/*******************************************************************************
    * Private methods :
*******************************************************************************/

//===[ Method: process a non terminal directive ]==============================
void Directive::_processNonTerminalDirective(DirPartsIter& aDirectiveIter,
                                             DirPartsIter aDirectiveEnd)
{
    ++sCurrentLevel;
    const std::string& directiveKey = aDirectiveIter->mKey;

    if (Dictionary::find(sHosts.back(), directiveKey) != Complex) {
        throw Directive::Exception("Invalid_Directive",
                                   aDirectiveIter->mFile,
                                   aDirectiveIter->mNline);
    }
    if ((aDirectiveIter + 1) == aDirectiveEnd ||
        (aDirectiveIter + 1)->mLevel < sCurrentLevel) {
        throw Directive::Exception("Empty_Directive",
                                  aDirectiveIter->mFile,
                                  aDirectiveIter->mNline);
    }
    sHosts.push_back(directiveKey);
    mNonTerminal[sHosts.back()].push_back(
                SharedDir_ptr(new Directive(++aDirectiveIter, aDirectiveEnd))
    );
    --sCurrentLevel;
    sHosts.pop_back();
}

//===[ _processNonTerminalDirective ] =========================================
void Directive::_processTerminalDirective(DirPartsIter& aDirectiveIter)
{
    std::string directiveKey = aDirectiveIter->mKey;
    DirType type = Dictionary::find(sHosts.back(), directiveKey);

    if (type != Simple && type != List) {
        throw Directive::Exception("Invalid_Directive",
                                    aDirectiveIter->mFile,
                                    aDirectiveIter->mNline);
    }

    if (type == Simple && mTerminal.count(directiveKey) != 0) {
        throw Directive::Exception("Duplicate_Simple_Directive",
                                    aDirectiveIter->mFile,
                                    aDirectiveIter->mNline);
    }

    if (type == List) {
        std::vector<std::string> values = prs::split(aDirectiveIter->mRest, ',');
        mTerminal[directiveKey].insert(mTerminal[directiveKey].end(),
                                       values.begin(),
                                       values.end());
    } else {
        mTerminal[directiveKey].push_back(aDirectiveIter->mRest);
    }

    ++aDirectiveIter;
}

/*******************************************************************************
    * Directive Exception :
*******************************************************************************/

//===[ Constructor: Directive::Exception ]======================================
Directive::Exception::Exception(const std::string& aMessage,
                                const std::string& aFile,
                                int aNline)
{
    char mNline[16];
    sprintf(mNline, "%d", aNline);
    mMessage =  "\e[1m\e[1;31m" + aMessage 	+ ": " 
                "\e[0m\e[3m"	+ aFile		+ 
                " ["			+ mNline 	+ "]";
}

//===[ Destructor: Directive::Exception ]=======================================
Directive::Exception::~Exception(void) throw(){}

//===[ What: Directive::Exception ]=============================================
const char* Directive::Exception::what() const throw()
{
    return (mMessage.c_str());
}
