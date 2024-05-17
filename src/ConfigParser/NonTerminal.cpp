//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+######## < NonTerminal.cpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 17:26:36 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/17 22:40:53 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

# include "NonTerminal.hpp"

//====< destructor >============================================================
NonTerminal::~NonTerminal(void)
{
}

//====< clone >=================================================================
IExpression	*NonTerminal::clone(std::vector<Directive> dir, unsigned int& index)
{
	int		scope;

	this->key = dir[index++].getKey();
	std::cout << "NON_TERMINAL : " << this->key << std::endl; 
	scope = dir[index].getLevel();
	while (index < dir.size() && dir[index].getLevel() >= scope)
	{
		if (dir[index].getType() == TERMINAL)
			list.push_back((new Terminal())->clone(dir, index));
		if (dir[index].getType() == NON_TERMINAL)
			list.push_back((new NonTerminal())->clone(dir, index));
	}
	return (this);
}
