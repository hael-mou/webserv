//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########    < Terminal.cpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 17:27:00 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/21 21:39:48 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

# include "Terminal.hpp"

//====< destructor >============================================================
Terminal::~Terminal(void)
{
}

//====< getKey >================================================================
std::string	Terminal::getKey(void) const
{
	return (this->key);
}

//====< getList >===============================================================
std::vector<std::string>	Terminal::getList(void) const
{
	return (this->list);
}

//====< interpret >=============================================================
IExpression	*Terminal::interpret(std::vector<Directive> dir,  uint & index)
{
	std::vector<std::string>		val;

	this->key = dir[index].getKey();
	if (Grammar::getInstance().isDirKnown(this->key) == true)
		throw (Exception("Error: Terminal Expression: " + key));
	val = prs::split(dir[index].getRest(), ',');
	for (unsigned int index = 0; index < val.size(); index++)
	{
		val[index] = prs::trim(val[index]);
		if (val[index].empty() == true)
			throw (Exception("Error: Empty Value: " + key));
		list.push_back(val[index]);
	}
	return (this);
}
