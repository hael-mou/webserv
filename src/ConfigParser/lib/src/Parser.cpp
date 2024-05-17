//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########      < Parser.cpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/03/31 00:51:08 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/17 21:21:18 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

# include "Parser.hpp"

//====< trim >==================================================================
std::string prs::trim(std::string str)
{
	int		start;
	int		end;

	start = 0;
	end = str.length() - 1;
	while (start <= end && str[start] == ' ')
		start++;
	while (end >= 0 && str[end] == ' ')
	  	end--;
	return (str.substr(start, end - start + 1));
}

//====< parse >=================================================================
int	prs::parse(int value, std::string sValue)
{
	std::stringstream	ss(sValue);
	int					type;

	type = FSM::detectType(sValue);
	if (type == START)
		throw (Exception("Parse Error: Empty value > " + sValue));
	if (type != INT && type != DOUBLE)
		throw (Exception("Parse Error: Not a Integer value > " + sValue));
	if ((ss >> value) == NULL)
		throw (Exception("Error: Too large number for Double"));
	return (value);
}

//====< parse >=================================================================
double	prs::parse(double value, std::string sValue)
{
	std::stringstream	ss(sValue);
	int					type;

	type = FSM::detectType(sValue);
	if (type == START)
		throw (Exception("Parse Error: Empty value > " + sValue));
	if (type != INT && type != DOUBLE)
		throw (Exception("Parse Error: Not a double value > " + sValue));
	if ((ss >> value) == NULL)
		throw (Exception("Error: Too large number for Double"));
	return (value);
}

//====< parse >=================================================================
std::string	prs::parse(std::string value, std::string sValue)
{
	value = sValue;
	if (value.empty() == true)
		throw (Exception("Parse Error: Empty string"));
	return (value);
}

//====< getNextLine >===========================================================
std::string	prs::getNextLine(std::istream & stream)
{
	std::string	line;

	if (stream == NULL)
		throw (Exception("Stream Error: Invalid Stream."));
	getline(stream, line, '\n');
	return (line);
}

//====< split >=================================================================
std::vector<std::string> prs::split(const std::string s, const char sep)
{
	std::vector<std::string>	arr;
	std::stringstream			ss(s);
	std::string					buff;

	while (getline(ss, buff, sep))
		arr.push_back(buff);
	return (arr);
}

//====< lineToPair >============================================================
std::pair<std::string, std::string>	prs::lineToPair(std::string line, const char sep)
{
	std::stringstream					ss(line);
	std::pair<std::string, std::string> pair;

	getline(ss, pair.first, sep);
	getline(ss, pair.second);
	return (std::pair<std::string, std::string>(trim(pair.first), trim(pair.second)));
}
