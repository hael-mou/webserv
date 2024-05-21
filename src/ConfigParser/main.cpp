//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########        < main.cpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 20:50:27 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/21 21:52:26 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

# include "ConfigParser.hpp"

void	traverse(std::vector<IExpression *> list);
//====< main >==================================================================
int	main(void)
{
	ConfigParser				parser("test.yaml");
	std::vector<IExpression *>	list;

	try
	{
		list = parser.parse();
		traverse(list);
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl; 
	}
	return (EXIT_SUCCESS);
}

void	traverse(std::vector<IExpression *> list)
{
	std::vector<std::string>				tmp;

	for (unsigned int index = 0; index < list.size(); index++)
	{
		std::cout << "==== " << list[index]->getKey() << " ====" << std::endl;
		if (Grammar::getInstance().isDirKnown(list[index]->getKey()))
			traverse(dynamic_cast<NonTerminal *>(list[index])->getList());
//		dynamic_cast<Terminal *>(list[index])->getList();
	}
}
