# include "Grammar.hpp"

//====< instance >=======================================
Grammar *Grammar::instance = NULL;

//====< constructor >====================================
Grammar::Grammar(void)
{
	bool re = this->addSubDirective("http", "server");
	std::cout << "re : " << re << std::endl;
	re = this->addSubDirective("http", "listen");
	std::cout << "re : " << re << std::endl;
	re = this->addSubDirective("server", "listen");
	std::cout << "re : " << re << std::endl;
}

//====< getInstance >====================================
Grammar & Grammar::getInstance(void)
{
	if (instance == NULL)
		instance = new Grammar();
	return (*instance);
}

//====< addDirective >===================================
bool	Grammar::addDirective(std::string dir)
{
	std::pair<std::string, std::vector<std::string> > pair;

	if (!grammar.empty() && grammar.find(dir) != grammar.end())
		return (false);
	pair.first = dir;
	pair.second = std::vector<std::string>();
	grammar.insert(pair);
	return (true);
}

//====< addSubDirective >===================================
bool	Grammar::addSubDirective(std::string dir, std::string subDir)
{
	std::map<std::string, std::vector<std::string> >::iterator iter;
	std::vector<std::string>		tmp;

	this->addDirective(dir);
	iter = grammar.find(dir);
	tmp = iter->second;
	if (!tmp.empty() && find(tmp.begin(), tmp.end(), subDir) != tmp.end())
		return (false);
	iter->second.push_back(subDir);	
	return (true);
}

//====< isDirKnown >===================================================================
bool	Grammar::isDirKnown(std::string dir)
{
	if (grammar.find(dir) == grammar.end())
		return (false);
	return (true);
}

//====< isSubDirKnown >================================================================
bool	Grammar::isSubDirKnown(std::string dir, std::string subDir)
{
	std::vector<std::string>	tmp;

	if (this->isDirKnown(dir) == false)
		throw (Exception("Error: Unknown Directive: " + dir));
	tmp = grammar.find(dir)->second;
	if (find(tmp.begin(), tmp.end(), subDir) == tmp.end())
		throw (Exception("Error: Unknown subDirective: " + subDir));
	return (true);
}
