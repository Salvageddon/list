#pragma once

typedef struct LISTITEM ListItem;

typedef struct{
    ListItem * origin; //first item on the list
    int length; //item count of the list
} List;

/*
    Initialize List
*/
List LST_createList(void);

/*
    Add item to a list at the end of it
    \param target target list
    \param value object to be added of any type
    \param destructor destructor of added object
*/
void LST_add(List * target, void * value, void (*destructor)(void * value));

/*
    Add item to a list at specified index
    \param target target list
    \param index position on the list to be added at
    \param value object to be added of any type
    \param destructor destructor of added object
*/
void LST_addAt(List * target, int index, void * value, void (*destructor)(void * value));

/*
    Remove item from specified index
    \param target target list
    \param index position on the list to be removed
    \param freeValue pass 1 if you want to invoke the destructor. Otherwise pass 0, but be ware of mem leaks.
*/
void LST_remove(List * target, int index, int freevalue);

/*
    Return item from specified index
    \param target target list
    \param index position on the list to returned
*/
void * LST_get(List target, int index);

/*
    Set an item at specified position on the list
    \param target target list
    \param index position on the list to be changed
    \param value object to be added of any type
    \param destructor destructor of added object
    \param freeOldValue pass 1 if you want to invoke the old value destructor. Otherwise pass 0, but be ware of mem leaks.
*/
void LST_set(List target, int index, void * value, void (*destructor)(void * value), int freeoldvalue);

/*
    Clear the list
    \param target target list
    \param freeValue pass 1 if you want to invoke the destructors. Otherwise pass 0, but be ware of mem leaks.
*/
void LST_clear(List * target, int freevalue);