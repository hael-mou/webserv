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
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/15 18:03:56 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)


#ifndef __IEXPRESSION_HPP__
# define __IEXPRESSION_HPP__

# include <iostream>
# include <vector>
# include "Directive.hpp"

class	IExpression
{
	public:
	virtual ~IExpression(void) {};

	virtual IExpression	*clone(std::vector<Directive> dir, int & index) = 0;
};

#endif /*__IEXPRESSION_HPP__*/
