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
# include <map>

class	Grammar
{
	private:
		std::map<std::string, std::vector<std::string> > grammar;
	
	public:
		static Grammar & getInstance(void);
		// add Directive
		// add SubDir
		// SearchDir
		// SearchSubDir
};

#endif /*__GRAMMAR_HPP__*///====================================================
