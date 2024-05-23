/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ WebServer Main File ]                                               #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-21                                                   #
#                                                                              #
** ************************************************************************* **/

# include <iostream>

// int main(int  argc, char const *argv[])
// {
// 	if (argc == 2)
// 	{
// 		(void)argv;
// 		//std::cout << argv[1] << std::endl;
// 	}
// 	while (1);
// 	return 0;
// }

# include "Reactor.hpp"
# include "SelectMultiplexer.hpp"
# include <sys/socket.h>
# include <unistd.h>
# include <netinet/in.h>
# include <handler.hpp>
# include <unistd.h>

int createServer(int port)
{
	int severSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (severSocket == -1)
	{
		std::cerr << "socket error" << std::endl;
		exit(1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(severSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		std::cerr << "bind error" << std::endl;
		exit(1);
	}
	return (severSocket);
}

int main()
{
	int sever1 = createServer(8080);
	int sever2 = createServer(8081);
	int sever3 = createServer(8082);

	Reactor reactor(new SelectMultiplexer());

	reactor.registerHandler(sever1, new Handler(sever1));
	reactor.registerHandler(sever2, new Handler(sever2));
	reactor.registerHandler(sever3, new Handler(sever3));

	while (1)
	{
		reactor.handleEvents(3000);
		std::cout << "done" << std::endl;
	}
	close(sever1);
	close(sever2);
	close(sever3);
}