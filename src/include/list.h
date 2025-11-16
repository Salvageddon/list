#pragma once

typedef struct LST_LIST{
    struct LST_ELEMENT * origin;
    int length;

    void (*add)(struct LST_LIST *, void *);
    void (*remove)(struct LST_LIST * list, int index, int freeVal);
    void (*clear)(struct LST_LIST * list, int freeVal);
} List;

List createList(void);