/* Gabriel Do
COEN 12
Project 4 - Part 1
Wednesday 2:15pm */

#include <assert.h> // declaring libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

typedef struct node
{
    void *data;
    struct node *next;
    struct node *prev;
}NODE;

typedef struct list
{
    int count;
    NODE *head; // sentinel node or first node; dummy node
    int (*compare)(); // compare two elements
}LIST;

/* return a pointer to a new list using compare as its comparison function, which may be NULL 
Big-O Notation: O(1) */
LIST *createList(int (*compare)())
{
    LIST *lp = malloc(sizeof(LIST)); // allocate memory for list
    assert(lp!=NULL);
    lp->count=0;
    lp->head=malloc(sizeof(NODE)); // allocate memory for head node
    assert(lp->head!=NULL);
    lp->compare=compare;
    lp->head->next=lp->head; // make list circular
    lp->head->prev=lp->head;
    return lp;
}

/* deallocate memory associated with the list pointed to by lp
Big-O Notation: O(n) */
void destroyList(LIST *lp)
{
    assert(lp!=NULL);
    NODE *pDel = lp->head;
    NODE *pNext;
    do
    {
        pNext = pDel->next;
        free(pDel);
        pDel=pNext;
    } while (pDel!=lp->head);
    free(lp);
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
    NODE *pNew=malloc(sizeof(NODE));
    assert(pNew!=NULL);
    pNew->data=item;
    lp->head->next->prev=pNew; // point to dummy node
    pNew->next=lp->head->next; // setting up previous and next of new node
    pNew->prev=lp->head;
    lp->head->next=pNew; // update pointer
    lp->count++;
}

/* add item as the last item in the list pointed to by lp
Big-O Notation: O(1) */ 
void addLast(LIST *lp, void *item)
{
    assert(lp!=NULL && item!=NULL);
    NODE *pNew=malloc(sizeof(NODE));
    assert(pNew!=NULL);
    pNew->data=item;
    lp->head->prev->next=pNew; // point to dummy node
    pNew->next=lp->head; // setting up previous and next of new node
    pNew->prev=lp->head->prev; 
    lp->head->prev=pNew; // update pointer
    lp->count++;
}

/* remove and return the first item in the list pointed to by lp ; the list must not be empty
Big-O Notation: O(1) */ 
void *removeFirst(LIST *lp)
{
    assert(lp!=NULL);
    NODE *pDel = lp->head->next; // first item 
    void *temp=pDel->data; // keep track of node data
    lp->head->next=pDel->next;
    pDel->next->prev=lp->head;
    free(pDel);
    lp->count--;
    return temp;
}

/* remove and return the last item in the list pointed to by lp ; the list must not be empty
Big-O Notation: O(1) */ 
void *removeLast(LIST *lp)
{
    assert(lp!=NULL);
    NODE *pDel = lp->head->prev; // last item
    void *temp=pDel->data; // keep track of node data
    lp->head->prev=pDel->prev;
    pDel->prev->next=lp->head;
    free(pDel);
    lp->count--;
    return temp;
}

/* return, but do not remove, the first item in the list pointed to by lp ; the list must not be empty
Big-O Notation: O(1) */
void *getFirst(LIST *lp)
{
    assert(lp!=NULL);
    return lp->head->next->data;
}

/* return, but do not remove, the last item in the list pointed to by lp ; the list must not be empty
Big-O Notation: O(1) */
void *getLast(LIST *lp)
{
    assert(lp!=NULL);
    return lp->head->prev->data;
}

/* if item is present in the list pointed to by lp then remove it; the comparison function must not be NULL
Big-O Notation: O(n) */
void removeItem(LIST *lp, void *item)
{
    assert(lp!=NULL && item!=NULL && lp->compare!=NULL);
    NODE *pDel=lp->head->next; // walking pointer for traversal
    int i;
    for (i=0;i<lp->count;i++)
    {
        if((*lp->compare)(pDel->data,item)==0)
        {
            pDel->prev->next=pDel->next;
            pDel->next->prev=pDel->prev;
            free(pDel);
            lp->count--;
        }
        pDel=pDel->next;
    }
}

/*if item is present in the list pointed to by lp then return the matching item, otherwise return NULL; the comparison function must not be NULL
Big-O Notation: O(n) */
void *findItem(LIST *lp, void *item)
{
    assert(lp!=NULL && item !=NULL && lp->compare!=NULL);
    NODE *pFind = lp->head->next; // // walking pointer for traversal
    int i;
    for (i=0;i<lp->count;i++)
    {
        if((*lp->compare)(pFind->data,item)==0)
            return pFind->data;
        pFind=pFind->next;
    }
    return NULL;
}

/* allocate and return an array of items in the list pointed to by lp
Big-O Notation: O(n) */
void *getItems(LIST *lp)
{
    assert(lp!=NULL);
    void **array = malloc(sizeof(void*)*lp->count);
    assert(array!=NULL);
    NODE *pGet = lp->head->next; // // walking pointer for traversal 
    int i;
    for(i=0;i<lp->count;i++)
    {
        array[i]=pGet->data;
        pGet=pGet->next;
    }
    return array;
}

