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
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/21 15:16:24 by oezzaou
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

		std::string					getKey(void) const;
		std::vector<IExpression *>	getList(void) const;

		IExpression *interpret(std::vector<Directive> dir, uint & index);
};

#endif /*__NONTERMINAL_HPP__*///================================================
