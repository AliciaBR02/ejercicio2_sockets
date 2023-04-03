#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// auxiliary function to check the length of value1 is correct
int is_value1_valid(char *value1) {
    if (strlen(value1) > 256) {
        return -1;
    }
    return 0;
}

int sendMessage(int socket, char * buffer, int len) {
	int r;
	int l = len;
	do {	
		r = write(socket, buffer, l);
		l = l -r;
		buffer = buffer + r;
	} while ((l>0) && (r>=0));
	
	if (r < 0)
		return (-1);   /* fail */
	else
		return(0);	/* full length has been sent */
}

int recvMessage(int socket, char *buffer, int len) {
	int r;
	int l = len;
	do {	
		r = read(socket, buffer, l);
		l = l -r ;
		buffer = buffer + r;
	} while ((l>0) && (r>=0));
	
	if (r < 0)
		return (-1);   /* fallo */
	else
		return(0);	/* full length has been receive */
}
 /* The structure of the following functions are all the same:
    1- create the sockets
    2- create the msg struct to be sent
    3- send msg
    4- receive it
    5- close queues */

int client_init() {
    int sd;
    int err;
    int test;
    struct sockaddr_in server_addr, client_addr;

    sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == 1) {
		printf("Error en socket\n");
		return -1;
	}
    // set server address
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons( 8888 );
    
    err = connect(sd, (struct sockaddr *) &server_addr,  sizeof(server_addr));
	if (err == -1) {
		printf("Error en connect\n");
		return -1;
	}
    test = 0; // suma
    err = sendMessage(sd, (char *) &test, sizeof(char));  // envía la operacion
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
