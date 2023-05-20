#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef SocketManagement_H
#define SocketManagement_H

class SocketManagement
{
private:
	struct sockaddr_in server_addr;
	struct sockaddr_in target_addr;

	int listen_fd;
	int active_fd;

public:
	SocketManagement();
	~SocketManagement();

	int ConnectTo(std::string, int);
	int ListenBy(int);

	int getListenFD();
	int getActiveFD();
};

#endif
