/* Gabriel Do
COEN 12
Project 3 - Part 2
Wednesday 2:15pm */

#include <assert.h> // declaring libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

typedef struct set // declare structure
{
    int count; // number of elements in the array
    int length; // length of the array
    void* *data; // address of the array
    char *flags; // flags for data where 'E' = EMPTY; 'F' = FILLED, 'D' = DELETED
    int (*compare)(); // compare two elements
    unsigned (*hash)();
}SET;

/* Big-O Notation: O(n)  */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) // return a pointer to a new set with a maximum capacity of maxElts
{
    SET *sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count=0;
    sp->length=maxElts;
    sp->compare=compare;
    sp->hash=hash;
    sp->data=malloc(sizeof(void*)*maxElts); // allocate memory for data
    assert(sp->data!=NULL);
    sp->flags=malloc(sizeof(char)*maxElts); // allocate memory for flags
    assert(sp->flags!=NULL);
    int i;
    for (i=0; i<maxElts; i++)
        sp->flags[i] = 'E'; // assign all flags to EMPTY
    return sp;
}

/* Big-O Notation: O(n) */
void destroySet(SET *sp) // deallocate memory associated with the set pointed to by sp
{
    assert(sp!=NULL);
    free(sp->data);
    free(sp->flags);
    free(sp); // free set
}

/* Big-O Notation: O(1) */
int numElements(SET *sp) // return the number of elements in the set pointed to by sp
{
    assert(sp!=NULL);
    return sp->count;
}

/* Big-O Notation: O(1) ideal; O(n) worst */
static int search(SET *sp, void *elt, bool *found) //  auxiliary function search that returns index if found or returns index where elmement would be inserted if not found
{
    assert((sp!=NULL) && (elt!=NULL));
    int home = (*sp->hash)(elt) % sp->length; // home location
    int i;
    int idx; // idx of key
    int deleted_flag = -1; 
    for (i=0;i<sp->length;i++)
    {
        idx = (home + i) % sp->length; // linear probing
        if(sp->flags[idx]=='F') // if spot is FILLED
        {
            if((*sp->compare)(sp->data[idx],elt)==0) // compare; if true, stop; if not true, keep going
            {
                *found=true;
                return idx; // return index of element 
            } 
        }
        else if(sp->flags[idx]=='D') // if spot is DELETED
        {
            if(deleted_flag == -1)
                deleted_flag = idx; // keep track of first deleted spot and keep going
        }
        else if (sp->flags[idx]=='E') // if spot is EMPTY
        { // return index where element would be inserted
            *found=false;
            if (deleted_flag == -1)
                return idx; // return the empty spot
            return deleted_flag; // return the first deleted spot
        }
    }
    *found=false;
    return deleted_flag;
}

/* Big-O Notation: O(1) ideal; O(n) worst */
void addElement(SET *sp, void *elt) // add elt to the set pointed to by sp
{
    assert((sp != NULL) && (elt != NULL) && (sp->count < sp->length));
    bool found;
    int idx = search(sp,elt,&found);
    if (found == true) // if duplicate found
        return;
    sp->data[idx]=elt; //  add element to data but does not allocate memory 
    sp->flags[idx]='F'; // change flags to FILLED
    sp->count++; // increase counter
}

/* Big-O Notation: O(1) ideal; O(n) worst */
void removeElement(SET *sp, void *elt) // remove elt from the set pointed to by sp
{
    assert((sp != NULL) && (elt != NULL));
    bool found;
    int idx = search(sp,elt,&found);
    if (found == false) // if not found
        return;
    sp->data[idx]=NULL;
    sp->flags[idx]='D'; // change flags to DELETED
    sp->count--;
}

/* Big-O Notation: O(1) ideal; O(n) worst */
void *findElement(SET *sp, void *elt) // if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
{
    assert((sp != NULL) && (elt != NULL));
    bool found;
    int idx = search(sp,elt,&found);
    if (found == false) // if not found
        return NULL;
    return sp->data[idx]; 
}

/* Big-O Notation: O(n) */
void *getElements(SET *sp) // allocate and return an array of elements in the set pointed to by sp
{
    assert(sp != NULL);
    int i, j=0;
    void **elts=malloc(sizeof(void*)*sp->count);
    assert(elts != NULL);
    for (i=0; i<sp->length; i++)
    {
        if(sp->flags[i]=='F') // if flag is FILLED
        {
            elts[j]=sp->data[i];
            j++;
        }
    }
    return elts;
}



