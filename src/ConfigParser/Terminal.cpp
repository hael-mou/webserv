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
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/19 19:35:27 by oezzaou
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

//====< isEmpty >===============================================================
bool	Terminal::isEmpty(std::vector<Directive> dir, unsigned int index)
{
	(void) index;
	(void) dir;
	return (false);
}

//====< interpret >=============================================================
IExpression	*Terminal::interpret(std::vector<Directive> dir, unsigned int & index)
{
	std::vector<std::string> val;

	this->key = dir[index].getKey();
	std::cout << "Terminal : " << key << std::endl;
	val = prs::split(dir[index].getRest(), ',');
	if (val.empty() == true)
		throw (std::out_of_range("Error: " + key + " has no value"));
	for (unsigned int i = 0; i < val.size(); ++i)
		list.push_back(prs::trim(val[i]));
	return (this);
}
