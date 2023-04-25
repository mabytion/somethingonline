#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024

int main()
{
	int server_sock = 0;
	int client_sock = 0;
	int client_addr_size = 0;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	char recv_buff[BUFF_SIZE + 5];

	int connect = 0;
	char tmp[32] = { 0, };

	if((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket err\n");
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family		= AF_INET;
	server_addr.sin_port		= htons(4001);
	server_addr.sin_addr.s_addr	= htonl(INADDR_ANY);

	if(bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("bind err\n");
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}

	if(listen(server_sock, 5) < 0)
	{
		printf("listen err\n");
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}

	client_addr_size = sizeof(client_addr);
	while(1)
	{
		if(!connect)
		{
			if((client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size)) < 0)
			{
				printf("accept err\n");
				fprintf(stderr, "%s\n", strerror(errno));
				return -1;
			}
			else
			{
				inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, tmp, sizeof(tmp));
				printf("connected by %s\n", tmp);
				connect = 1;
				
			}
		}

		memset(recv_buff, 0, sizeof(recv_buff));
		if(read(client_sock, recv_buff, BUFF_SIZE) <= 0)
		{
			close(client_sock);
			printf("unknown msg\n");
			connect = 0;
		}

		if(strncmp(recv_buff, "logging", 7) == 0)
		{
			printf("%s\n", recv_buff);
		}
		
		if(strncmp(recv_buff, "exit", 4) == 0)
		{
			close(client_sock);
			printf("connection tear down\n");
			connect = 0;
		}

		if(strncmp(recv_buff, "kill", 4) == 0)
		{
			break;
		}
	}
	close(server_sock);

	printf("Passive socket was closed\n");
	printf("EOF\n");

	return 0;
}
