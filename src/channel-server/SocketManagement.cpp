#include "SocketManagement.h"

SocketManagement::SocketManagement()
{
	std::cout << "Create SocketManagement()" << std::endl;
}

SocketManagement::~SocketManagement()
{
	close(active_fd);
	close(listen_fd);
}

int SocketManagement::ConnectTo(std::string target, int port)
{
	if((active_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << strerror(errno) << std::endl;
		return 1;
	}

	memset(&target_addr, 0, sizeof(target_addr));
	target_addr.sin_family		= AF_INET;
	target_addr.sin_port		= htons(port);
	target_addr.sin_addr.s_addr	= inet_addr(target.c_str());

	if(connect(active_fd, (struct sockaddr*)&target_addr, sizeof(target_addr)) < 0)
	{
		std::cout << strerror(errno) << std::endl;
		return 2;
	}

	return 0;
}

int SocketManagement::ListenBy(int port)
{
	if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << strerror(errno) << std::endl;
		return 1;
	}

	server_addr.sin_family		= AF_INET;
	server_addr.sin_port		= htons(port);
	server_addr.sin_addr.s_addr	= htonl(INADDR_ANY);

	if(bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		std::cout << strerror(errno) << std::endl;
		return 2;
	}

	if(listen(listen_fd, 5) < 0)
	{
		std::cout << strerror(errno) << std::endl;
		return 3;
	}

	return 0;
}

int SocketManagement::getActiveFD()
{
	return active_fd;
}

int SocketManagement::getListenFD()
{
	return listen_fd;
}
