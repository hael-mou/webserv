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

//====< interpret >=============================================================
IExpression	*Terminal::interpret(std::vector<Directive> dir, unsigned int & index)
{
	std::vector<std::string>		 val;

	std::cout << "Terminal : " << dir[index].getRest() << std::endl;
	this->key = dir[index].getKey();
	if (Grammar::getInstance().isDirKnown(this->key) == true)
		throw (Exception("Error: Terminal Expression: " + key));
	val = prs::split(dir[index].getRest(), ',');
	/*for (unsigned int i = 0; i < val.size(); i++)
	{
		val[i] = prs::trim(val[i]);
		if (val[i].empty() == true)
			throw (Exception("Error: Empty Value: " + key));
		std::cout << "val : " << val[i] << std::endl;
		list.push_back(val[i]);
	}*/
	return (this);
}
