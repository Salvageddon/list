#include "../include/list.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int a;
    int b;
} test;

int main(){
    List list = createList();

    test * ttest = malloc(sizeof(ttest));

    ttest->a = 10;
    ttest->b = 20;

    test * ttest2 = malloc(sizeof(ttest));

    ttest2->a = 50;
    ttest2->b = 60;

    list.add(&list, ttest);
    
    printf("%d\n", list.length);
    printf("%d\n", ((test *)list.getVal(list, 0))->a);

    list.setVal(list, 0, ttest2);

    printf("%d\n", ((test *)list.getVal(list, 0))->a);

    list.clear(&list, 1);

    printf("%d\n", list.length);

    free(ttest);

    return 0;
}