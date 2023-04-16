#include <stdio.h>
#include "claves/claves.h"

int main(void) {
    printf("-------------------------------------\n");
    printf("Client 1\n");
    printf("-------- RESULTS OF EXECUTION --------\n\n");
    
    // testing init
    int test_init = client_init();
    printf("Result of init: %d\n\n", test_init);

    // testing set_value
    
    int test_set_value1 = client_set_value(1, "insert", 7, 4.12);
    int test_set_value2 = client_set_value(2, "computer", 4, 3.57);
    int test_set_value3 = client_set_value(3, "book", 5, 2.12);
    int test_set_value4 = client_set_value(4, "pen", 3, 1.57);
    printf("Insert first element: %d\n", test_set_value1);
    printf("Insert second element: %d\n", test_set_value2);
    printf("Insert third element: %d\n", test_set_value3);
    printf("Insert fourth element: %d\n", test_set_value4);
    
    // testing get_value
    char value1[256];
    int value2;
    double value3;
    int test_get_value1 = client_get_value(1, value1, &value2, &value3);
    printf("Get first element: %d \n", test_get_value1);
    printf("Value1: %s \n", value1);
    printf("Value2: %d \n", value2);
    printf("Value3: %f \n\n", value3);
    int test_get_value2 = client_get_value(2, value1, &value2, &value3);
    printf("Get second element: %d \n", test_get_value2);
    printf("Value1: %s \n", value1);
    printf("Value2: %d \n", value2);
    printf("Value3: %f \n\n", value3);
    int test_get_value3 = client_get_value(3, value1, &value2, &value3);
    printf("Get third element: %d \n", test_get_value3);
    printf("Value1: %s \n", value1);
    printf("Value2: %d \n", value2);
    printf("Value3: %f \n\n", value3);

    return 0;
}