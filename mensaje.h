#ifndef _MENSAJE_H_
#define _MENSAJE_H_

#define MAX 256

struct message {
    int8_t op;
    int key;
    int key2;
    char value1[MAX];
    int value2;
    double value3;
    char *ptr1;
    int *ptr2;
    double *ptr3;
    int8_t res;
};

#endif