#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int init() {
    FILE *f = fopen("data.txt", "r");
    // create the file if it does not exist
    if (f == NULL) {
        f = fopen("data.txt", "w");
        fclose(f);
    } else {
        fclose(f);
    }
    return 0;
}

int exist(int key) {
    FILE *f = fopen("data.txt", "r");
    // read the file line by line and check if the first number is key
    int k;
    char v1[100];
    int v2;
    double v3;
    while (fscanf(f, "%d %s %d %lf", &k, v1, &v2, &v3) != EOF) {
        if (k == key) {
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return -1;
}

int set_value(int key, char *value1, int value2, double value3) {
    // append the key, value1, value2 and value3 at the end of the file
    if (exist(key) == 0)
        return -1;
    FILE *f = fopen("data.txt", "a");
    fprintf(f, "%d %s %d %lf\n", key, value1, value2, value3);
    fclose(f);
    return 0;
}

int get_value(int key, char *value1, int *value2, double *value3) {
    FILE *f = fopen("data.txt", "r");
    // read the file line by line and check if the first number is the searched key
    int k;
    char v1[256];
    int v2;
    double v3;
    while (fscanf(f, "%d %s %d %lf", &k, v1, &v2, &v3) != EOF) {
        // if we find the key, copy the values to the pointers and return 0
        if (k == key) {
            strcpy(value1, v1);
            *value2 = v2;
            *value3 = v3;
            fclose(f);
            return 0;
        }
    }
    return -1;
}

int delete_value(int key) {
    // we write on a temporal file the data except the key's tuple
    FILE *f = fopen("data.txt", "r");
    FILE *f2 = fopen("data2.txt", "w");
    int k;
    char v1[100];
    int v2;
    double v3;
    while (fscanf(f, "%d %s %d %lf\n", &k, v1, &v2, &v3) != EOF) {
        if (k != key) {
            fprintf(f2, "%d %s %d %lf\n", k, v1, v2, v3);
        }
    }
    // then we rename the temporal file to data.txt
    fclose(f);
    fclose(f2);
    remove("data.txt");
    rename("data2.txt", "data.txt");
    return 0;
}

int modify_value(int key, char *value1, int value2, double value3) {
    int exists = exist(key);
    if (exists == -1)
        return -1;
    // we delete the key and then we insert it again with the new data
    delete_value(key);
    set_value(key, value1, value2, value3);    
    return 0;
}

int copy_key(int key1, int key2) {
    int exists = exist(key1);
    if (exists == -1)
        return -1;
    char value1[256];
    int value2;
    double value3;
    // we get the data of the key1 and then we insert it with the key2
    get_value(key1, value1, &value2, &value3);
    set_value(key2, value1, value2, value3);
    return 0;
}
