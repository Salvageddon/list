/*
    You can use this main file to learn how the List works.
    Modify it or test it or whatever, have fun :)
*/

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct{
    int a;
    float b;
    char * dynamic;
} Test;

Test * createTest(int a, float b){
    Test * o = malloc(sizeof(Test));

    o->a = a;
    o->b = b;
    o->dynamic = malloc(20);

    for(int i = 0; i < 20; i++){
        o->dynamic[i] = 97 + i;
    }

    return o;
}

void destroyTest(void * t){
    Test * test = (Test *)t;

    free(test->dynamic);
    free(t);
}

int main(){
    List list = LST_createList();

    Test * t1 = createTest(10, 0.5F);
    Test * t2 = createTest(20, 1.5F);
    Test * t3 = createTest(30, 2.5F);
    Test * t4 = createTest(40, 3.5F);
    Test * t5 = createTest(50, 4.5F);

    printf("%d\n", list.length);
    LST_add(&list, t1, &destroyTest);
    LST_add(&list, t2, &destroyTest);
    LST_add(&list, t3, &destroyTest);
    LST_add(&list, t4, &destroyTest);
    LST_add(&list, t5, &destroyTest);
    printf("%d\n", list.length);

    Test * t6 = createTest(0, 0);
    /*
        NOTE: In LST_addAt() indexes equal to the length of a List are allowed,
        because they will just append new element on the end of the list.
        Basically same result as using LST_add().
    */
    LST_addAt(&list, 5, t6, &destroyTest);
    for(int i = 0; i < list.length; i++){
        Test * ttest = LST_get(list, i);
        printf("%d: %d %f %s\n", i, ttest->a, ttest->b, ttest->dynamic);
    }
    printf("%d\n", list.length);

    Test * test = LST_get(list, 0);
    printf("%d %f %s\n", test->a, test->b, test->dynamic);

    Test * oldTest = LST_get(list, 3);
    LST_set(list, 3, createTest(60, 5.5F), &destroyTest, 1);
    Test * newTest = LST_get(list, 3);
    printf("%d %f %s\n\n", newTest->a, newTest->b, newTest->dynamic);

    //NOTE: this will (and should) segfault.
    //printf("%s\n", oldTest->dynamic);
    //destroyTest(oldTest);

    for(int i = 0; i < list.length; i++){
        Test * ttest = LST_get(list, i);
        printf("%d: %d %f %s\n", i, ttest->a, ttest->b, ttest->dynamic);
    }

    LST_remove(&list, 0, 1);
    LST_remove(&list, 1, 1);
    LST_remove(&list, 2, 1);
    printf("\n");

    for(int i = 0; i < list.length; i++){
        Test * ttest = LST_get(list, i);
        printf("%d: %d %f %s\n", i, ttest->a, ttest->b, ttest->dynamic);
    }

    printf("%d\n", list.length);
    LST_clear(&list, 1);
    printf("%d\n", list.length);

    //NOTE: this will also segfault.
    //printf("%s\n", t1->dynamic);

    return 0;
}