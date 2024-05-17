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
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/17 22:30:19 by oezzaou
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

//void	AST(std::vector<IExpression *> list);

//====< main >==================================================================
int	main(void)
{
	ConfigParser				parser("test.yaml");
	std::vector<IExpression *>	list;

	list = parser.parse();
//	AST(list);
	return (EXIT_SUCCESS);
}

//====< AST >===================================================================
/*void	AST(std::vector<IExpression *> list)
{
	for (unsigned int index = 0; index < list.size(); index++)
	{
		if (list[index]->getType() == NON_TERMINAL)
		{
			std::cout << "NonTerminal : " << list[index]->getKey() << std::endl;
			AST(list[index]);
		}
		if (list[index]->getType() == TERMINAL)
			std::cout << "Terminal : " << list[index]->getKey() << std::endl;
	}
}*/
