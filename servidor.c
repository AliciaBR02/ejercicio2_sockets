#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "operaciones/operaciones.h"
#include <sys/socket.h>

/*
// function to process the message and execute the requested operation
void process_message(struct message *msg) {    
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
    q_client = mq_open(msg_resp.client_queue_name, O_WRONLY);
    if (q_client < 0) {
        perror("mq_open(q_client)");
        mq_close(q_server);
    }
    if (mq_send(q_client, (const char *)&msg_resp, sizeof(msg_resp), 0) < 0) {
        perror("mq_send(q_client)");
        mq_close(q_server);
        mq_close(q_client);
    }
}*/

int main(void) {
    // si mandamos un double tal cual, se considerará error SLL
    int val;
    struct sockaddr_in server_addr,  client_addr;
    int sd;
    if ((sd =  socket(AF_INET, SOCK_STREAM, 0))<0){
                printf ("SERVER: Error en el socket");
                return (0);
        }
        val = 1;
        setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *) &val, sizeof(int));

	bzero((char *)&server_addr, sizeof(server_addr));
    	server_addr.sin_family      = AF_INET;
    	server_addr.sin_addr.s_addr = INADDR_ANY;
    	server_addr.sin_port        = htons(4200);

    	err = bind(sd, (const struct sockaddr *)&server_addr,
			sizeof(server_addr));
	if (err == -1) {
		printf("Error en bind\n");
		return -1;
	}

    	err = listen(sd, SOMAXCONN);
	if (err == -1) {
		printf("Error en listen\n");
		return -1;
	}
    return 0;
}
