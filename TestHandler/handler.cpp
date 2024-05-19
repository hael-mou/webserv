#include "handler.hpp"

Handler::Handler(Socketfd fd)
{
	server_fd = fd;
	mode = Read;
}

Mode Handler::getMode(void)
{
	return (mode);
}

# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>


HandlerState	Handler::handleEvent(void)
{
	Socketfd client_fd = accept(server_fd, NULL, NULL);

	if (client_fd == -1)
		return (END);
	
	char buffer[1024];
	while (recv(client_fd, buffer, 1024, 0) > 0)
		send(client_fd, buffer, 1024, 0);
	close(client_fd);
	return (CONTINUE);
}

int main()
{
	int socketFd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(socketFd, (struct sockaddr*)&addr, sizeof(addr));
	listen(socketFd, 5);
	Reactor reactor;
	reactor.registerHandler(socketFd, new Handler(socketFd));

	while (1)
	{
		reactor.handleEvents();
	}
}
