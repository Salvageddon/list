#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"
#include <salvagames/list.h>

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

    for(int i = 0; i < 19; i++){
        o->dynamic[i] = i + 97;
    }

    o->dynamic[19] = '\0';

    return o;
}

void destroyTest(void * test){
    Test * t = test;

    free(t->dynamic);
    free(t);
}

void displayList(List list){
    for(int i = 0; i < list.length; i++){
        Test * test = LST_get(list, i);
        printf("%d => %d %f %s\n", i, test->a, test->b, test->dynamic);
    }
    printf("\n");
}

int main(){
    printf("AAA\n");
    List list = LST_createList();
    
    LST_add(&list, createTest(10, 0.5F), &destroyTest);
    LST_add(&list, createTest(20, 1.5F), &destroyTest);
    LST_add(&list, createTest(30, 2.5F), &destroyTest);
    LST_add(&list, createTest(40, 3.5F), &destroyTest);
    LST_add(&list, createTest(50, 4.5F), &destroyTest);
    LST_add(&list, createTest(60, 5.5F), &destroyTest);
    LST_add(&list, createTest(70, 6.5F), &destroyTest);

    displayList(list);

    LST_addAt(&list, 3, createTest(80, 7.5F), &destroyTest);

    displayList(list);

    LST_remove(&list, 5, 1);

    displayList(list);

    LST_set(list, 0, createTest(90, 8.5F), &destroyTest, 1);

    displayList(list);

    LST_clear(&list, 1);

    printf("%d\n", list.length);

    return 0;
}