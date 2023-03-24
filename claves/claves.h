#ifndef _CLAVES_H_
#define _CLAVES_H_

#include <mqueue.h>
#include <stdio.h>

int client_init();
int client_set_value(int key, char *value1, int value2, double value3);
int client_get_value(int key, char *value1, int *value2, double *value3);
int client_modify_value(int key, char *value1, int value2, double value3);
int client_delete_value(int key);
int client_exist(int key);
int client_copy_key(int key1, int key2);
#endif