#include "Server.h"
#include "sqlite3.h"

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
	sprintf(outstr, "%d:%d:%.2f%.2f%.2f%.2f%.2f%.2f%.2f%.2f%.2f", *cmd, *id, transform->position.x, transform->position.y, transform->position.z, transform->rotation.x, transform->rotation.y, transform->rotation.z, transform->scale.x, transform->scale.y, transform->scale.z);
}

int Server::passfunction(char* buf, Player* plylist, int* players, Player* client, int s){
	int d = (int)buf[0]-48;

	char newbuf[512];
	int id = 1;
	// --------------
	Transform a_trans;
	if (d == C_LOGIN){
		puts("LOGIN");
		plylist[*players] = *client;
		plylist[*players].id = *players;
		*players += 1;
		d = 0;
		printf("\nNumer of players: %d\n", *players);
		//getencodedtransform(&a_trans, newbuf, &d, &id);
		//broadcast(plylist, players, s, newbuf, sizeof(newbuf));
	}
	if (d == C_LOGOUT){

		if (*players == 0) //make sure we don't have negative players, prettify
			return 1;
		puts("LOGOUT"); //TODO
		//plylist[*players] = null;
		*players -= 1;
		printf("\nNumer of players: %d\n", *players);
	}
	if (d == C_TRANSFORM){
			puts("C_TRANSFORM");
			//a_trans.setScale(0.5, 0.5, 0.5);
			a_trans.setPosition(grabPositionFromDB(&d));
			getencodedtransform(&a_trans, newbuf, &d, &id);
			broadcast(plylist, players, s, newbuf, sizeof(newbuf));
	}
	//DEBUG PURPOSES
	//printf("\nEncoded string:\n%s\n", buf);
	return 0;
}

Vector3 sql_position;
void setSQLPosition(float x, float y, float z){
	sql_position.x = x;
	sql_position.y = y;
	sql_position.z = z;
}

int sql_callback(void* data, int argc, char** argv, char** azColName){

	int i;
	float x, y, z;
	/*for (i = 0; i < argc; i++){

		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		if (strcmp(azColName[i], "POSX") == 1){
			x = (float)strtod(argv[i], NULL);
			printf("Yeaposx %f\n", x);
		}
		if (strcmp(azColName[i], "POSY") == 1){
			y = (float)strtod(argv[i], NULL);
			printf("Yeaposy %f\n", y);
		}
		if (strcmp(azColName[i], "POSZ") == 1){
			z = (float)strtod(argv[i], NULL);
			printf("Yeaposz %f\n", z);
		}
	}*/
	x = (float)strtod(argv[0], NULL);
	y = (float)strtod(argv[1], NULL);
	z = (float)strtod(argv[2], NULL);
	setSQLPosition(x, y, z);
	return 0;
}


Vector3 Server::grabPositionFromDB(int* id){

	sqlite3* db;
	char* zErrMsg;
	char sql[50];
	const char* data = "Callback";
	int rc;

	rc = sqlite3_open("db/transforms.db", &db);

	if (rc)
		printf("%s", sqlite3_errmsg(db));

	sprintf(sql, "SELECT * FROM TRANSFORMS WHERE ID == 1");
	rc = sqlite3_exec(db, sql, sql_callback, (void*)data, &zErrMsg);

	sqlite3_close(db);
	return sql_position;
}
