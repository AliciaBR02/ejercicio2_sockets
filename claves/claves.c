#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

// auxiliary function to check the length of value1 is correct
int is_value1_valid(char *value1) {
    if (strlen(value1) > 256) {
        return -1;
    }
    return 0;
}

 /* The structure of the following functions are all the same:
    1- open the queues
    2- create the msg struct to be sent
    3- send msg
    4- receive it
    5- close queues */

int client_init() {
    int sd;
    sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == 1) {
		printf("Error en socket\n");
		return -1;
	}
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
