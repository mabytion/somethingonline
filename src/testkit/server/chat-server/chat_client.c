#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFF_SIZE 1024

int main(int argc, char* argv[])
{
	struct sockaddr_in serv_addr;

	char buf[BUFF_SIZE];
	char name[80];

	int sock_fd;
	int sock_len;
	int max_fd;
	int fd_num;

	fd_set read_fds, old_fds;
	int read_num;

	int first_run = 1;

	if(argc < 2)
	{
		snprintf(name, 6, "Guest");
	}
	else
	{
		strcpy(name, argv[1]);
	}

	
	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket err\n");
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(8082);

	if(connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("connect err\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(1);
	}
	
	int option = 1;
	setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

	FD_ZERO(&read_fds);
	FD_SET(sock_fd, &read_fds);
	FD_SET(0, &read_fds);

	max_fd = sock_fd;
	old_fds = read_fds;

	if(write(sock_fd, "ok\n", 3) <= 0)
	{
		printf("init err\n");
		return 1;
	}

	while(1)
	{
		read_fds = old_fds;
		fd_num = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
		if(first_run)
		{

			if(read(sock_fd, buf, BUFF_SIZE) <= 0)
			{
				printf("init(r) err\n");
				return 1;
			}
			else
			{
				if(strncmp("ok", buf, 2) == 0)
				{
					printf("OK.\n");
					first_run = 0;
				}
			}

			if(write(sock_fd, name, strlen(name)) <= 0)
			{
				printf("init(w) err\n");
				return 1;
			}

			else
			{
				printf("your name: [%s]\n", name);
			}

		}

		else
		{

			if(FD_ISSET(sock_fd, &read_fds))
			{
				memset(buf, 0, BUFF_SIZE);
				if((read_num = read(sock_fd, buf, BUFF_SIZE)) <= 0)
				{
					printf("read err\n");
					return 1;
				}
				
				if(write(1, buf, read_num) != read_num)
				{
					printf("write err\n");
					return 1;
				}
			}
			if(FD_ISSET(0, &read_fds))
			{
				memset(buf, 0, BUFF_SIZE);
				read_num = read(0, buf, BUFF_SIZE);
				if(read_num <= 0)
				{
					return 1;
				}

				if(strncmp(buf, "exit", 4) == 0)
				{
					close(sock_fd);
					break;
				}

				if(read_num != write(sock_fd, buf, read_num))
				{
					return 1;
				}
			}
		
		}
	}
	
		return 0;
}
