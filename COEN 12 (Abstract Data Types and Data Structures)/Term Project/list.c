/* Gabriel Do
COEN 12
Term Project
Wednesday 2:15pm */

#include <assert.h> // declaring libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

typedef struct node
{
    int count; /* number of entries in array */
    int length; /* length of allocated array */
    int first; /* index of first slot */
    void **data; /* allocated array of entries */
    struct node *next;
    struct node *prev;
}NODE;

typedef struct list
{
    int count; // number of nodes in list 
    NODE *head; // head node
    NODE *tail; // tail node
}LIST;
    
/* return a pointer to a new list 
Big-O Notation: O(1) */
LIST *createList(void)
{
    LIST *lp = malloc(sizeof(LIST)); // allocate memory for list
    assert(lp!=NULL);
    NODE *np = malloc(sizeof(NODE)); // allocate memory for node
    assert(np!=NULL);
    np->count=0;
    np->length=8; // start array at small size; length shown in figure 1
    np->first=0;
    np->data=malloc(sizeof(void*)*np->length); // allocate memory for data
    assert(np->data!=NULL);
    lp->count=0;
    lp->head=lp->tail=np;
    return lp;
}

/* deallocate memory associated with the list pointed to by lp 
Big-O Notation: O(n) */
void destroyList(LIST *lp)
{
    assert(lp!=NULL);
    NODE *pDel = lp->head;
    NODE *pNext;
    while (pDel!=NULL)
    {
        pNext=pDel->next;
        free(pDel->data);
        free(pDel);
        pDel=pNext;
    }
    free(lp); // free list
}

/* return the number of items in the list pointed to by lp
Big-O Notation: O(1) */
int numItems(LIST *lp)
{
    assert(lp!=NULL);
    return lp->count;
}

/* add item as the first item in the list pointed to by lp
Big-O Notation: O(1) */
void addFirst(LIST *lp, void *item)
{
    assert(lp!=NULL && item!=NULL);
    if (lp->head->count==lp->head->length) // if array in first node full
    {
        NODE *pNew=malloc(sizeof(NODE));
        assert(pNew!=NULL);
        pNew->prev=NULL;
        pNew->data=malloc(sizeof(void*)*lp->head->length*2); // allocate new node
        pNew->next=lp->head;
        lp->head->prev=pNew;
        pNew->length=lp->head->length*2;
        lp->head=pNew; // make the new node the new first node
        pNew->first=0;
        pNew->count=0;
    }
    int idx = (lp->head->first + lp->head->length-1)%(lp->head->length); // hashing to find index of front of array in first node: (f+n−1) % m
    lp->head->first=idx; // make it the index of first slot
    lp->head->data[idx]=item; // add item in front of first node
    lp->head->count++;
    lp->count++;
}

/* add item as the last item in the list pointed to by lp 
Big-O Notation: O(1) */
void addLast(LIST *lp, void *item)
{
    assert(lp!=NULL && item!=NULL);
    if (lp->tail->count == lp->tail->length) // if array in last node full
    {
        NODE *pNew=malloc(sizeof(NODE));
        assert(pNew!=NULL);
        pNew->next=NULL;
        pNew->data=malloc(sizeof(void*)*lp->tail->length*2); // allocate new node
        pNew->prev=lp->tail;
        lp->tail->next=pNew;
        pNew->length=lp->tail->length*2;
        lp->tail=pNew; // make the new node the new first node
        pNew->first=0;
        pNew->count=0;
    }
    int idx = (lp->tail->first + lp->tail->count)%(lp->tail->length); // hashing to find index of rear of array in last node
    lp->tail->data[idx]=item; // add item in rear of last node
    lp->tail->count++;
    lp->count++;
}

/* remove and return the first item in the list pointed to by lp; the list must not be empty
Big-O Notation: O(1) */
void *removeFirst(LIST *lp)
{
    assert(lp!=NULL);
    if(lp->head->count==0) // if array empty
    {
        NODE *pDel=lp->head;
        lp->head=lp->head->next; // make the next node the new first node
        lp->head->prev=NULL;
        free(pDel->data);
        free(pDel);
    }
    void *temp=lp->head->data[lp->head->first]; // copy of front of array in first node
    int idx = (lp->head->first+1)%(lp->head->length); // index of new first slot
    lp->head->first=idx; // make new first slot the front of the array)
    lp->head->count--;
    lp->count--;
    return temp;
}

/* remove and return the last item in the list pointed to by lp; the list must not be empty
Big-O Notation: O(1) */
void *removeLast(LIST *lp)
{
    assert(lp!=NULL);
    if(lp->tail->count==0) // if array empty
    {
        NODE* pDel = lp->tail;
        lp->tail = lp->tail->prev; // make the prev node the new last node
        lp->tail->next = NULL;
        free(pDel->data); // free data
        free(pDel); // free node
    }
    int idx=(lp->tail->first+lp->tail->count)%(lp->tail->length); // index of rear slot
    void *temp=lp->tail->data[idx]; // copy of rear of array in last node
    lp->tail->count--;
    lp->count--;
    return temp;
}

/* return the item at position index in the list pointed to by lp; the index must be within range
Big-O Notation: O(logn) */
void *getItem(LIST *lp, int index)
{
    assert(lp!=NULL);
    assert(index>=0 && index<lp->count); // within range

    NODE *pGet = lp->head; // // walking pointer/node for traversal 
    while(index>=pGet->count)
    {
        index-=pGet->count; // decrease index
        pGet=pGet->next;
    }
    int idx = (pGet->first+index)%(pGet->length); // index
    void *temp=pGet->data[idx]; // copy
    return temp;
}

/* Big-O Notation: O(logn) */
void setItem(LIST *lp, int index, void *item)
{
    assert(lp!=NULL && item !=NULL);
    assert(index >= 0 && index < lp->count); // within range
    NODE *pSet = lp->head; // // walking pointer/node for traversal 
    while(index>=pSet->count)
    {
        index-=pSet->count; // decrease index
        pSet=pSet->next;
    }
    int idx = (pSet->first+index)%pSet->length; // index
    pSet->data[idx]=item; // set the item at position index in the list pointed to by lp
}


