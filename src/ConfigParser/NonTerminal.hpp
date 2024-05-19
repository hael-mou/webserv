//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+######## < NonTerminal.hpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 17:25:36 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/19 19:47:23 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

//====< NonTerminal >===========================================================
#ifndef __NONTERMINAL_HPP__
# define __NONTERMINAL_HPP__

# include "IExpression.hpp"

class	Terminal;

class	NonTerminal : public IExpression
{
	private:
		std::string					key;
		std::vector<IExpression *>	list;

	public:
		~NonTerminal(void);

		bool		isEmpty(std::vector<Directive> dir, unsigned int index);

		IExpression *interpret(std::vector<Directive> dir, unsigned int & index);
};

#endif /*__NONTERMINAL_HPP__*///================================================
