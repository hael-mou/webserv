//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########     < Grammar.cpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/21 10:08:48 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/21 16:10:43 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

# include "Grammar.hpp"

//====< instance >==============================================================
Grammar *Grammar::instance = NULL;

//====< constructor >===========================================================
Grammar::Grammar(void)
{
	this->addSubDirective("http", "server");
	this->addSubDirective("http", "listen");
	this->addSubDirective("server", "listen");
}

//====< getInstance >===========================================================
Grammar & Grammar::getInstance(void)
{
	if (instance == NULL)
		instance = new Grammar();
	return (*instance);
}

//====< addDirective >==========================================================
bool	Grammar::addDirective(std::string dir)
{
	if (grammar.find(dir) != grammar.end())
		return (false);
	grammar.insert(g_pair(dir, std::vector<std::string>()));
	return (true);
}

//====< addSubDirective >=======================================================
bool	Grammar::addSubDirective(std::string dir, std::string subDir)
{
	std::map<std::string, std::vector<std::string> >::iterator	iter;
	std::vector<std::string>									tmp;

	this->addDirective(dir);
	iter = grammar.find(dir);
	tmp = iter->second;
	if (find(tmp.begin(), tmp.end(), subDir) != tmp.end())
		return (false);
	return (iter->second.push_back(subDir), true);
}

//====< isDirKnown >============================================================
bool	Grammar::isDirKnown(std::string dir)
{
	if (grammar.find(dir) == grammar.end())
		return (false);
	return (true);
}

//====< isSubDirKnown >=========================================================
bool	Grammar::isSubDirKnown(std::string dir, std::string subDir)
{
	std::vector<std::string>		tmp;

	if (this->isDirKnown(dir) == false)
		throw (Exception("Error: Unknown Directive: " + dir));
	tmp = grammar.find(dir)->second;
	if (find(tmp.begin(), tmp.end(), subDir) == tmp.end())
		throw (Exception("Error: Unknown subDirective: " + subDir));
	return (true);
}
