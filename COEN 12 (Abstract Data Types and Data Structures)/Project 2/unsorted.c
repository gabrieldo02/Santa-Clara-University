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

/* Big-O Notation: O(n) */
static int search(SET *sp, char *elt) // sequential search to locate an element in the array
{
    int i;
    for (i=0;i<sp->count;i++)
    {
        if(strcmp(sp->data[i], elt)==0) // compare strings
            return i; // return position if found
    }
    return -1; // return -1 if not found
}

/* Big-O Notation: O(1) */
void addElement(SET *sp, char *elt) // add elt to the set pointed to by sp
{
    assert((sp != NULL) && (elt != NULL) && (sp->count < sp->length));
    if ((search(sp,elt)) != -1) // search if duplicate found
        return;
    sp->data[sp->count]=strdup(elt); //  allocate memory and copy the string
    sp->count++; // increase counter
}

/* Big-O Notation: O(1) */
void removeElement(SET *sp, char *elt) // remove elt from the set pointed to by sp
{
    assert((sp != NULL) && (elt != NULL));
    int i = search(sp,elt);
    if (i == -1) // if not found
        return;
    if(sp->count == 1) // if there is only 1 element
    {
        free(sp->data[i]);
        sp->count--; // decrease counter
        return;
    }
    free(sp->data[i]);
    sp->data[i] = sp->data[sp->count-1];
    sp->count--;
}

/* Big-O Notation: O(n) */
char *findElement(SET *sp, char *elt) // if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
{
    assert((sp != NULL) && (elt != NULL));
    int i = search(sp,elt);
    if (i == -1) // if not found
        return NULL;
    return sp->data[i]; 
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
