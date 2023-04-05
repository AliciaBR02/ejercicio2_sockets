#include <stdio.h>
#include "claves/claves.h"

int main(void) {
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
    /*
    // testing modify_value
    int test_modify_value = client_modify_value(2, "modified_2", 4, 3.57);
    printf("Modify second element: %d \n", test_modify_value);

    // testing delete_value
    int test_delete_value = client_delete_value(3);
    printf("Delete third element: %d \n\n", test_delete_value);
    
    // testing exist
    int test_exist1 = client_exist(1);
    int test_exist2 = client_exist(2);
    int test_exist3 = client_exist(3);
    int test_exist4 = client_exist(4);
    int test_exist5 = client_exist(8);
    printf("Exist first element: %d \n", test_exist1);
    printf("Exist second element: %d \n", test_exist2);
    printf("Exist third element (should not): %d \n", test_exist3);
    printf("Exist fourth element: %d \n", test_exist4);
    printf("Exist fifth element (should not): %d \n", test_exist5);

    // testing copy_key
    int test_copy_key1 = client_copy_key(4, 6);
    printf("Copy third element to fourth element: %d \n", test_copy_key1);

    // testing set_value for value1 with more than 256 characters
    int test_set_value_wrong_value1 = client_set_value(5, "This is a very long string that should not be accepted by the server because it is longer than 256 charactersThis is a very long string that should not be accepted by the server because it is longer than 256 charactersThis is a very long string that should not be accepted by the server because it is longer than 256 characters", 7, 4.12);
    printf("Insert fifth element: %d \n", test_set_value_wrong_value1);*/

    return 0;
}