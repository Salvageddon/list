#include "../include/list.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct LST_ListElement{
    struct LST_ListElement * next;
    void * val;
    void (*destructor)(void * val);
} Element;

Element * createElement(void * val, void (*destructor)(void * val)){
    Element * o = malloc(sizeof(Element));

    o->next = NULL;
    o->val = val;
    o->destructor = destructor;

    return o;
}

Element * getElement(List l, int index){
    if(index < 0){
        return NULL;
    }

    Element * el = l.origin;

    for(int i = 1; i <= index; i++){
        el = el->next;
    }

    return el;
}

void freeElement(Element * freeMe, int freeVal){
    if(freeVal) freeMe->destructor(freeMe->val);
    free(freeMe);
}

int indexError(List l, int index){
    return index < 0 || index >= l.length;
}

List LST_createList(void){
    return (List){
        NULL,
        0
    };
}

void LST_add(List * list, void * value, void (*destructor)(void * value)){
    if(list == NULL){
        printf("List (add()): List cannot be NULL\n");
        return;
    }

    if(value == NULL || destructor == NULL){
        printf("List (add()): Cannot add NULL values or destructors\n");
        return;
    }

    Element * last = getElement(*list, list->length - 1);
    Element * new = createElement(value, destructor);

    if(!last) list->origin = new;
    else last->next = new;

    list->length++;
}

void LST_addAt(List * list, int index, void * value, void (*destructor)(void * value)){
    if(list == NULL){
        printf("List (addAt()): List cannot be NULL\n");
        return;
    }

    if(value == NULL || destructor == NULL){
        printf("List (addAt()): Cannot add NULL values or destructors\n");
        return;
    }

    if(indexError(*list, index) && (index != list->length)){
        printf("List (addAt()): Index was out of range\n");
        return;
    }

    Element * new = createElement(value, destructor);
    Element * prev = getElement(*list, index - 1);

    if(!prev){
        new->next = list->origin;
        list->origin = new;
    }
    else{
        new->next = prev->next;
        prev->next = new;
    }

    list->length++;
}

void * LST_get(List list, int index){
    if(indexError(list, index)){
        printf("List (get()): Index was out of range\n");
        return NULL;
    }

    return getElement(list, index)->val;
}

void LST_set(List list, int index, void * value, void (*destructor)(void * value), int freeOldValue){
    if(indexError(list, index)){
        printf("List (set()): Index was out of range\n");
        return;
    }

    if(value == NULL || destructor == NULL){
        printf("List (set()): Cannot add NULL values or destructors\n");
        return;
    }

    Element * el = getElement(list, index);

    if(freeOldValue) el->destructor(el->val);

    el->val = value;
    el->destructor = destructor;
}

void LST_remove(List * list, int index, int freeValue){
    if(list == NULL){
        printf("List (remove()): List cannot be NULL\n");
        return;
    }

    if(indexError(*list, index)){
        printf("List (remove()): Index was out of range\n");
        return;
    }

    Element * removeMe = getElement(*list, index);
    Element * prev = getElement(*list, index - 1);
    Element * next = removeMe->next;

    if(!prev) list->origin = next;
    else prev->next = next;

    freeElement(removeMe, freeValue);

    list->length--;
}

void LST_clear(List * list, int freeValue){
    if(list == NULL){
        printf("List (clear()): List cannot be NULL\n");
        return;
    }

    while(0 < list->length){
        LST_remove(list, 0, freeValue);
    }
}