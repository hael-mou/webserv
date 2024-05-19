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
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/19 19:32:33 by oezzaou
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

# include "Directive.hpp"
# include "Exception.hpp"
# include <vector>

class	IExpression
{
	public:
	virtual ~IExpression(void) {};

	virtual	bool		isEmpty(std::vector<Directive> dir, unsigned int index) = 0;

	virtual IExpression	*interpret(std::vector<Directive> dir, unsigned int & index) = 0;
};

IExpression	*clone(int dirType);

#endif /*__IEXPRESSION_HPP__*///================================================
