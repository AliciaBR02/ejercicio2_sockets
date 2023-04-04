#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include "operaciones/operaciones.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include "sockets/sockets.h"

// threads and mutexes
pthread_cond_t cond_message;
pthread_mutex_t mutex_message;
int not_message_copied = 1;

// function to process the message and execute the requested operation
void process_message(int s) {

    // copy the descriptor to a local variable
    int s_local;
    pthread_mutex_lock(&mutex_message);
    // copy the message to the global variable
    s_local = (* (int *) s);
    not_message_copied = 0;
    pthread_cond_signal(&cond_message);
    pthread_mutex_unlock(&mutex_message);

    // execute the requested operation
    switch (msg_resp.op) {
        case 1:
            msg_resp.res = init();
            break;
        case 2:
            msg_resp.res = set_value(msg_resp.key, msg_resp.value1, msg_resp.value2, msg_resp.value3);
            break;
        case 3:
            msg_resp.res = get_value(msg_resp.key, msg_resp.value1, &msg_resp.value2, &msg_resp.value3);
            break;
        case 4:
            msg_resp.res = modify_value(msg_resp.key, msg_resp.value1, msg_resp.value2, msg_resp.value3);
            break;
        case 5:
            msg_resp.res = delete_value(msg_resp.key);
            break;
        case 6:
            msg_resp.res = exist(msg_resp.key);
            break;
        case 7:
            msg_resp.res = copy_key(msg_resp.key, msg_resp.key2);
            break;
        default:
            msg_resp.res = -1;
            break;
    }
    
    // send the response to the client
    err = sendMessage(s, (char *) &msg_resp, sizeof(struct message));
    if (err == -1){
        perror("server: send");
        return;
    }
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
    //int val;

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


    // infinite loop waiting for requests
    while (1) {
        dprintf(1, "waiting for conection...");

        // first we connect with the client
        sc = accept(sd, (struct sockaddr *)&client_addr, (socklen_t *)&size);
        if (sc == -1) {
            perror("error: accept");
            return -1;
        }
        dprintf(1, "accepted connection de IP: %s   Puerto: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        
        // then we process the message
        pthread_create(&thread, &attr, (void *)process_message, (void *)&sd);

        pthread_mutex_lock(&mutex_message);
        while (not_message_copied == 1) {
            pthread_cond_wait(&cond_message, &mutex_message);
        }
        not_message_copied = 1;
        pthread_mutex_unlock(&mutex_message);


        // close connection
        close(sc);
    }
    // close socket
    close(sd);
    return 0;
}
