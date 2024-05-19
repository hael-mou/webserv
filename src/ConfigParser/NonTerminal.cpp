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
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/19 22:22:08 by oezzaou
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

//====< isEmpty >===============================================================
bool	NonTerminal::isEmpty(std::vector<Directive> dir, unsigned int index)
{
	if (dir[index].getLevel() >= dir[index + 1].getLevel())
		throw (Exception("Error: Empty Block: " + dir[index].getKey()));
	return (false);
}

//====< interpret >=============================================================
IExpression	*NonTerminal::interpret(std::vector<Directive> dir, unsigned int& index)
{
	int						scope;

	this->isEmpty(dir, index);
	this->key = dir[index].getKey();
	scope = dir[index].getLevel();
	while (++index < dir.size() && dir[index].getLevel() > scope)
	{
		// check if it is a valid non_terminal
		// check if this directive can be in this scope
		if (dir[index].getLevel() - scope > 1)
			throw (Exception("Error: Not Aligned: " + dir[index].getKey()));
		list.push_back(clone(dir[index].getType())->interpret(dir, index));
	}
	return (this);
}
