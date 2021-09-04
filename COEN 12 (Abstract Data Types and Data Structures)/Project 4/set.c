/* Gabriel Do
COEN 12
Project 4 - Part 2
Wednesday 2:15pm */

#include <assert.h> // declaring libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
#include "list.h"
#include "list.c"
#define alpha 20

struct set // declare structure
{
    int count; // number of elements in the array
    int length; // length of the array
    LIST **lists; // pointer to a list
    int (*compare)(); // compare two elements
    unsigned (*hash)();
};

/* return a pointer to a new set with a maximum capacity of maxElts/alpha
Big-O Notation: O(n) */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    SET *sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count=0;
    sp->length=maxElts/alpha;
    sp->compare=compare;
    sp->hash=hash;
    sp->lists=malloc(sizeof(LIST*)*sp->length);
    assert(sp->lists!=NULL);
    int i;
    for (i=0;i<sp->length;i++) // traverse list
        sp->lists[i]=createList(compare); // from list ADT
    return sp;
}

/* deallocate memory associated with the set pointed to by sp
Big-O Notation: O(n) */
 void destroySet(SET *sp)
 {
    assert(sp!=NULL);
    int i;
    for (i=0;i<sp->length;i++) // traverse list
        destroyList(sp->lists[i]); // from list ADT
    free(sp->lists); // free lists
    free(sp); // free set
 }

 /* return the number of elements in the set pointed to by sp
Big-O Notation: O(1) */
int numElements(SET *sp)
{
    assert(sp!=NULL);
    return sp->count;
}

/* add elt to the set pointed to by sp
Big-O Notation: O(n) */
void addElement(SET *sp, void *elt)
{
    assert(sp!=NULL && elt!=NULL);
    int idx = (*sp->hash)(elt) % sp->length;
    if (findItem(sp->lists[idx],elt)==NULL) // from list ADT; traverse to find if elt is not present in list 
    {
        addFirst(sp->lists[idx],elt); //from list ADT
        sp->count++;
    }
}

/* remove elt from the set pointed to by sp
Big-O Notation: O(n) */
void removeElement(SET *sp, void *elt)
{
    assert(sp!=NULL && elt!=NULL);
    int idx = (*sp->hash)(elt) % sp->length;
    if (findItem(sp->lists[idx],elt)!=NULL) // // from list ADT; traverse to find if elt is present in list 
    {
        removeItem(sp->lists[idx],elt); // from list ADT
        sp->count--;
    }
}

/* if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
Big-O Notation: O(n) */
void *findElement(SET *sp, void *elt)
{
    assert(sp!=NULL && elt!=NULL);
    int idx = (*sp->hash)(elt) % sp->length;
    return findItem(sp->lists[idx],elt); // from list ADT
}

/* allocates and returns one array of the elements in all the lists in set 
Big-O Notation: O(n^2) */
void *getElements(SET *sp)
{
    assert(sp!=NULL);
    int i, j;
    int counter=0;
    void **elts=malloc(sizeof(void*)*sp->count);
    assert(elts != NULL);
    void **copyList;
    for (i=0; i<sp->length; i++)
    {
        copyList = getItems(sp->lists[i]); // from list ADT
        for (j=0;j<numItems(sp->lists[i]);j++) // go into each list
        {
            elts[counter]=copyList[j];
            counter++;
        }
    }
    return elts;
}


