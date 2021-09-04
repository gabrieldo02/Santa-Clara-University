/* Gabriel Do
COEN 12
Project 5 - Part 1
Wednesday 2:15pm */

#include <assert.h> // declaring libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pqueue.h"

#define parent(x) (((x)-1)/2) // parent index
#define left(x) ((x)*2+1) // left child index
#define right(x) ((x)*2+2) // right child index

struct pqueue 
{
    int count; /* number of entries in array */
    int length; /* length of allocated array */
    void **data; /* allocated array of entries */
    int (*compare)(); /* comparison function */
};

/* return a pointer to a new priority queue using compare as its comparison function 
Big-O Notation: (1) */
PQ *createQueue(int (*compare)())
{
    PQ *pq = malloc(sizeof(PQ));
    assert(pq!=NULL);
    pq->count=0;
    pq->length=10; // start array at small size
    pq->compare=compare;
    pq->data=malloc(sizeof(void*)*pq->length); // allocate memory for data
    assert(pq->data!=NULL);
    return pq;
}

/* deallocate memory associated with the priority queue pointed to by pq 
Big-O Notation: O(n) */
void destroyQueue(PQ *pq)
{
    assert(pq!=NULL);
    int i;
    for (i=0;i<pq->count;i++)
        free(pq->data[i]);
    free(pq->data);
    free(pq); // free priority queue
}

/* return the number of entries in the priority queue pointed to by pq 
Big-O Notation: O(1) */
int numEntries (PQ *pq)
{
    assert(pq!=NULL);
    return pq->count;
}

/* add entry to the priority queue pointed to by pq 
Big-O Notation: O(logn) */
void addEntry(PQ *pq, void *entry)
{
    assert(pq!=NULL && entry!=NULL);
    if (pq->count==pq->length) // if priority queue full
    {
        pq->data=realloc(pq->data,sizeof(void*)*pq->length*2); // double array's length
        pq->length*=2;
    }
    pq->data[pq->count]=entry; // place entry at the end of the binary heap
    int idx = pq->count; // current index of entry in array
    while((*pq->compare)(pq->data[idx],pq->data[parent(idx)])<0) // compare if entry is smaller than parent and reheap up by swapping with new parent 
    {
        void *temp=pq->data[parent(idx)];
        pq->data[parent(idx)]=pq->data[idx];
        pq->data[idx]=temp;
        idx=parent(idx); // make parent the new index of entry
    }
    pq->count++;
}


/* remove and return the smallest entry from the priority queue pointed to by pq 
Big-O Notation: O(logn) */
void *removeEntry (PQ *pq)
{
    assert(pq !=NULL);
    void *root = pq->data[0]; // remember root
    pq->data[0]=pq->data[pq->count-1]; // replace root by the last element in the binary heap
    int idx = 0; // index of upstart value (used to be last element)
    int smaller_idx = 0; // index of smaller child
    pq->count--;
    while(left(idx)<pq->count) // while left child exists
    {
        smaller_idx=left(idx);
        if(right(idx)<pq->count) // if right child exists
        {
            if((*pq->compare)(pq->data[right(idx)],pq->data[left(idx)])<0) // compare if right child is smaller than left child
                smaller_idx=right(idx);
        }
        if((*pq->compare)(pq->data[smaller_idx],pq->data[idx])<0) // compare if child is smaller than parent and reheap down by swaping with smaller child
        {
            void *temp=pq->data[smaller_idx];
            pq->data[smaller_idx]=pq->data[idx];
            pq->data[idx]=temp;
            idx=smaller_idx; // update idx
        }
        else
            break;
    }
    return root;
}

