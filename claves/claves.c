#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "../sockets/sockets.h"

// auxiliary function to check the length of value1 is correct
int is_value1_valid(char *value1) {
    if (strlen(value1) > 256) {
        return -1;
    }
    return 0;
}

 /* The structure of the following functions are all the same:
    1- create the sockets
    2- create the msg struct to be sent
    3- send msg
    4- receive it
    5- close queues */

int client_init(int argc, char *argv[]) {
    int sd;
    int err;
    int test;
    struct sockaddr_in server_addr, client_addr;
	struct hostent *hp;

	if (argc != 2){
        printf("Not enough arguments \n");
        return(0);
    }

    sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == 1) {
		printf("Error en socket\n");
		return -1;
	}
    // set server address
	hp = gethostbyname (argv[1]);
	if (hp == NULL) {
		perror("gethostbyname");
		return -1;
	}
    memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length);
   	server_addr.sin_family  = AF_INET;
   	server_addr.sin_port    = htons(4200);
    
    err = connect(sd, (struct sockaddr *) &server_addr,  sizeof(server_addr));
	if (err == -1) {
		perror("connect");
		return -1;
	}
    test = 0;
    err = sendMessage(sd, (char *) &test, sizeof(char));
	if (err == -1){
		perror("client: send");
		return -1;
	}
    close(sd);
    return 0;
}


int client_set_value(int key, char *value1, int value2, double value3) {
    return 0;
}

int client_get_value(int key, char *value1, int *value2, double *value3) {
    return 0;
}

int client_modify_value(int key, char *value1, int value2, double value3) {
    return 0;
}

int client_delete_value(int key) {
    return 0;
}

int client_exist(int key) {
    return 0;
}

int client_copy_key(int key1, int key2) {
    return 0;
}
