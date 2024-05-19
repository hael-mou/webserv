//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########    < Terminal.hpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 17:27:40 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/19 22:24:19 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

//====< Terminal >==============================================================
#ifndef __TERMINAL_HPP__
# define __TERMINAL_HPP__

# include "IExpression.hpp"
# include "Parser.hpp"

class	Terminal : public IExpression
{
	private:
		std::string					key;
		std::vector<std::string>	list;

	public:
		~Terminal(void);

		bool		isEmpty(std::vector<Directive> dir, unsigned int index);

		IExpression	*interpret(std::vector<Directive> dir, unsigned int & index);
};

#endif /*__TERMINAL_HPP__*///===================================================
