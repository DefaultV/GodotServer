#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#include "Transform.cpp"

#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data
#define MAXPLAYERS 8

enum func_call{
	C_TRANSFORM
};

void die(char *s)
{
	perror(s);
	exit(1);
}

int broadcast(struct sockaddr_in* plylist, int s, char* buf, size_t buflen){
	for(int i = 0; i < sizeof(*plylist)/sizeof(plylist[0]); i++){
		printf("Sending to player: %d", plylist[i].sin_port);
		socklen_t len = sizeof(plylist[i]);
		if (sendto(s, buf, buflen, 0, (struct sockaddr*) &plylist[i], len) == -1){
			die("sendto()");
		}
	}
	return 0;
}

int passfunction(char* arr, struct sockaddr_in* plylist, int s){
	int d = (int)arr[0]-48;
	char buf[BUFLEN];

	switch(d){
		case C_TRANSFORM:
			puts("C_TRANSFORM");
			sprintf(buf, "%d", C_TRANSFORM);
			broadcast(plylist, s, buf, sizeof(buf));
			break;
		default:
			printf("Error, function not defined");
			break;
	}
	return 0;
}

int main(void)
{
	struct sockaddr_in si_me, si_other;

	int s, i, slen = sizeof(si_other) , recv_len;
	char buf[BUFLEN];

	//Vector3 newvec(1,1,1);
	//Transform newtrans(newvec, newvec, newvec);
	//create a UDP socket
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		die("socket");
	}

	// zero out the structure
	memset((char *) &si_me, 0, sizeof(si_me));

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = inet_addr("192.168.1.13");//htonl(INADDR_ANY);

	//bind socket to port
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
	{
		die("bind");
	}

	sockaddr_in playerlist[MAXPLAYERS];
	//keep listening for data
	while(1)
	{
		fflush(stdout);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		{
			die("recvfrom()");
		}else{
			playerlist[0] = si_other;
		}

		//print details of the client/peer and the data received
		printf("\nReceived packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("Data: %s\n" , buf);
		passfunction(buf, playerlist, s);
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
