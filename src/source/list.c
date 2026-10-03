#include "../include/list.h"
#include <stdio.h>
#include <stdlib.h>

struct LISTITEM{
    ListItem * next;
    void * val;
    void (*destctor)(void * val);
};

ListItem * createItem(ListItem * next, void * val, void (*destctor)(void * val)){
    ListItem * o = malloc(sizeof(ListItem));

    o->next = next;
    o->val = val;
    o->destctor = destctor;

    return o;
}

void freeItem(ListItem * item, int freevalue){
    if(freevalue) item->destctor(item->val);
    free(item);
}

ListItem * getItem(List list, int index){
    if(index < 0) return NULL;

    ListItem * item = list.origin;

    for(int i = 1; i <= index; i++){
        item = item->next;
    }

    return item;
}

List LST_createList(void){
    return (List){
        NULL,
        0
    };
}

void LST_add(List * target, void * value, void (*destructor)(void * value)){
    if(target == NULL){
        printf("List (add()): Target cannot be NULL.\n");
        return;
    }

    if(value == NULL || destructor == NULL){
        printf("List (add()): Neither the value nor the destructor cannot be NULL.\n");
        return;
    }
    
    ListItem * last = getItem(*target, target->length - 1);
    ListItem * new = createItem(NULL, value, destructor);
    
    if(last == NULL){
        target->origin = new;
    }
    else{
        last->next = new;
    }

    target->length++;
}

void LST_addAt(List * target, int index, void * value, void (*destructor)(void * value)){
    if(target == NULL){
        printf("List (addAt()): Target cannot be NULL.\n");
        return;
    }

    if(index < 0 || index > target->length){
        printf("List (addAt()): Index is invalid.\n");
        return;
    }

    if(value == NULL || destructor == NULL){
        printf("List (addAt()): Neither the value nor the destructor cannot be NULL.\n");
        return;
    }

    if(index == target->length){
        ListItem * selected = getItem(*target, target->length - 1);
        ListItem * new = createItem(NULL, value, destructor);
        
        selected->next = new;
    }
    else{
        ListItem * selected = getItem(*target, index);
        ListItem * prev = getItem(*target, index - 1);
        ListItem * new = createItem(selected, value, destructor);

        if(prev == NULL){
            target->origin = new;
        }
        else{
            prev->next = new;
        }
    }

    target->length++;
}

void LST_remove(List * target, int index, int freevalue){
    if(target == NULL){
        printf("List (remove()): Target cannot be NULL.\n");
        return;
    }

    if(index < 0 || index >= target->length){
        printf("List (remove()): Index is invalid.\n");
        return;
    }

    ListItem * selected = getItem(*target, index);
    ListItem * prev = getItem(*target, index - 1);
    ListItem * next = selected->next;

    if(prev == NULL){
        target->origin = next;
    }
    else{
        prev->next = next;
    }

    freeItem(selected, freevalue);

    target->length--;
}

void * LST_get(List target, int index){
    if(index < 0 || index >= target.length){
        printf("List (get()): Index is invalid. NULL returned.\n");
        return NULL;
    }

    return getItem(target, index)->val;
}

void LST_set(List target, int index, void * value, void (*destructor)(void * value), int freeoldvalue){
    if(index < 0 || index >= target.length){
        printf("List (set()): Index is invalid.\n");
        return;
    }

    if(value == NULL || destructor == NULL){
        printf("List (set()): Neither the value nor the destructor cannot be NULL.\n");
        return;
    }

    ListItem * selected = getItem(target, index);

    if(freeoldvalue) selected->destctor(selected->val);

    selected->val = value;
    selected->destctor = destructor;
}

void LST_clear(List * target, int freevalue){
    if(target == NULL){
        printf("List (clear()): Target cannot be NULL.\n");
        return;
    }
    
    for(int i = target->length - 1; i >= 0; i--){
        freeItem(getItem(*target, i), freevalue);
    }

    target->length = 0;
    target->origin = NULL;
}