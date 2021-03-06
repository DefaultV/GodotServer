#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

#include "Transform.h"
#include "Player.h"

class Server{
	public:
		void die(char*);
		int broadcast(Player*, int*, int, char*, size_t);
		void getencodedtransform(Transform*, char*, int*, int*);
		bool checkIfNewPlayer(Player*, Player*, int*);
		int passfunction(char*, Player*, int*, Player*, int);
		Vector3 grabPositionInDB(int*);
		void setPositionInDB(int*, Vector3);
		void createDBUThread();
		static void* creatureUpdate(void*);
};
