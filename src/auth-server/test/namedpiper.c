#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define MSG_SIZE 1024
#define PIPENAME "./pipe"

int main()
{
	char msg[MSG_SIZE];
	int fd;
	
	if((fd = open(PIPENAME, O_RDWR)) < 0)
	{
		printf("fuck2\n");
		return 0;
	}

	for(;;)
	{
		if(read(fd, msg, sizeof(msg)) < 0)
		{
			printf("fail2\n");
			return 0;
		}

		printf("recv: %s\n", msg);
	}

	return 0;
}
