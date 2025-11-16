#include "../include/list.h"

#include <stdio.h>
#include <stdlib.h>

struct LST_ELEMENT{
    struct LST_ELEMENT * next;
    void * val;
    void (*valDestructor)(void * val);
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

void add(List * list, void * newElement, void (*destructor)(void * val)){
    if(!newElement){
        printf("List.add(): Cannot add NULL element.\n");
        return;
    }

    if(!destructor){
        printf("List.add(): Cannot attach NULL destructor.\n");
        return;
    }

    Element * new = malloc(sizeof(Element));
    new->val = newElement;
    new->next = NULL;
    new->valDestructor = destructor;

    Element * last = gotoIndex(*list, list->length - 1);

    if(!last) list->origin = new;
    else last->next = new;

    list->length++;
}

void removeElement(List * list, int index, int freeVal){
    if(index < 0 || index >= list->length){
        printf("List.remove(): Index is out of bounds\n");
        return;
    } 

    Element * removeMe = gotoIndex(*list, index);
    Element * previous = gotoIndex(*list, index - 1);
    Element * next = removeMe->next;

    if(!previous) list->origin = next;
    else previous->next = next;

    if(freeVal) removeMe->valDestructor(removeMe->val);
    free(removeMe);

    list->length--;
}

void clear(List * list, int freeVal){
    while(0 < list->length){
        removeElement(list, 0, freeVal);
    }

    list->origin = NULL;
}

void * getVal(List list, int index){
    if(index < 0 || index >= list.length){
        printf("List.getVal(): Index is out of bounds\n");
        return NULL;
    }

    return gotoIndex(list, index)->val;
}

void setVal(List list, int index, void * newVal, void (*destructor)(void * val)){
    if(index < 0 || index >= list.length){
        printf("List.setVal(): Index is out of bounds\n");
        return;
    }

    if(!destructor){
        printf("List.setVal(): Cannot attach NULL destructor.\n");
        return;
    }
    
    Element * el = gotoIndex(list, index);
    el->val = newVal;
    el->valDestructor = destructor;
}

List createList(void){
    return(List){
        NULL,
        0,
        &add,
        &removeElement,
        &clear,
        &getVal,
        &setVal
    };
}