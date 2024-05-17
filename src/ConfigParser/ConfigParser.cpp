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
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/17 22:39:11 by oezzaou
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

ConfigParser::ConfigParser(void)
{
}

ConfigParser::ConfigParser(std::string fileName)
{
	this->fileName = fileName;
	fileStream.open(fileName, std::ios::in);
}

//====< ~ConfigParser >=========================================================
ConfigParser::~ConfigParser(void)
{
	fileStream.close();
}

//====< detecDirtType >=========================================================
int	ConfigParser::getDirType(std::string line)
{
	int				position;

	line = prs::trim(line);
	position = line.find(':');
	if (position <= 0 || std::count(line.begin(), line.end(), ':') > 1)
		throw (std::out_of_range("Invalid Directive: " + line));
	return ((position == (int) line.length() - 1) ? NON_TERMINAL : TERMINAL);
}

//====< isAligned >=============================================================
bool	ConfigParser::isAligned(Directive prev, Directive curr)
{
	if (prev.getType() == NON_TERMINAL && prev.getLevel() > curr.getLevel())
		throw (std::out_of_range("not aligned"));
	if (prev.getType() == TERMINAL && prev.getLevel() != curr.getLevel())
		throw (std::out_of_range("not aligned"));
	return (true);
};

//====< getAlignment >==========================================================
int ConfigParser::getAlignment(std::string line)
{
	int							column;
	std::vector<int>::iterator	element;

	column = line.find_first_not_of(' ');
	if (level.size() == 0 || column > level.back())
		level.push_back(column);
	if (level.size() != 0 && column < level.back())
	{
		element = std::find(level.begin(), level.end(), column); 
		if (element == level.end())
			throw (std::out_of_range("Invalid level : " + line));
		return (element - level.begin());
	}
	return (static_cast<int>(level.size() - 1));
}

//====< parseLine >=============================================================
Directive ConfigParser::parseLine(std::string line, v_dir dirs, int level)
{
	Directive							dir;
	std::pair<std::string, std::string>	pair;

	dir.setType(getDirType(line));
	dir.setLevel(level);
	if (dir.getType() == TERMINAL && dirs.size() > 0)
		isAligned(dirs.back(), dir);
	pair = prs::lineToPair(line, ':');
	dir.setKey(pair.first);
	dir.setRest(pair.second);
	return (dir);
}

//====< parseBlock >============================================================
IExpression	*ConfigParser::parseBlock(std::vector<Directive> dir)
{
	unsigned int	index = 0;
	
	if (dir.size() == 1)
		throw (std::out_of_range("Incomplete block"));
	return ((new NonTerminal())->clone(dir, index));
}

//====< parse >=================================================================
std::vector<IExpression *> ConfigParser::parse(void)
{
	std::string		line;
	int				level;
	v_dir			dir;

	while (getline(fileStream, line))
	{
		if (line.empty() == true)
			continue ;
		level = getAlignment(line);
		if (dir.size() > 0 && level == 0)
		{
			list.push_back(parseBlock(dir));
			dir = std::vector<Directive>();
		}
		dir.push_back(parseLine(line, dir, level));
	}
	list.push_back(parseBlock(dir));
	return (list);
}
