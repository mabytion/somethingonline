/*
 * =====================================================================================
 *
 *       Filename:  tcp_client.c
 *
 *    Description:  TCP Client Example
 *
 *        Version:  1.0
 *        Created:  01/17/2023 05:41:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024

int main(int argc, char** argv)
{
	int client_socket;
	struct sockaddr_in server_addr;
	char buff[BUFF_SIZE + 5];

	int i;

	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(client_socket < 0)
	{
		printf("socket err: ln 35\n");
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family		= AF_INET;
	server_addr.sin_port		= htons(4001);	
	server_addr.sin_addr.s_addr	= inet_addr("192.168.75.11");

	if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
	{
		printf("connect err: ln 47\n");
		exit(1);
	}
	
	char* tmp = "kill";

	write(client_socket, tmp, strlen(tmp));
	printf("%s\n", tmp);
	close(client_socket);
	
	return 0;
}
