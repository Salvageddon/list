/*
    List Library v1.0.0
    copyright (c) 2025-2026 Salvageddon

    You can use this however you want, but I'm not taking any 
    responsobility for whatever you do with it.

    Prefix: LST
*/

#pragma once

/*
    List object.
*/
typedef struct{
    /*Pointer to the first element of the list.*/
    struct LST_ListElement * origin;

    /*Number of elements in the list.*/
    int length;
} List;

/*
    Create a List.
    At this state it doesn't have to be freed in any way.

    \returns the List object.
*/
List LST_createList(void);

/*
    Add an element at the end of a List.

    \param list pointer to the list having element added.
    \param value value of new element. Basically what you're adding.
    \param destructor destructor of the value. 
*/
void LST_add(List * list, void * value, void (*destructor)(void * value));

/*
    Add an element at specified index of a List.
    Passing an index equal to length of the List is allowed.

    \param list pointer to the list having element added.
    \param index index where a new element is added. Existing and next elements are getting pushed forward.
    \param value value of new element. Basically what you're adding.
    \param destructor destructor of the value. 
*/
void LST_addAt(List * list, int index, void * value, void (*destructor)(void * value));

/*
    Get value at specified index on a List.

    \param list pointer to the list having value returned.
    \param index index of the value.

    \returns value found at the index.
*/
void * LST_get(List list, int index);

/*
    Set new value at specified index on the List.
    You can also free the old value.

    \param list pointer to the list having value replaced.
    \param index index of the old value.
    \param value new value.
    \param destructor destructor of the new value. 
    \param freeOldValue pass 1 if you want to free the old value, or 0 if not.
*/
void LST_set(List list, int index, void * value, void (*destructor)(void * value), int freeOldValue);

/*
    Remove element of a List at specified index.
    You can also free the old value.

    \param list pointer to the list having element removed.
    \param index index of the removed element.
    \param freeValue pass 1 if you want to free the value, or 0 if not.
*/
void LST_remove(List * list, int index, int freeValue);

/*
    Truncates a list to length of 0.
    Basically a destructor for List.

    \param list pointer to the list being cleared.
    \param freeValue pass 1 if you want to free all values, or 0 if not.
*/
void LST_clear(List * list, int freeValue);