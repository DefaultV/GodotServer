#include "Server.h"

enum func_call{
	C_LOGIN,
	C_LOGOUT,
	C_TRANSFORM,
	C_SPAWN
};

void Server::die(char *s)
{
	perror(s);
	exit(1);
}

int Server::broadcast(Player* plylist, int* players, int s, char* buf, size_t buflen){

	for(int i = 0; i <= *players-1; i++){
		printf("\n%lu player(s)", sizeof(*plylist)/sizeof(plylist[0]));
		printf("\nSending -%s- to player on port: %d", buf ,plylist[i].socket.sin_port);
		socklen_t len = sizeof(plylist[i].socket);
		if (sendto(s, buf, buflen, 0, (struct sockaddr*) &plylist[i].socket, len) == -1){
			//die("sendto()");
			printf("Sending failed -- Broadcast");
		}
	}
	return 0;
}

void Server::getencodedtransform(Transform* transform, char* outstr, int* cmd, int* id){
	sprintf(outstr, "%d:%d:%d%d%d%d%d%d%d%d%d", *cmd, *id, transform->position.x, transform->position.y, transform->position.z, transform->rotation.x, transform->rotation.y, transform->rotation.z, transform->scale.x, transform->scale.y, transform->scale.z);
}

//DEBUG TEST TRANSFORM MAKE SQL DB TODO
Vector3 onevec(1,1,1);
Vector3 zerovec(0,0,0);
Transform newtrans(zerovec, zerovec, onevec);

int Server::passfunction(char* buf, Player* plylist, int* players, Player* client, int s){
	int d = (int)buf[0]-48;

	char newbuf[512];
	int id = 1;
	// --------------
	if (d == C_LOGIN){
		puts("LOGIN");
		plylist[*players] = *client;
		plylist[*players].id = *players;
		*players += 1;
		d = 0;
		printf("\nNumer of players: %d\n", *players);
		getencodedtransform(&newtrans, newbuf, &d, &id);
		broadcast(plylist, players, s, newbuf, sizeof(newbuf));
	}
	if (d == C_LOGOUT){

		puts("LOGOUT"); //TODO
		//plylist[*players] = null;
		*players -= 1;
		printf("\nNumer of players: %d\n", *players);
	}
	if (d == C_TRANSFORM){
			puts("C_TRANSFORM");
			d = 1;
			Vector3 newvec(0,2,0);
			newtrans.position = newvec;
			getencodedtransform(&newtrans, newbuf, &d, &id);
			broadcast(plylist, players, s, newbuf, sizeof(newbuf));
	}
	//DEBUG PURPOSES
	//printf("\nEncoded string:\n%s\n", buf);
	return 0;
}

