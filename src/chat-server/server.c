/*
 * =====================================================================================
 *
 *       Filename:  server_epoll.c
 *
 *    Description:  epoll
 *
 *        Version:  1.0
 *        Created:  2023년 04월 21일 16시 27분 02초
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
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "header/jwt-c.h"

#define MAX_CLIENT 100
#define BUFF_SIZE 1024
#define LOG_SIZE 1536

struct udata
{
	int fd;
	char name[80];
};

const char* skey = "2JkpyD4C5v_qW=nzKkGCKCG-hhhb6K&2sk+m-72s^ntMXWC3fHUt^b6s7Ksg7DmA";
int user_fds[SOMAXCONN];

void sendMsg(struct epoll_event ev, char* msg);

int main()
{
//	struct node** hashTable = createHashTable();
	struct JToken* token;
	struct node** hashTable;

	struct sockaddr_in serv_sock, client_sock;
	struct sockaddr_in log_sock;
	struct epoll_event* events;	
	struct epoll_event ev;

	int listen_fd = 0;
	int client_fd = 0;
	int log_fd = 0;
	int ret = 0;
	int epoll_fd = 0;
	int client_fd_size = 0;
	int optval = 1;

	struct udata* user_data;

	char buf[BUFF_SIZE+1];
	char tmp[LOG_SIZE];
	char conn_str[] = "connected.\n";
	size_t read_size;
	int i;

	events = (struct epoll_event*)malloc(sizeof(struct epoll_event) * SOMAXCONN);
	/* to log server */
	if((log_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("create log socket fail\n");
		return -1;
	}

	memset(&log_sock, 0, sizeof(log_sock));
	log_sock.sin_family		= AF_INET;
	log_sock.sin_port		= htons(4001);
	log_sock.sin_addr.s_addr	= inet_addr("192.168.75.11");

	if(connect(log_fd, (struct sockaddr*)&log_sock, sizeof(log_sock)) < 0)
	{
		printf("connect err\n");
		fprintf(stderr, "%s\n", strerror(errno));
	}
	printf("Connected.\n");


	/* serv sock setting */
	if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("create socket fail\n");
		return -1;
	}
	printf("Passive Socket Created.\n");

	memset(&serv_sock, 0, sizeof(serv_sock));
	serv_sock.sin_family		= AF_INET;
	serv_sock.sin_port			= htons(8082);
	serv_sock.sin_addr.s_addr	= htonl(INADDR_ANY);

	setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	if(bind(listen_fd, (struct sockaddr*)&serv_sock, sizeof(serv_sock)) < 0)
	{
		printf("bind fail\n");
		return -1;
	}
	printf("Binded.\n");
			
	if(listen(listen_fd, 5))
	{
		printf("listen fail\n");
		exit(1);
	}
	printf("Listened.\n");

	/* epoll create */
	if((epoll_fd = epoll_create(SOMAXCONN)) < 0)
	{
		printf("epoll_create() fail\n");
		return -1;
	}
	printf("epoll_fd Created.\n");


	/* epoll setting */
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = epoll_fd;

	/* epoll add */
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev);
	memset(user_fds, -1, sizeof(int) * SOMAXCONN);
	printf("epoll Added.\n");

	while(1)
	{
		/* epoll wait */
		ret = epoll_wait(epoll_fd, events, SOMAXCONN, -1);
		printf("epoll_fd reached. ret=%d\n", ret);

		if(ret < -1)
		{
			printf("epoll_wait\n");
			break;
		}

		else if(ret == 0)
		{
			printf("idle\n");
			continue;
		}
		
		else
		{
			/* fd work */
			for(i=0;i<ret;i++)
			{	
			#ifdef DEBUG
				printf("event occured\n");
				printf("event number: %d\n", i);
			#endif
				if(events[i].data.fd == epoll_fd)
				{
					memset(buf, 0, BUFF_SIZE+1);
					client_fd_size = sizeof(client_sock);
					client_fd = accept(listen_fd, (struct sockaddr*)&client_sock, &client_fd_size);

				#ifdef DEBUG
					printf("accept fd: %d\n", client_fd);
				#endif

					read(client_fd, buf, BUFF_SIZE+1);

				#ifdef DEBUG
					printf("read: %s\n", buf);
				#endif

					token = initJToken(buf);
					if(verifyJToken(token, skey))
					{
						decodeJToken(token);
				#ifdef DEBUG
					printf("decodeJToken: %s [%d]\n", token->payload, strlen(token->payload));
				#endif
						hashTable = createHashTable();
						parseJSON_n(&hashTable, token->payload, strlen(token->payload));
				#ifdef DEBUG
					printf("hashTable\n");
					printHashTable(&hashTable);
				#endif
						
						write(client_fd, "ok\n", 3);
				#ifdef DEBUG
					printf("client_fd: %d\n", client_fd);
				#endif
						user_fds[client_fd] = 1;
		
						user_data = (struct udata*)malloc(sizeof(user_data) * 1);
						user_data->fd = client_fd;
						char* tmp = getValuebyKey(&hashTable, "user");
						printf("test>> %p ", user_data->name);
						for(i=0;tmp[i];i++)
						{
							user_data->name[i] = tmp[i];
						}
						user_data->name[i] = '\0';
						printf("%p\n", user_data->name);
		
						printf("[%s] joined. \n", user_data->name);
		
						usleep(25000);
		
						write(user_data->fd, conn_str, strlen(conn_str));
		
						ev.events = EPOLLIN;
						ev.data.ptr = user_data;
		
						epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev);

						printf(">> %p\n", user_data);

//						freeJToken(token);
//				#ifdef DEBUG
//					printf("== freeJToken Complete ==\n");
//				#endif
						deleteHashTable(&hashTable);
				#ifdef DEBUG
					printf("== cleanHashTable Complete ==\n");
				#endif
						
					}
					else
					{
						printf("close fd: %d\n",  client_fd);
						user_fds[client_fd] = -1;
						close(client_fd);
					}
				}
				else
				{
					user_data = events[i].data.ptr;
					memset(buf, 0, BUFF_SIZE+1);
					read_size = read(user_data->fd, buf, BUFF_SIZE+1);
					if(read_size <= 0)
					{
						epoll_ctl(epoll_fd, EPOLL_CTL_DEL, user_data->fd, events);
						close(user_data->fd);
						printf("close fd: %d\n", user_data->fd);
						printf("Connection lost: %s %p\n", user_data->name, user_data);
						user_fds[user_data->fd] = -1;

						printf("user_data = %p\n", user_data);

						free(user_data);
					}
					else
					{
						memset(tmp, 0, LOG_SIZE);
						sprintf(tmp, "0/chat/chat/%s/%s\0", user_data->name, buf);
						write(log_fd, tmp, strlen(tmp));
						sendMsg(events[i], buf);
					}
					
				}
			}
	
			continue;
		}
	}

	if(close(epoll_fd))
	{
		fprintf(stderr, "Failed to close epoll fd\n");
		return 1;
	}
	

	return 0;
}

void sendMsg(struct epoll_event ev, char* msg)
{
	int i;
	char buf[BUFF_SIZE + 24];
	struct udata* user_data;
	user_data = ev.data.ptr;
	for(i=0;i<SOMAXCONN;i++)
	{
		memset(buf, 0, BUFF_SIZE + 24);
		sprintf(buf, "%s : %s", user_data->name, msg);
		if(user_fds[i] == 1)
		{
			write(i, buf, BUFF_SIZE + 24);
		}
	}
}
