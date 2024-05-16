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
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/15 12:59:41 by oezzaou
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


Directive::Directive(void)
{
}

Directive::~Directive(void)
{
}

int	Directive::getType(void) const
{
	return (this->type);
}

void	Directive::setType(int type)
{
	this->type = type;
}

int	Directive::getLevel(void) const
{
	return (this->level);
}

void	Directive::setLevel(int level)
{
	this->level = level;
}

std::string	Directive::getKey(void) const
{
	return (this->key);
}

void		Directive::setKey(const std::string key)
{
	this->key = key;
}
