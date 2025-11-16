#pragma once

typedef struct LST_LIST{
    struct LST_ELEMENT * origin;
    int length;

    void (*add)(struct LST_LIST * list, void * newElement);
    void (*remove)(struct LST_LIST * list, int index, int freeVal);
    void (*clear)(struct LST_LIST * list, int freeVal);
    void * (*getVal)(struct LST_LIST list, int index);
    void (*setVal)(struct LST_LIST list, int index, void * newVal);
} List;

List createList(void);