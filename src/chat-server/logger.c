#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#define PIPENAME "./pipe"
#define LOG_SIZE 1536

int main()
{
	char msg[LOG_SIZE];
	struct sockaddr_in log_sock;

	int log_fd, pipe_fd;
	int i;

	if((pipe_fd = open(PIPENAME, O_RDWR)) < 0)
	{
		printf("pipe open fail\n");
		return 0;
	}

	if((log_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
	    printf("create log socket fail\n");
	    return -1;
	}

	memset(&log_sock, 0, sizeof(log_sock));
	log_sock.sin_family     = AF_INET;
	log_sock.sin_port       = htons(4001);
	log_sock.sin_addr.s_addr    = inet_addr("192.168.123.11");

	if(connect(log_fd, (struct sockaddr*)&log_sock, sizeof(log_sock)) < 0)
	{
	    printf("connect err\n");
	    fprintf(stderr, "%s\n", strerror(errno));
	}
	printf("Connected.\n");

	while(1)
	{
		if(read(pipe_fd, msg, sizeof(msg)) < 0)
		{
			printf("pipe read fail\n");
			return 0;
		}

		write(log_fd, msg, strlen(msg));

		for(i=0;i<LOG_SIZE;i++)
		{
			msg[i] = 0;
		}

	}

	return 0;
}
