//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########      < KeyValueParser.hpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oussama <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/04/05 16:17:58 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/17 21:21:35 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

//====< KeyValueParser Class >==================================================
#ifndef __PARSER_HPP__
# define __PARSER_HPP__

# include <sstream>
# include <iostream>
# include <string>
# include <fstream>
# include <map>
# include <vector>
# include "Date.hpp"
# include "FSM.hpp"
# include "Exception.hpp"

namespace	prs
{

	template <class p1, class p2, char sep = '|'>
	class	KeyValueParser
	{
		private:
			std::string		fileName;

		public:
			std::fstream	fileStream;

			KeyValueParser(void);
			KeyValueParser(std::fstream fileStream);
			KeyValueParser(std::string fileName);
			~KeyValueParser(void);

			std::map<p1, p2>	parseFile(void);
			std::pair<p1, p2>	parseNextLine(void);
			std::string			skipLine(void);
			bool				eof(void);
	};


	std::string		parse(std::string value, std::string sValue);
	int				parse(int value, std::string sValue);
	double			parse(double value, std::string sValue);

	std::string					getNextLine(std::istream & stream);
	std::string					trim(std::string str);

	std::vector<std::string>	split(const std::string s, const char sep);

	std::pair<std::string, std::string>	lineToPair(std::string line, const char sep);

# include "KeyValueParser.tpp"

//	std::string 	split(std::string str, std::string sep);

};

#endif /*__PARSER_HPP__*/
