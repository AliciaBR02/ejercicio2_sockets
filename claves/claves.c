#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "../sockets/sockets.h"
#include "../mensaje.h"

//SIZE OF THE STRUCT MESSAGE
//int size = sizeof(int)*3 + sizeof(int8_t)*2 + sizeof(double) + sizeof(char *)*(256+1) + sizeof(int*) + sizeof(double*);
//char buffer[512];
// auxiliary function to check the length of value1 is correct
char *port_tuplas;
char *ip_tuplas;
struct sockaddr_in server_addr, client_addr;
int sd;
char buffer[512]; // where the arguments will be written to be sent

int is_value1_valid(char *value1) {
    if (strlen(value1) > 256) {
        return -1;
    }
    return 0;
}

int set_env_variables() {
    port_tuplas = getenv("PORT_TUPLAS");
    ip_tuplas = getenv("IP_TUPLAS");
    if (port_tuplas == NULL || ip_tuplas == NULL) {
        printf("Error: no se han encontrado las variables de entorno PORT_TUPLAS o IP_TUPLAS\n");
        return -1;
    }
}

int set_socket_connection() {
    int err;

    sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == 1) {
		printf("Error en socket\n");
		return -1;
	}
    // set server address

   	server_addr.sin_family  = AF_INET;
   	server_addr.sin_port    = htons(atoi(port_tuplas));
    server_addr.sin_addr.s_addr = inet_addr(strcmp(ip_tuplas, "localhost") == 0 ? "127.0.0.1" : ip_tuplas);
    
    err = connect(sd, (struct sockaddr *) &server_addr,  sizeof(server_addr));
	if (err == -1) {
		perror("connect");
		return -1;
	}

}
 /* The structure of the following functions are all the same:
    1- create the sockets
    2- create the msg struct to be sent
    3- send msg
    4- receive it
    5- close queues */

int client_init() {
    int err;
    
    err = set_env_variables();
    if (err == -1) return -1;

    err = set_socket_connection();
    if (err == -1) return -1;

    sprintf(buffer, "1\n");
    char res;
    
    err = sendMessage(sd, buffer, sizeof(buffer) + 1);
	if (err == -1){
		perror("client: send");
		return -1;
	}
    err = recvMessage(sd, (char *)&res, sizeof(char));
    if (err == -1){
        perror("client: recv");
        return -1;
    }
    memset(buffer, 0, sizeof(buffer));
    close(sd);
    return res;
}


int client_set_value(int key, char *value1, int value2, double value3) {
    int err;
    
    err = set_env_variables();
    if (err == -1) return -1;

    err = set_socket_connection();
    if (err == -1) return -1;

    int key2 = 0;
    sprintf(buffer, "2\n%d\n%d\n%d\n%f\n%s\n", key, key2, value2, value3, value1);
    char res;
    
    err = sendMessage(sd, buffer, sizeof(buffer) + 1);
	if (err == -1){
		perror("client: send");
		return -1;
	}
    err = recvMessage(sd, (char *)&res, sizeof(char));
    if (err == -1){
        perror("client: recv");
        return -1;
    }
    memset(buffer, 0, sizeof(buffer));
    close(sd);
    return res;
}

int client_get_value(int key, char *value1, int *value2, double *value3) {
    int err;
    
    err = set_env_variables();
    if (err == -1) return -1;

    err = set_socket_connection();
    if (err == -1) return -1;

    sprintf(buffer, "3\n%d\n", key);
    struct message res;
    
    err = sendMessage(sd, buffer, sizeof(buffer) + 1);
	if (err == -1){
		perror("client: send");
		return -1;
	}
    err = recvMessage(sd, buffer, sizeof(buffer));
    if (err == -1){
        perror("client: recv");
        return -1;
    }
    readLine(sd, (char*)&res.res, sizeof(buffer));
    readLine(sd, (char*)&res.value2, sizeof(buffer));
    readLine(sd, (char*)&res.value3, sizeof(buffer));
    readLine(sd, res.value1, sizeof(buffer));
    memset(buffer, 0, sizeof(buffer));
    close(sd);
    strcpy(value1, res.value1);
    *value2 = res.value2;
    *value3 = res.value3;
    return res.res;
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
