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
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/17 22:35:53 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

#ifndef __NONTERMINAL_HPP__
# define __NONTERMINAL_HPP__

# include "Terminal.hpp"

class	NonTerminal : public IExpression
{
	private:
		std::string					key;
		std::vector<IExpression *>	list;

	public:
		~NonTerminal(void);

		IExpression *clone(std::vector<Directive> dir, unsigned int & index);
};

#endif /*__NONTERMINAL_HPP__*/
