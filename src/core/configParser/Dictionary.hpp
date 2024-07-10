/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Dictionary header file ]                                             #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-21                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __DICTIONARY_HPP__
# define   __DICTIONARY_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "typedefs.hpp"
# include "Utils.hpp"

# include <iostream>
# include <fstream>

/*******************************************************************************
    * defines :
*******************************************************************************/
#define CONFIG_FILE_PATH  "src/core/configParser/Dictionary.conf"

/*******************************************************************************
    * Dictionary Static Class :
*******************************************************************************/

enum DirType { Inline = 0, List, Block, Invalid };

class Dictionary
{
public:
    typedef std::pair<std::string, DirType>                TerminalDirPair;
    typedef std::vector<TerminalDirPair>                   NonTerminalDirVector;
    typedef std::map<std::string, NonTerminalDirVector>    GrammarMap;

    static DirType  find(const_string& aDir, const_string& aSubDir);

private:
    static GrammarMap sGrammar;

    Dictionary(void);

    static GrammarMap   _initializeGrammar(const_string aFilePath);
    static bool         _isValidKey(const_string& aLine);
    static void         _processValue(const_string& aLine, const_string& aKey,
                                      GrammarMap& aGrammar);
};

#endif /* __DICTIONARY_HPP__ */
