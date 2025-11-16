/*

    List library for C.

    Feel free to use it however you want. But I do not take
    any responsobility for whatever you do with it.

*/

#pragma once

/*
    List data.
*/
typedef struct LST_LIST{
    /* Pointer to the first element. */
    struct LST_ELEMENT * origin;

    /* Length of the list. */
    int length;

    /*
        Add an element at the end of the list.
        All elements must be freed using either clear() or remove().

        \param list list to have element added.
        \param newElement value of the new element. Must be allocated dynamically.
        \param destructor destructor of the value. Used for safely freeing value when removing element.
    */
    void (*add)(struct LST_LIST * list, void * newElement, void (*destructor)(void * val));

    /*
        Remove an element at specified index of the list.

        \param list list to have element removed.
        \param index index on the list that will have element removed.
        \param freeVal pass 1 if you want to free the element value or 0 if not.
    */
    void (*remove)(struct LST_LIST * list, int index, int freeVal);

    /*
        Clear the list. Also a destructor for list.

        \param list list to be cleared.
        \param freeVal pass 1 if you want to free the element value or 0 if not.
    */
    void (*clear)(struct LST_LIST * list, int freeVal);

    /*
        Get value from specified index.

        \param list list to have value returned.
        \param index on the list that will have value returned.

        \returns value of the element.
    */
    void * (*getVal)(struct LST_LIST list, int index);

    /*
        Change value at specified index.

        \param list list to have value changed.
        \param index on the list that will have value changed.
        \param newVal new value. Must be allocated dynamically.
        \param newDestructor destructor of new value. Used for safely freeing value when removing element.
    */
    void (*setVal)(struct LST_LIST list, int index, void * newVal, void (*newDestructor)(void * val));
} List;

/*
    Create list and initialize it.

    \returns a list with loaded function pointers.
*/
List createList(void);