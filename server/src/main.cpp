#include "Server.h"
#include <pthread.h>
#include <unistd.h>

#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data
#define MAXPLAYERS 8

int main(void)
{	Server server;
	struct sockaddr_in si_me, si_other;

	int s, recv_len, players = 0;
	socklen_t slen = sizeof(si_other)/2; //HACKFIX TODO
	char buf[BUFLEN];

	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		//server.die("socket");
		puts("Socket failed");
	}

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	//si_me.sin_addr.s_addr = inet_addr("127.0.0.1");//htonl(INADDR_ANY);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
	{
		//server.die("bind");
		puts("Bind failed");
	}

	Player playerlist[MAXPLAYERS];
	server.createDBUThread();
	while(1)
	{
		fflush(stdout);

		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		{
			//server.die("recvfrom()");
			puts("Recieve failed");
		}
		Player player;
		player.socket = si_other;
		server.passfunction(buf, playerlist, &players, &player, s);
	}
	return 0;
}
