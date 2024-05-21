//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+######## < IExpression.hpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 17:28:34 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/21 15:25:44 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

//====< IExpression >===========================================================
#ifndef __IEXPRESSION_HPP__
# define __IEXPRESSION_HPP__

# include "Grammar.hpp"
# include "Directive.hpp"
# include "Exception.hpp"

typedef unsigned int	uint;

class	IExpression
{
	public:
	virtual ~IExpression(void) {};

	virtual	std::string	getKey(void) const = 0;

	virtual IExpression	*interpret(std::vector<Directive> dir, uint& index) = 0;
};

IExpression	*clone(int dirType);

#endif /*__IEXPRESSION_HPP__*///================================================
