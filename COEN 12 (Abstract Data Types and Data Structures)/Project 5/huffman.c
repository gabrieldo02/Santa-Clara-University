/* Gabriel Do
COEN 12
Project 5 - Part 2
Wednesday 2:15pm */

#include <assert.h> // declaring libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "pqueue.h"
#include "pack.h"

typedef struct node NODE;
NODE *nodes[257];
int counts[257]; // array

/* Make node (two purposes): 1. Create a new node with the given data. 2. Create a
new node with the given data and set the parent of the left and right node passed in
equal to the newly created node.
Big-O Notation: O(1) */
static NODE *mknode(int data, NODE *left, NODE *right)
{
    NODE *np=malloc(sizeof(NODE)); // allocate memory for node
    assert(np!=NULL);
    np->parent=NULL;
    np->count=data;
    if (left!=NULL)
        left->parent=np;
    if (right!=NULL)
        right->parent=np;
    return np;
}

/* Node compare: comparison function for two given nodes that you pass to your createQueue
Big-O Notation: O(1) */
static int comparison(NODE *node_1, NODE *node_2)
{
    assert(node_1 !=NULL && node_2 !=NULL);
    if(node_1->count<node_2->count) // if less than
        return -1;
    else if(node_1->count>node_2->count) // if greater than
        return 1;
    else // if the same
        return 0;
}

/* Depth: returns the depth of a given node
Big-O Notation: O(h) */
static int depth(NODE *np)
{
    assert(np!=NULL);
    if(np->parent==NULL)
        return 0;
    return depth(np->parent)+1;
}

/* Big-O Notation: O(n) */
int main(int argc, char *argv[])
{
    FILE *fp=fopen(argv[1],"r"); // opens file for reading 
    if (fp==NULL)
    {
        printf("file does not exist!\n");
        return 0;
    }
    int c;
    while(c!=EOF) // loops until end of file
    {
        c= getc(fp); // get each individual characters from file
        counts[c]++; // count frequency of each character
    }
    fclose(fp);
    PQ *pq = createQueue(comparison);
    int i;
    for(i=0;i<256;i++) // we loop until 256 instead of 257 because we don't include the EOF character
    {
        if(counts[i]>0) // if frequency is greater than 0
        {
            nodes[i]=mknode(counts[i],NULL,NULL); // create binary tree consisting of just a leaf for each character with a nonzero count
            addEntry(pq,nodes[i]); // insert tree into priority queue
        }
    }
    nodes[256]=mknode(0,NULL, NULL); // create tree with a zero count for the end of file marker
    addEntry(pq,nodes[256]); // insert tree into priority queue
    while(numEntries(pq)>1) // while priority queue has more than 1 tree
    {
        NODE *left=removeEntry(pq); // remove the 2 lowest priority trees
        NODE *right=removeEntry(pq);
        NODE *np=mknode(left->count+right->count, left, right); // create a new tree with each of these trees as subtrees
        addEntry(pq,np); // insert new tree into priority queue
    }
    for(i=0;i<257;i++)
    {
        if (nodes[i]!=NULL) // there exists a node
        {
            if(isprint(i)) // if character is printable
                printf("'%c': %d x %d bits = %d bits\n",i,counts[i],depth(nodes[i]),counts[i]*depth(nodes[i]));
            else
                printf("%03o: %d x %d bits = %d bits\n",i,counts[i],depth(nodes[i]),counts[i]*depth(nodes[i]));
        }
    }
    pack(argv[1],argv[2],nodes); // compress file
    return 0;
}
