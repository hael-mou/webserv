//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########< ParserUtils.cpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 11:53:26 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/21 16:47:09 by oezzaou

#include "ParserUtils.hpp"

/*******************************************************************************
	* ParserUtils :
*******************************************************************************/

//===[ strtrim : ]============================================================
std::string prs::strtrim(const std::string& input)
{
    size_t start = input.find_first_not_of(' ');
    if (std::string::npos == start)
        return (std::string());
    size_t end = input.find_last_not_of(' ');
    return (input.substr(start, end - start + 1));
}

//===[ lineToPair : ]=========================================================
prs::keyValuePair prs::lineToPair(const std::string& line, const char sep)
{
	prs::keyValuePair	pair;
	std::stringstream	ss(line);
	getline(ss, pair.first, sep);
	getline(ss, pair.second);
	return (keyValuePair(strtrim(pair.first), strtrim(pair.second)));
}

//===[ split : ]==============================================================
std::vector<std::string> prs::split(const std::string str, const char sep)
{
	std::vector<std::string>	arr;
	std::stringstream			ss(str);
	std::string					buff;

	while (getline(ss, buff, sep))
		arr.push_back(buff);
	return (arr);
}