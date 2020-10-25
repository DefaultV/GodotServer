#include "Server.h"

enum func_call{
	C_LOGIN,
	C_LOGOUT,
	C_TRANSFORM
};

void Server::die(char *s)
{
	perror(s);
	exit(1);
}

int Server::broadcast(Player* plylist, int* players, int s, char* buf, size_t buflen){

	printf("%d", *players);
	for(int i = 0; i <= *players-1; i++){
		printf("\n%d player(s)", sizeof(*plylist)/sizeof(plylist[0]));
		printf("\nSending to player on port: %d", plylist[i].socket.sin_port);
		socklen_t len = sizeof(plylist[i].socket);
		printf("\nlen: %d\n", sizeof(plylist[i].socket));
		if (sendto(s, buf, buflen, 0, (struct sockaddr*) &plylist[i].socket, len) == -1){
			die("sendto()");
		}
	}
	return 0;
}

void Server::getencodedtransform(Transform* transform, char* outstr, int* cmd, int* id){

	sprintf(outstr, "%d:%d:%d%d%d%d%d%d%d%d%d", *cmd, *id, transform->position.x, transform->position.y, transform->position.z, transform->rotation.x, transform->rotation.y, transform->rotation.z, transform->scale.x, transform->scale.y, transform->scale.z);
}

int Server::passfunction(char* buf, Player* plylist, int* players, Player* client, int s){
	int d = (int)buf[0]-48;

	//DEBUG TEST TRANSFORM MAKE SQL DB TODO
	Vector3 onevec(1,1,1);
	Vector3 zerovec(0,0,0);
	Transform newtrans(zerovec, zerovec, onevec);
	int id = 1;
	// --------------
	if (d == C_LOGIN){
		puts("LOGIN");
		plylist[*players] = *client;
		plylist[*players].id = *players;
		*players += 1;
		printf("\nNumer of players: %d\n", *players);
	}
	if (d == C_LOGOUT){

		puts("LOGOUT"); //TODO
		//plylist[0] = null;
	}
	if (d == C_TRANSFORM){
			puts("C_TRANSFORM");
			getencodedtransform(&newtrans, buf, &d, &id);
			printf("\nEncoded string:\n%s\n", buf);
			broadcast(plylist, players, s, buf, sizeof(buf));
	}
	return 0;
}

