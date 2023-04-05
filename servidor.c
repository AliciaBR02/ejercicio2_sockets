#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include "operaciones/operaciones.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include "sockets/sockets.h"
#include "mensaje.h"

// threads and mutexes' global variables
pthread_cond_t cond_message;
pthread_mutex_t mutex_message;
int not_message_copied = 1;
char buffer[1024];


// function to process the message and execute the requested operation
void process_message(struct message *msg) {
    struct message msg_resp = *msg;
    // copy the descriptor to a local variable
    int s_local;
    pthread_mutex_lock(&mutex_message);
    // copy the message to the global variable
    s_local = msg_resp.s;
    not_message_copied = 0;
    pthread_cond_signal(&cond_message);
    pthread_mutex_unlock(&mutex_message);

    int err, res;
    int data = 0;

    dprintf(1, "\n\nop received %d\n", msg_resp.op);
    switch (msg_resp.op) {
        case 1:
            res = init();
            break;
        case 2:
            res = set_value(msg_resp.key, msg_resp.value1, msg_resp.value2, msg_resp.value3);
            break;
        case 3:
            res = get_value(msg_resp.key, msg_resp.value1, &msg_resp.value2, &msg_resp.value3);
            data = 1;
            break;
        case 4:
            res = modify_value(msg_resp.key, msg_resp.value1, msg_resp.value2, msg_resp.value3);
            break;
        case 5:
            res = delete_value(msg_resp.key);
            break;
        case 6:
            res = exist(msg_resp.key);
            break;
        case 7:
            res = copy_key(msg_resp.key, msg_resp.key2);
            break;
        default:
            res = -1;
            break;
    }
    
    // send the response to the client
    if (data == 1) {
        sprintf(buffer, "%d\n%d\n%f\n%s\n", res, msg_resp.value2, msg_resp.value3, msg_resp.value1);
        err = sendMessage(s_local, buffer, strlen(buffer) + 1);
        if (err == -1) {
            perror("server: send data");
            data = 0;
            return;
        }
    } else {
        err = sendMessage(s_local, (char *)&res, sizeof(char));
        if (err == -1){
            perror("server: send");
            return;
        }
    }
    // close the socket
    close(s_local);
    pthread_exit(NULL);
}

// ESTRUCTURA SOCKET TCP DEL SERVIDOR
// 1- Abrir el socket
// 2- Asignarle una dirección
// 3- Escuchar en el socket
// 4- Aceptar conexiones
// 5- Recibir datos
// 6- Enviar datos
// 7- Cerrar el socket
int main(int argc, char *argv[]) {
    // si mandamos un double tal cual, se considerará error SLL
    int err;
    struct sockaddr_in server_addr,  client_addr;
    socklen_t size;
    int sd; // socket descriptor of the server
    int sc; // socket connection with client
    char *port;
    int optval = 1;

    if (argc != 2) {
        printf("Not enough arguments\n");
        return -1;
    }
    port = argv[1];
    // we create the socket
    if ((sd =  socket(AF_INET, SOCK_STREAM, 0))<0){
        printf ("SERVER: Error en el socket");
        return (0);
    }
    
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));
    // we initialize the server address
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port        = htons(atoi(port));

    // we assign the server address to the socket created
    err = bind(sd, (const struct sockaddr *)&server_addr,
			sizeof(server_addr));
	if (err == -1) {
		perror("bind");
		return -1;
	}
    
    // socket starts listening
    err = listen(sd, SOMAXCONN);
	if (err == -1) {
		perror("listen");
		return -1;
	}

    size = sizeof(client_addr);

    // ***concurrency***
    pthread_t thread;
    pthread_attr_t attr;
    // initialize the mutex and condition variables
    pthread_mutex_init(&mutex_message, NULL);
    pthread_cond_init(&cond_message, NULL);

    pthread_attr_init(&attr);
    // attributes => independent threads
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    struct message msg_received, msg;

    // infinite loop waiting for requests
    
    while (1) {
        dprintf(1, "waiting for conection...\n");

        // first we connect with the client
        sc = accept(sd, (struct sockaddr *)&client_addr, (socklen_t *)&size);
        if (sc == -1) {
            perror("error: accept");
            return -1;
        }
        dprintf(1, "accepted connection from IP: %s   Port: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        
        
        //reading op
        readLine(sc, buffer, sizeof(uint16_t) + 1);
        msg.op = atoi(buffer);
        memset(buffer, 0, 10);

        // reading key
        readLine(sc, buffer, sizeof(int) + 1);
        msg.key = atoi(buffer);
        memset(buffer, 0, 10);

        // reading key2
        readLine(sc, buffer, sizeof(int) + 1);
        msg.key2 = atoi(buffer);
        memset(buffer, 0, 10);

        // reading value2
        readLine(sc, buffer, sizeof(int) + 1);
        msg.value2 = atoi(buffer);
        memset(buffer, 0, 33);


        // reading value3
        readLine(sc, buffer, sizeof(double) + 1);
        msg.value3 = atof(buffer);
        memset(buffer, 0, 33);

        // reading value1
        readLine(sc, buffer, 257);
        strcpy(msg.value1, buffer);
        memset(buffer, 0, sizeof(buffer));

        msg.s = sc;


        // then we process the message
        pthread_create(&thread, &attr, (void *)process_message, (void *)&msg);
        pthread_mutex_lock(&mutex_message);
        while (not_message_copied == 1) {
            pthread_cond_wait(&cond_message, &mutex_message);
        }
        not_message_copied = 1;
        pthread_mutex_unlock(&mutex_message);

        // close connection
        //close(sc);
    }
    // close socket
    close(sd);
    return 0;
}
