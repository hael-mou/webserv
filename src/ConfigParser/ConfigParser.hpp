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
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/19 20:02:02 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

//====< ConfigParser >==========================================================
#ifndef __CONFIGPARSER_HPP__
# define __CONFIGPARSER_HPP__

# include "NonTerminal.hpp"
# include "Terminal.hpp"
# include "Directive.hpp"
# include "Exception.hpp"
# include "Parser.hpp"

typedef std::vector<IExpression *>::iterator	vii;
typedef std::vector<Directive>					vd;

class	ConfigParser
{
	private:
		std::fstream				fileStream;
		std::string					fileName;
		std::vector<int>			level;
		std::vector<IExpression *>	list;

		int							getDirectiveType(std::string line);
		int							getLevel(std::string line);
	
	public:
		ConfigParser(void);
		ConfigParser(std::string fileName);
		~ConfigParser(void);

		Directive					parseLine(std::string line, int level);
		IExpression					*parseBlock(std::vector<Directive> dir, int scope);

		std::vector<IExpression *>	parse(void);
};

IExpression	*clone(int dirType);

#endif /*__CONFIGPARSER_HPP__*///===============================================
