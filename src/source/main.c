#include "../include/list.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int a;
    int b;
    float * dynamic;
} test;

test * createTest(void){
    test * ret = malloc(sizeof(test));

    ret->a = 0;
    ret->b = 0;
    ret->dynamic = malloc(sizeof(float));

    return ret;
}

void freeTest(void * test1){
    free(((test*)test1)->dynamic);
    free(test1);
}

int main(){
    List list = createList();

    test * ttest = createTest();

    ttest->a = 10;
    ttest->b = 20;

    test * ttest2 = createTest();

    ttest2->a = 50;
    ttest2->b = 60;
    *ttest2->dynamic = 10.0F;

    list.add(&list, ttest, &freeTest);
    
    printf("%d\n", list.length);
    printf("%d\n", ((test *)list.getVal(list, 0))->a);

    list.setVal(list, 0, ttest2, &freeTest);

    printf("%d\n", ((test *)list.getVal(list, 0))->a);

    list.clear(&list, 1);

    printf("%d\n", list.length);

    freeTest(ttest);



    return 0;
}