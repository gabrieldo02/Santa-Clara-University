/* Gabriel Do
COEN 12
Project 2
Wednesday 2:15pm */

# include <assert.h> // declaring libraries
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "set.h"

typedef struct set // declare structure
{
    int count; // number of elements in the array
    int length; // length of the array
    char* *data; // address of the array
}SET;

/* Big-O Notation: O(1)  */
SET *createSet(int maxElts) // return a pointer to a new set with a maximum capacity of maxElts
{
    SET *sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count=0;
    sp->length=maxElts;
    sp->data=malloc(sizeof(char*)*maxElts);
    assert(sp->data!=NULL);
    return sp;
}

/* Big-O Notation: O(n) */
void destroySet(SET *sp) // deallocate memory associated with the set pointed to by sp
{
    assert(sp!=NULL);
    int i;
    for(i=0;i<sp->count;i++)
        free(sp->data[i]);
    free(sp->data);
    free(sp); // free set
}

/* Big-O Notation: O(1) */
int numElements(SET *sp) // return the number of elements in the set pointed to by sp
{
    assert(sp!=NULL);
    return sp->count;
}

/* Big-O Notation: O(logn) */
static int search(SET *sp, char *elt, bool *found) //  binary search to locate an element in the array
{
    int lo, hi, mid;
    lo=0;
    hi=sp->count-1;
    while (lo<=hi)
    {
        mid=(lo+hi)/2; // set mid
        if(strcmp(elt, sp->data[mid])<0) // string compare middle element with elt
            hi=mid-1;
        else if(strcmp(elt, sp->data[mid])>0)
            lo=mid+1;
        else // if the string is the middle element
        {
            *found=true;
            return mid;
        }
    }
    *found=false;
    return lo;
}

/* Big-O Notation: O(n) */
void addElement(SET *sp, char *elt) // add elt to the set pointed to by sp
{
    assert((sp != NULL) && (elt != NULL) && (sp->count < sp->length));
    int i;
    bool found;
    int idx = search(sp,elt,&found);
    if (found == true) // if duplicate found
        return;
    for (i=sp->count;i>idx;i--)
        sp->data[i]=sp->data[i-1];
    sp->data[idx]=strdup(elt); //  allocate memory and copy the string
    sp->count++; // increase counter
}

/* Big-O Notation: O(n) */
void removeElement(SET *sp, char *elt) // remove elt from the set pointed to by sp
{
    assert((sp != NULL) && (elt != NULL));
    int i;
    bool found;
    int idx = search(sp,elt,&found);
    if (found == false) // if not found
        return;
    if(sp->count == 1) // if there is only 1 element
    {
        free(sp->data[i]);
        sp->count--; // decrease counter
        return;
    }
    free(sp->data[idx]);
    for(i=idx+1;i<sp->count;i++)
        sp->data[i-1]=sp->data[i];
    sp->count--;
}

/* Big-O Notation: O(logn) */
char *findElement(SET *sp, char *elt) // if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
{
    assert((sp != NULL) && (elt != NULL));
    bool found;
    int idx = search(sp,elt,&found);
    if (found == false) // if not found
        return NULL;
    return sp->data[idx]; 
}

/* Big-O Notation: O(n) */
char **getElements(SET *sp) // allocate and return an array of elements in the set pointed to by sp
{
    assert(sp != NULL);
    char **elements=malloc(sizeof(char*)*sp->count);
    int i;
    for (i=0; i<sp->count; i++)
        elements[i]=sp->data[i];
    return elements;
}