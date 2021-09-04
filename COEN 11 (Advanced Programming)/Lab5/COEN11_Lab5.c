/* Gabriel Do
COEN 11
Lab 5
Tuesday 2:15pm */

#include <stdio.h>
#include <string.h>
#define NODE struct node

struct node
{
    char names[20];
    int group; // size of group
    NODE *next;
};
NODE *head=(NODE*)NULL;
NODE *tail=(NODE*)NULL;

void insert()
{
    char nameInput[20];
    int groupInput;
    NODE *p;
    printf("What is your name?\n");
    scanf("%s", nameInput);
    int i=check_duplicate(nameInput);
    if (i==1)
    {
        printf("Name is already in use\n");
        return;
    }
    p = (NODE*)malloc(sizeof (NODE));  //malloc is used to create an unallocated node in memory to populate
    strcpy (p->names, nameInput);
    printf("How many people in your group?\n");
    scanf("%d", &groupInput);
    p->group = groupInput; 
    printf("%s has been added to the waiting list for %d people\n", p->names, p->group); 
    p->next = NULL;
    if(head == NULL) //if list is empty
    {
        tail = head = p;
        return;
    }
    else //tail pointer pointing to the last node; list is not empty
    {   
        tail->next = p;
        tail = p;
        return;
    }
}

void cancel()
{
    int wasRemoved = 0;
    int size;
    NODE *p;
    NODE *q;
    NODE *temp;
    if (head == (NODE *)NULL) //if list is empty
    {
        printf ("the list is empty\n");
        return;
    } 
    p = q = head;
    printf("What size?\n"); 
    scanf("%d", &size);
    while(p != (NODE *)NULL && size>0)
    {
        if(p->group <=size) // cases	
        {
            wasRemoved = 1;
            size-=p->group; 
            if(p == head)	//if delete first node
            {
                head = p->next;
                printf("%s's spot (for %d people) on the waiting list will be removed\n", p->names, p->group);
            }
            else if(p == tail)	//if delete last node
            {
                tail = q;
                q->next = NULL;
                printf("%s's spot (for %d people) on the waiting list will be removed\n", p->names, p->group);
            }
            else if (p == head && p == tail) //if delete only node
            {
                tail = head = NULL;
                printf("%s's spot (for %d people) on the waiting list will be removed\n", p->names, p->group);
            }
            else	//if delete one of the middle nodes
            {
                q->next = p->next;
                printf("%s's spot (for %d people) on the waiting list will be removed\n", p->names, p->group);
            }
            temp = p;
            p = p->next;
            free(temp);
        }
        else
        {
            q = p;
            p = p->next;
        }
    }
    if (wasRemoved==0) //if delete non-existing node
        printf("No names on the waiting list fits that size\n");
    return;
}

void list()
{
    NODE *p;
    if (head == (NODE *)NULL)
    {
        printf ("the list is empty\n");
        return;
    }
    p=head;
    while (p != (NODE *)NULL)
    {
        printf ("%s, %d people\n", p->names, p->group);
        p = p->next;
    }
    return;
}

void search_size()
{
    int size;
    NODE *p;
    p = head;
    int wasFound=0;
    printf("What size?\n");
    scanf("%d", &size);
    while (p != (NODE *)NULL)
    {
        if(p->group <=size)
        {
            wasFound=1;
            printf("%s, %d people\n", p->names, p->group);
        }
        p = p->next;
    }
    if (wasFound==0)
        printf("No entries less than or equal to entered size\n");
    return;
}

int check_duplicate(char *name)
{
    NODE *p;
    p=head;
    while (p != (NODE *)NULL)
    {
        if(strcmp(name, p->names) == 0)
            return 1;
        p = p->next;
    }
    return 0;
}

int main()
{
    int i;
    while(1)
    {
        printf("(1) Insert\n");
        printf("(2) Remove\n");
        printf("(3) List\n");
        printf("(4) Show entries less than or equal to entered size\n");
        printf("(0) Quit\n");
        scanf ("%i",&i);
        switch (i)
        {
            case 1:
                insert();
                break;
            case 2:
                cancel();
                break;
            case 3:
                list();
                break;
            case 4:
                search_size();
                break;
            case 0:
                printf("Exiting App\n");
                return 0;
            default:
                printf("bad option\n");
                break;
        }
    }
}