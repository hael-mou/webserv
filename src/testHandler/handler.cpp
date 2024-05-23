#include "handler.hpp"

Handler::Handler(int fd)
	: mHandle(fd), mMode(IMultiplexer::Read)
{
}

Handler::~Handler(void)
{
}

const Handler::Handle&	Handler::getHandle(void) const
{
	return (mHandle);
}

const Handler::Mode&		Handler::getMode(void) const
{
	return (mMode);
}

# include <iostream>
Handler::HandlerQueue		Handler::handleEvent(void)
{
	struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);

	char read[1024];
	std::memset(read, 0, 1024);
	int bytes_received = recvfrom(mHandle, read, 1024, 0,
		(struct sockaddr *)&client_address, &client_len);
	std::cout << "received : " << read << std::endl;
	sendto(mHandle, read, bytes_received, 0, 
		(struct sockaddr *)&client_address, client_len);
	
	return (HandlerQueue());
}