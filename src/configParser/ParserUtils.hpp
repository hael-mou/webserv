//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########< ParserUtils.hpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 11:58:00 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/21 14:05:50 by oezzaou

#ifndef   __PARSERUTILS_HPP__
# define   __PARSERUTILS_HPP__

/*******************************************************************************
	* Includes :
*******************************************************************************/
# include <string>
# include <sstream>
# include <vector>

/*******************************************************************************
	* ParserUtils :
*******************************************************************************/

namespace prs
{
	typedef std::pair<std::string, std::string>		keyValuePair;

	std::string   strtrim(const std::string& str);
	keyValuePair  lineToPair(const std::string& line, const char sep);
	std::vector<std::string> split(const std::string str, const char sep);

};

#endif /* __PARSERUTILS_HPP__ */
