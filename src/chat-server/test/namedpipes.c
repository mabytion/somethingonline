#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define MSG_SIZE 1024
#define PIPENAME "./pipe"

int main()
{
	char msg[MSG_SIZE];
	int fd;
	int i, rc;
	int pid;

	if(access(PIPENAME, F_OK) == 0)
	{
		unlink(PIPENAME);
	}

	if((rc = mkfifo(PIPENAME, 0666)) < 0)
	{
		printf("fail to open named pipe\n");
		return 0;
	}

	pid = fork();
	
	if(pid == 0)
	{
		execlp("./namedpiper", "./namedpiper", NULL);
	}

	else
	{

		if((fd = open(PIPENAME, O_WRONLY)) < 0)
		{
			printf("fuck\n");
			return 0;
		}

		for(i=0;i<3;i++)
		{
			snprintf(msg, sizeof(msg), "[%i]", i);

			if(write(fd, msg, sizeof(msg)) < 0)
			{
				printf("fail\n");
				return 0;
			}
		}
	}

	return 0;
}
