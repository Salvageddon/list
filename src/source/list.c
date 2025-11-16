#include "../include/list.h"

#include <stdio.h>
#include <stdlib.h>

struct LST_ELEMENT{
    struct LST_ELEMENT * next;
    void * val;
};

typedef struct LST_ELEMENT Element;

Element * gotoIndex(List list, int index){
    if(index < 0) return NULL;

    Element * element = list.origin;

    for(int i = 1; i < index; i++){
        element = element->next;
    }

    return element;
}

void add(List * list, void * newElement){
    if(!newElement){
        printf("List.add(): Cannot add NULL element.\n");
    }

    Element * new = malloc(sizeof(Element));
    new->val = newElement;
    new->next = NULL;

    Element * last = gotoIndex(*list, list->length - 1);

    if(!last) list->origin = new;
    else last->next = new;

    list->length++;
}

void removeElement(List * list, int index, int freeVal){
    if(index < 0 || index >= list->length){
        printf("List.remove(): Index is out of bounds\n");
    } 

    Element * removeMe = gotoIndex(*list, index);
    Element * previous = gotoIndex(*list, index - 1);
    Element * next = removeMe->next;

    if(!previous) list->origin = next;
    else previous->next = next;

    if(freeVal) free(removeMe->val);
    free(removeMe);

    list->length--;
}

void clear(List * list, int freeVal){
    while(0 < list->length){
        removeElement(list, 0, freeVal);
    }
}

List createList(void){
    return(List){
        NULL,
        0,
        &add,
        &removeElement,
        &clear
    };
}