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
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/21 17:39:53 by oezzaou
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
	for (unsigned int index = 0; index < list.size(); index++)
		delete list[index];
}

//====< getKey >================================================================
std::string	NonTerminal::getKey(void) const
{
	return (this->key);
}

//====< getList >===============================================================
std::vector<IExpression *>	NonTerminal::getList(void) const
{
	return (this->list);
}

//====< interpret >=============================================================
IExpression	*NonTerminal::interpret(std::vector<Directive> dir, uint & index)
{
	int						scope;

	scope = dir[index].getLevel();
	this->key = dir[index].getKey();
	if (index + 1 >= dir.size() || scope >= dir[index + 1].getLevel())
		throw (Exception("Error: Empty Block: " + dir[index].getKey()));
	while (index + 1 < dir.size() && dir[index + 1].getLevel() > scope)
	{
		if (dir[++index].getLevel() - scope > 1)
			throw (Exception("Error: Not Aligned: " + dir[index].getKey()));
		Grammar::getInstance().isSubDirKnown(key, dir[index].getKey());
		list.push_back(clone(dir[index].getType())->interpret(dir, index));
	}
	return (this);
}
