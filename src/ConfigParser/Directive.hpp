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
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/05/17 16:21:46 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

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
		void		setType(int type);

		int			getLevel(void) const;
		void		setLevel(int level);

		std::string	getKey(void) const;
		void		setKey(std::string key);

		std::string getRest(void) const;
		void		setRest(std::string key);
};

#endif /*__DIRECTIVE_HPP__*/
