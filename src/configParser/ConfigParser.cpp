//  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣴⣶⣾⣿⣶⣶⣶⣶⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢠⡶⠻⠛⠟⠋⠉⠀⠈⠤⠴⠶⠶⢾⣿⣿⣿⣷⣦⠄⠀⠀⠀          𓐓  ConfigParser.hpp 𓐔           
//  ⠀⠀⠀⠀⠀⢀⠔⠋⠀⠀⠤⠒⠒⢲⠀⠀⠀⢀⣠⣤⣤⣬⣽⣿⣿⣿⣷⣄⠀⠀                                              
//  ⠀⠀⠀⣀⣎⢤⣶⣾⠅⠀⠀⢀⡤⠏⠀⠀⠀⠠⣄⣈⡙⠻⢿⣿⣿⣿⣿⣿⣦⠀  Student: oezzaou <oezzaou@student.1337.ma> 
//  ⢀⠔⠉⠀⠊⠿⠿⣿⠂⠠⠢⣤⠤⣤⣼⣿⣶⣶⣤⣝⣻⣷⣦⣍⡻⣿⣿⣿⣿⡀                                              
//  ⢾⣾⣆⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇                                              
//  ⠀⠈⢋⢹⠋⠉⠙⢦⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇     Created: 2024/05/15 11:58:00 by oezzaou
//  ⠀⠀⠀⠑⠀⠀⠀⠈⡇⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇     Updated: 2024/05/25 14:05:50 by hael-mou
//  ⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢀⣾⣿⣿⠿⠟⠛⠋⠛⢿⣿⣿⠻⣿⣿⣿⣿⡿⠀                                             
//  ⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⢠⣿⣟⣭⣤⣶⣦⣄⡀⠀⠀⠈⠻⠀⠘⣿⣿⣿⠇⠀                                            
//  ⠀⠀⠀⠀⠀⠱⠤⠊⠀⢀⣿⡿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⠏⠀⠀                             𓆩♕𓆪      
//  ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠘⢧⡀⠀⠀⠸⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠐⠋⠀⠀⠀                        𓄂 oussama ezzaou𓆃
//  ⠀⠀⠀⠀⠀⠘⠄⣀⡀⠸⠓⠀⠀⠀⠠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                              

#include "ConfigParser.hpp"

/*******************************************************************************
    * Construction :
*******************************************************************************/

//===[ Constructor: ]===========================================================
ConfigParser::ConfigParser(void){}

//===[ Destructor: ]============================================================
ConfigParser::~ConfigParser(void)
{
    while (mFiles.empty() == false) {
        _CloseLastOpenFile();
    }
}

/*******************************************************************************
    * Public Methods :
*******************************************************************************/

//===[ Method: open a new file ]================================================
void ConfigParser::openFile(const std::string& aFileName, int aStartColumn)
{
    if (_isFileAlreadyOpen(aFileName) == true)
        throw (Exception("File_Already_Open", aFileName));
    
    std::fstream*	stream = new std::fstream(aFileName.c_str(), std::ios::in);
    if (!stream->is_open()) {
        delete (stream);
        throw (Exception("Can't_Open_File", aFileName));
    }
    mFiles.push_back(File(aFileName, stream));
    mStartColumn.push_back(aStartColumn);
    mlineCount.push_back(0);
}

//===[ Method: parse the configuration ]========================================
mem::shared_ptr<Directive>	ConfigParser::parse(void)
{
	mem::shared_ptr<Directive>	globalDir;
	std::vector<DirectivePart>	dirParts;
    std::string					line;

	while (!mFiles.empty())
	{
		while (std::getline(*(mFiles.back().second), line))
		{
            ++mlineCount.back();
            _processLine(line, globalDir, dirParts);
        }
        if (mFiles.size() == 1 && dirParts.empty() == true)
            throw (Exception("Empty_Configuration", mFiles.back().first));
        _CloseLastOpenFile();
    }
	DirPartSet::iterator iter = dirParts.begin();
	globalDir->push(iter, dirParts.end());
	return (globalDir);
}

/*******************************************************************************
    * Private Methods :
*******************************************************************************/

//==[ Method: Process a line ]==================================================
void	ConfigParser::_processLine(std::string& aLine,
                                  Dir_ptr& aGlobalDir,
                                  DirPartSet& aDirParts)
{
	aLine = aLine.substr(0, aLine.find_first_of('#'));
	if (prs::strtrim(aLine).empty())
		return ;
	int level = _getLevel(aLine);
	if (_includeDirective(aLine, level) == true)
        return ;
	if (_isValidDirective(aDirParts, level) == true) {
		DirPartSet::iterator iter = aDirParts.begin();
		aGlobalDir->push(iter, aDirParts.end());
		aDirParts.clear();
	}
	std::string file = mFiles.back().first;
	int lineNum = mlineCount.back();
	aDirParts.push_back(DirectivePart(aLine, file, lineNum, level));
}

//===[ Method: check if a file is already open ]================================
bool ConfigParser::_isFileAlreadyOpen(const std::string& aFileName) const
{
    std::vector<File>::const_iterator it;
    for (it = mFiles.begin(); it != mFiles.end(); ++it) {
        if (it->first == aFileName)
            return (true);
    }
    return (false);
}

//===[ Method: get the level of a line ]========================================
int	ConfigParser::_getLevel(const std::string& aLine)
{
    std::vector<int>::iterator	iter;
    int							column;

    column = aLine.find_first_not_of(' ') + mStartColumn.back();
    iter = find(mLevels.begin(), mLevels.end(), column);
    if (mLevels.empty() == false && iter != mLevels.end())
        return (iter - mLevels.begin());
    mLevels.push_back(column); 
    return (static_cast<int>(mLevels.size()) - 1);
}

//===[ Method: check if a line is a valid directive ]===========================
bool ConfigParser::_isValidDirective(const DirPartSet &aDirParts, int aLevel) const
{
    if (aDirParts.size() == 1 && aDirParts[0].mType == Terminal)
    {
        if (aDirParts[0].mLevel > 0)
        return (true);
    }
    return (!aDirParts.empty() && mLevels[aLevel] <= mLevels[0]);
}

//===[ Method: handle an include directive ]====================================
bool ConfigParser::_includeDirective(const std::string& aLine, int aLevel)
{
    if (aLine.find("include") == std::string::npos)
        return (false);
    prs::keyValuePair kv = prs::lineToPair(aLine, ':');
    if (kv.first != "include" || kv.second.empty())
        return (false);
    if (kv.second[0] != '/' || kv.second[0] != '.')
    {
        std::string curFile = mFiles.back().first;
        kv.second = curFile.substr(0, curFile.find_last_of('/') + 1) + kv.second;
    }
    openFile(kv.second, mLevels[aLevel]);
    return (true);
}

//===[ Method: close the last open file ]======================================
void ConfigParser::_CloseLastOpenFile(void)
{
    delete (mFiles.back().second);
    mFiles.pop_back();
    mStartColumn.pop_back();
    mlineCount.pop_back();
}

/*******************************************************************************
    * ConfigParser Exception :
*******************************************************************************/

//===[ Constructor: Exception ]=================================================
ConfigParser::Exception::Exception(std::string aMessage, std::string aLine)
{
    mMessage =  "\e[1m\e[1;31m" + aMessage 	+ ": " 
                "\e[0m\e[3m"	+ aLine;
}

//===[ Destructor: Exception ]==================================================
ConfigParser::Exception::~Exception() throw() {};

//===[ Method: what ]===========================================================
const char* ConfigParser::Exception::what() const throw()
{
    return (mMessage.c_str());
}
