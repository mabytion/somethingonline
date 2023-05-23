#include "JWT_HS256.h"
#include "SocketManagement.h"
#include "Character.h"
#include <iostream>
#include <unistd.h>

#define PLAIN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ"
#define COMPLETE "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.pF3q46_CLIyP_1QZPpeccbs-hC4n9YW2VMBjKrSO6Wg"

using namespace std;

int main()
{
	vector<Character*> characters;
	string conn_str("500/Connected");
	struct sockaddr_in player_addr;
	int player_addr_size;

	struct epoll_event* events;
	struct epoll_event ev;

	int ret = 0;
	int epoll_fd = 0;

	/* P/A Socket Create */
	SocketManagement* smgmt = new SocketManagement();
	smgmt->ConnectTo("192.168.123.11", 4001);
	smgmt->ListenBy("8081");


	/* epoll create */
	if((epoll_fd = epoll_create(SOMAXCONN)) < 0)
	{
		cout << strerror(errno) << endl;
		return 101;
	}

	/* epoll setting */
	ev.events = EPOLLIN;
	ev.data.fd = epoll_fd;

	/* epoll add */	
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, smgmt.getListenFD());
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, smgmt.getActiveFD());

	while(1)
	{
		/* epoll wait */
		ret = epoll_wait(epoll_fd, events, SOMAXCONN, -1);

		if(ret < -1)
		{
			cout << "epoll_wait" << endl;
			break;
		}

		else if(ret == 0)
		{
			cout << "idle" << endl;
			continue;
		}

		else
		{
			/* fd works */
			for(int i=0;i<ret;i++)
			{
				if(events[i].data.fd == epoll_fd)
				{
					player_addr_size = sizeof(player_addr);
					Character new_one = new Character();
					new_one->setFD(accept(smgmt.getListenFD(), (struct sockaddr*)&player_addr, &player_addr_size);
					
					 
				}
			}
		}


	}


	return 0;
}
