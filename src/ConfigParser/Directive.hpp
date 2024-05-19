//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########   < Directive.hpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/05/15 12:54:33 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/19 17:08:02 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

//====< Directive >=============================================================
#ifndef __DIRECTIVE_HPP__
# define __DIRECTIVE_HPP__

# include <iostream>

enum	DirectiveType
{
	TERMINAL,
	NON_TERMINAL
};

class	Directive
{
	private:
		int			type;
		int			level;
		std::string	key;
		std::string	rest;

	public:
		Directive(void);
		~Directive(void);

		int			getType(void) const;
		void		setType(const int type);

		int			getLevel(void) const;
		void		setLevel(const int level);

		std::string	getKey(void) const;
		void		setKey(const std::string key);

		std::string	getRest(void) const;
		void		setRest(const std::string key);
};

#endif /*__DIRECTIVE_HPP__*///==================================================
