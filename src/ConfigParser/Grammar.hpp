//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########     < Grammar.cpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/19 22:46:44 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/19 22:51:02 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

//====< Grammar >===============================================================
#ifndef __GRAMMAR_HPP__
# define __GRAMMAR_HPP__

# include <iostream>
# include <vector>
# include <map>
# include "Exception.hpp"

class	Grammar
{
	private:
		Grammar(void);
		
		static Grammar	*instance;
		std::map<std::string, std::vector<std::string> > grammar;

	public:
		static Grammar & getInstance(void);
	
		bool	addDirective(std::string dir);
		bool	addSubDirective(std::string dir, std::string subDir);
	
		bool	isDirKnown(std::string dir);	
		bool	isSubDirKnown(std::string dir, std::string subDir);
};

#endif /*__GRAMMAR_HPP__*///====================================================
