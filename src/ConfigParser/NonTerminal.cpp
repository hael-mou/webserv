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

//====< interpret >=============================================================
IExpression	*NonTerminal::interpret(std::vector<Directive> dir, unsigned int& index)
{
	int						scope;

	scope = dir[index].getLevel();
	this->key = dir[index].getKey();
	if (index >= dir.size() - 1 || scope >= dir[index + 1].getLevel())
		throw (Exception("Error: Empty Block: " + dir[index].getKey()));
	while (index + 1 < dir.size() && dir[index + 1].getLevel() > scope)
	{
		Grammar::getInstance().isSubDirKnown(key, dir[++index].getKey());
		if (dir[index].getLevel() - scope > 1)
			throw (Exception("Error: Not Aligned: " + dir[index].getKey()));
		list.push_back(clone(dir[index].getType())->interpret(dir, index));
	}
	return (this);
}
