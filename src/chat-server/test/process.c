#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd[2];
	int pid;
	char str[1024];

	if(pipe(fd) == -1)
	{
		fprintf(stderr, "error");
	}

	pid = fork();

	if(pid == 0)
	{
		printf("child\n");

		close(fd[1]);

		read(fd[0], str, 1024);

		printf("msg: %s", str);
	}
	if(pid > 0)
	 {
		printf("parent\n");

		close(fd[0]);

		write(fd[1], "piped\n", 6);
	}

	return 0;
}
