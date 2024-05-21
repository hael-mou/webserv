//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########< ConfigParser.cpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 11:53:26 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/19 22:36:19 by oezzaou
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

//====< constructor >===========================================================
ConfigParser::ConfigParser(void)
{
}

//====< constructor >===========================================================
ConfigParser::ConfigParser(std::string fileName)
{
	this->fileName = fileName;
	fileStream.open(fileName, std::ios::in);
}

//====< ~ConfigParser >=========================================================
ConfigParser::~ConfigParser(void)
{
	fileStream.close();
	for (vii i = list.begin(); i != list.end(); ++i)
		delete *i;
}

//====< detecDirtType >=========================================================
int	ConfigParser::getDirectiveType(std::string line)
{
	int				position;

	line = prs::trim(line);
	position = line.find(':');
	if (position <= 0 || std::count(line.begin(), line.end(), ':') > 1)
		throw (Exception("Syntax Error: Invalid Directive: " + line));
	return ((position == (int) line.length() - 1) ? NON_TERMINAL : TERMINAL);
}

//====< getLevel >==========================================================
int ConfigParser::getLevel(std::string line)
{
	std::vector<int>::iterator	iter;
	int							column;

	column = line.find_first_not_of(' ');
	iter = find(level.begin(), level.end(), column);
	if (!level.empty() && iter != level.end())
		return (iter - level.begin());
	level.push_back(column); 
	return (static_cast<int>(level.size()) - 1);
}

//====< parseLine >=============================================================
Directive ConfigParser::parseLine(std::string line, int level)
{
	std::pair<std::string, std::string>	pair;
	Directive							dir;

	dir.setType(getDirectiveType(line));
	dir.setLevel(level);
	pair = prs::lineToPair(line, ':');
	dir.setKey(pair.first);
	dir.setRest(pair.second);
	return (dir);
}

//====< parseBlock >============================================================
IExpression	*ConfigParser::parseBlock(std::vector<Directive> dir, int scope)
{
	unsigned int	index = 0;

	(void) scope;	
	if (dir.empty() == true)
		throw (Exception("Error: Empty config file"));
	if (dir[index].getLevel() > 0)
	{
		std::cout << "kkkkkkkkkkkkkk" << std::endl;
		throw (Exception("Error: Not aligned|: " + dir[index].getKey()));
	}
	return (clone(dir[index].getType())->interpret(dir, index));
}

//====< parse >=================================================================
std::vector<IExpression *> ConfigParser::parse(void)
{
	std::vector<Directive>		dir;
	std::string					line;
	int							level;

	while (getline(fileStream, line))
	{
		if (line.empty() == true)
			continue ;
		level = getLevel(line);
		if (!dir.empty() && level == 0)
		{
			list.push_back(parseBlock(dir, -1));
			dir = std::vector<Directive>();
		}
		dir.push_back(parseLine(line, level));
	}
	list.push_back(parseBlock(dir, -1));
	return (list);
}


























//=============================
IExpression	*clone(int dirType)
{
	if (dirType == TERMINAL)
		return (new Terminal());
	if (dirType == NON_TERMINAL)
		return (new NonTerminal());
	return (NULL);
}
