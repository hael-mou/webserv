//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########   < Directive.cpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 12:58:37 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/19 14:44:29 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

# include "Directive.hpp"

//====< constructor >===========================================================
Directive::Directive(void)
{
}

//====< destructor >============================================================
Directive::~Directive(void)
{
}

//====< getType >===============================================================
int	Directive::getType(void) const
{
	return (this->type);
}

//====< setType >===============================================================
void	Directive::setType(const int type)
{
	this->type = type;
}

//====< getLevel >==============================================================
int	Directive::getLevel(void) const
{
	return (this->level);
}

//====< setLevel >==============================================================
void	Directive::setLevel(const int level)
{
	this->level = level;
}

//====< getKey >================================================================
std::string	Directive::getKey(void) const
{
	return (this->key);
}

//====< setKey >================================================================
void		Directive::setKey(const std::string key)
{
	this->key = key;
}

//====< getRest >===============================================================
std::string Directive::getRest(void) const
{
	return (this->rest);
}

//====< setRest >===============================================================
void	Directive::setRest(const std::string rest)
{
	this->rest = rest;
}
