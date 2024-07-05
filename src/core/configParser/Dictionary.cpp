/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Dictionary source file ]                                             #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-21                                                   #
#                                                                              #
** ************************************************************************* **/

#include "Dictionary.hpp"

/*******************************************************************************
    * static Variables :
*******************************************************************************/
Dictionary::GrammarMap
Dictionary::sGrammar = Dictionary::_initializeGrammar(CONFIG_FILE_PATH);

/*******************************************************************************
     * public Methods :
*******************************************************************************/

//===[ Method: getGrammar ]=====================================================
DirType Dictionary::find(const_string& aDir, const_string& aSubDir)
{
    ComplexDirPairVector grammar = sGrammar[aDir];

    for (size_t i = 0; i < grammar.size(); ++i)
    {
        if (grammar[i].first == aSubDir)
            return (grammar[i].second);
     }
     return (Invalid);
}

/*******************************************************************************
    * Private Methods :
*******************************************************************************/

//===[ Method: initGrammar ]====================================================
Dictionary::GrammarMap Dictionary::_initializeGrammar(const_string aFilePath)
{
    Dictionary::GrammarMap grammar;
    std::ifstream configFile(aFilePath.c_str());

    if (!configFile.is_open())
    {
        Logger::log("ERROR", "\e[1;31mGrammar_File_Failed_To_Open: \e[0m"
                + aFilePath + "\n", 2);
        std::exit(EXIT_FAILURE);
    }

    std::string currentKey, line;
    while (std::getline(configFile, line))
    {
        line = utls::strtrim(line);
        if (line.empty())
            continue;

        if (_isValidKey(line))
            currentKey = line.substr(0, line.length() - 1);
        else if (!currentKey.empty())
            _processValue(line, currentKey, grammar);
    }

    configFile.close();
    return (grammar);
}

//===[ Method: isValidKey ]=====================================================
bool Dictionary::_isValidKey(const_string& line)
{
    size_t len = line.length();
    if (len > 1 && line[len - 1] == ':')
        return (true);
    return (false);
}

//===[ Method: processValue ]===================================================
void Dictionary::_processValue(const_string& aLine,
                               const_string& aKey,
                               GrammarMap& aGrammar)
{
    StringPair KeyValue = utls::lineToPair(aLine, '=');
    if (KeyValue.first.empty())
        return;
    KeyValue.second = utls::toLower(KeyValue.second);
    DirType terminalType = KeyValue.second == "list" ? List :
        (KeyValue.second == "complex" ? Complex : Simple);
    aGrammar[aKey].push_back(std::make_pair(KeyValue.first, terminalType));
}
