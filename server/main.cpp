#include "Server.h"

#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data
#define MAXPLAYERS 8

int main(void)
{	Server server;
	struct sockaddr_in si_me, si_other;

	int s, recv_len, players = 0;
	socklen_t slen = sizeof(si_other)/2; //HACKFIX TODO
	char buf[BUFLEN];

	//create a UDP socket
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		//server.die("socket");
		printf("Socket failed");
	}

	// zero out the structure
	memset((char *) &si_me, 0, sizeof(si_me));

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	//si_me.sin_addr.s_addr = inet_addr("127.0.0.1");//htonl(INADDR_ANY);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind socket to port
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
	{
		//server.die("bind");
		printf("Bind failed");
	}

	Player playerlist[MAXPLAYERS];
	//keep listening for data
	int id = 1;
	float inc = 0;
	while(1)
	{
		fflush(stdout);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		{
			//server.die("recvfrom()");
			printf("Recieve failed");
		}
		//print details of the client/peer and the data received
		printf("\nReceived packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("Data: %s\n" , buf);
		Player player;
		player.socket = si_other;
		server.passfunction(buf, playerlist, &players, &player, s);

		inc+= 0.01;
		printf("\nInc: %f\n", inc);
		server.setPositionInDB(&id, Vector3(0, 0+inc, -2));
		//now reply the client with the same data
		//strcpy(buf, "Hello from C++!");
		/*if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
		{
			die("sendto()");
		}
		else
			printf("\nSending data to %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));*/
	}
	return 0;
}
