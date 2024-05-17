//            ################                                                  
//          ####################                                                
//        ########################                                              
//       #############+########### #                                            
//       ######-..        .+########         < FSM.cpp >                        
//       ####-..            ..+####                                             
//       ###-...             .-####                                             
//       ###...              ..+##    Student: oezzaou <oezzaou@student.1337.ma>
//        #-.++###.      -###+..##                                              
//        #....  ...   .-.  ....##       Created: 2024/03/26 00:35:07 by oezzaou
//     --.#.-#+## -..  -+ ##-#-.-...     Updated: 2024/03/26 00:48:11 by oezzaou
//      ---....... ..  ........... -                                            
//      -+#..     ..   .       .+-.                                             
//       .--.     .     .     ..+.                                              
//         -..    .+--.-.     ...                                               
//         +.... .-+#.#+.    ..-                                                
//          +...#####-++###-..-                                                 
//          #---..----+--.---+##                                                
//        ###-+--.... ....--+#####                                              
//  ##########--#-.......-#-###########      Made By Oussama Ezzaou <OEZZAOU> :)

# include "FSM.hpp"

//====< constructor >===========================================================
FSM::FSM(void)
{
}

//====< detectType >============================================================
int	FSM::detectType(std::string str)
{
	int	prev_state;
	int	curr_state;
	int	state;
	int	index;

	index = -1;
	state = START;
	prev_state = state;
	while (str[++index] && prev_state != STRING)
	{
		curr_state = getNextState(prev_state, str[index]);
		if (curr_state == END && state == START)
			state = prev_state;
		prev_state = curr_state;
	}
	return ((state != START && prev_state == END)? state: prev_state);
}

//====< getNextState >========================================================
int	FSM::getNextState(int prv, char input)
{
	if (prv == START && strchr(" \t\r", input))
		return (START);
	if (prv == START && !isdigit(input))
		return (strchr("+-/*", input)? OPERATOR: CHAR);
	if ((prv == START || prv == OPERATOR || prv == INT) && isdigit(input))
		return (INT);
	if (prv == INT && input == '.')
		return (FUTURE_DOUBLE);
	if ((prv == FUTURE_DOUBLE || prv == DOUBLE) && isdigit(input))
		return (DOUBLE);
	if ((prv == INT || prv == DOUBLE) && input == 'f')
		return (FLOAT);
	if (prv != START && input == ' ')
		return (END);
	return (STRING);
}
