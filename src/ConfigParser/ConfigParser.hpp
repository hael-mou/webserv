//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########< ConfigParser.hpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 11:58:00 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/17 20:00:46 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)


#ifndef __CONFIGPARSER_HPP__
# define __CONFIGPARSER_HPP__

# include <fstream>
# include <sstream>
# include "Directive.hpp"
# include "NonTerminal.hpp"
# include "Terminal.hpp"

typedef std::vector<Directive>	v_dir;

class	ConfigParser
{
	private:
		std::string					fileName;
		std::fstream				fileStream;

		std::vector<int>			level;
		std::vector<IExpression *>	list;

		int					getDirType(std::string line);
		bool 				isAligned(Directive prev, Directive curr);
		int					getAlignment(std::string line);
	
	public:
		ConfigParser(void);
		ConfigParser(std::string fileName);
		~ConfigParser(void);

		IExpression					*parseBlock(std::vector<Directive> dir);
		Directive					parseLine(std::string line, v_dir dirs, int level);
		std::vector<IExpression *>	parse(void);
};

#endif /*__CONFIGPARSER_HPP__*/
