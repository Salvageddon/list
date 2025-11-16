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

    list.add(&list, ttest);
    
    printf("%d\n", list.length);

    list.clear(&list, 1);

    printf("%d\n", list.length);

    return 0;
}