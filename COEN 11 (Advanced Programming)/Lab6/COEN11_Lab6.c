/* Gabriel Do
COEN 11
Lab 6
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

struct list
{
    NODE *head;
    NODE *tail;
};
struct list array[4]={{NULL,NULL}, {NULL,NULL}, {NULL,NULL}, {NULL, NULL}};	

void insert() // insert a node with the name and number of people specified in the corresponding list
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
    if (groupInput==1 || groupInput==2)
    {
        if(array[0].head==NULL)
        {
            array[0].tail=array[0].head=p;
            array[0].tail->next=NULL;
        }
        else
        {
            array[0].tail->next=p;
            array[0].tail=p;
        }
    }
    if (groupInput==3 || groupInput==4)
    {
        if (array[1].head==NULL)
        {
            array[1].tail=array[1].head=p;
            array[1].tail->next=NULL;
        }
        else
        {
            array[1].tail->next=p;
            array[1].tail=p;
        }
    }
    if (groupInput==5 || groupInput==6)
    {
        if (array[2].head==NULL)
        {
            array[2].tail=array[2].head=p;
            array[2].tail->next=NULL;
        }
        else
        {
            array[2].tail->next=p;
            array[2].tail=p;
        }
    }
    if (groupInput>6)
    {
        if (array[3].head==NULL)
        {
            array[3].tail=array[3].head=p;
            array[3].tail->next=NULL;
        }
        else
        {
            array[3].tail->next=p;
            array[3].tail=p;
        }
    }
    return; 
}

void cancel() // show and delete the oldest nodes that fit the opening, smallest first
{
    int i;
    int wasRemoved = 0;
    int size;
    NODE *p;
    NODE *q;
    NODE *temp;
    if (array[0].head==NULL && array[1].head==NULL && array[2].head==NULL && array[3].head==NULL) //if list is empty
    {
        printf ("the list is empty\n");
        return;
    } 
    printf("What size?\n"); 
    scanf("%d", &size);
    for (i=0;i<4;i++)
    {
        p = q = array[i].head;
        while(p != NULL && size>0)
        {
            if(p->group <=size) // cases	
            {
                wasRemoved = 1;
                size-=p->group; 
                if(p == array[i].head)	//if delete first node
                {
                    array[i].head = p->next;
                    printf("%s's spot (for %d people) on the waiting list will be removed\n", p->names, p->group);
                }
                else if(p == array[i].tail)	//if delete last node
                {
                    array[i].tail = q;
                    q->next = NULL;
                    printf("%s's spot (for %d people) on the waiting list will be removed\n", p->names, p->group);
                }
                else if (p == array[i].head && p == array[i].tail) //if delete only node
                {
                    array[i].tail = array[i].head = NULL;
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
    }
    if (wasRemoved==0) //if delete non-existing node
        printf("No names on the waiting list fits that size\n");
    return;
}

void list() // print the list for each range: name and number, from oldest to newest
{
    int flag1=0;
    int flag2=0;
    int flag3=0;
    int flag4=0;
    int i;
    NODE *p;
    if (array[0].head==NULL && array[1].head==NULL && array[2].head==NULL && array[3].head==NULL) //if list is empty
    {
        printf ("the list is empty\n");
        return;
    } 
    for (i=0;i<4;i++)
    {
        p=array[i].head;
        while (p != NULL)
        {
            if (i==0)
            {
                if (flag1==0)
                {
                    printf("list 1:\n");
                    flag1=1;
                }
                printf ("%s, %d people\n", p->names, p->group);
            }
            if (i==1)
            {
                if (flag2==0)
                {
                    printf("list 2:\n");
                    flag2=1;
                }
                printf ("%s, %d people\n", p->names, p->group);
            }
            if (i==2)
            {
                if (flag3==0)
                {
                    printf("list 3:\n");
                    flag3=1;
                }
                printf ("%s, %d people\n", p->names, p->group);
            }
            if (i==3)
            {
                if (flag4==0)
                {
                    printf("list 4:\n");
                    flag4=1;
                }
                printf ("%s, %d people\n", p->names, p->group);
            }
            p = p->next;
        }
    }
    return;
}

void search_size() // print the entries that have group <= size
{
    int flag1=0;
    int flag2=0;
    int flag3=0;
    int flag4=0;
    int i;
    int size;
    NODE *p;
    int wasFound=0;
    printf("What size?\n");
    scanf("%d", &size);
    for (i=0;i<4;i++)
    {
        p=array[i].head;
        while (p != NULL)
        {
            if(p->group <=size)
            {
                wasFound=1;
                if (i==0)
                {
                    if (flag1==0)
                    {
                        printf("list 1:\n");
                        flag1=1;
                    }
                    printf ("%s, %d people\n", p->names, p->group);
                }
                if (i==1)
                {
                    if (flag2==0)
                    {
                        printf("list 2:\n");
                        flag2=1;
                    }
                    printf ("%s, %d people\n", p->names, p->group);
                }
                if (i==2)
                {
                    if (flag3==0)
                    {
                        printf("list 3:\n");
                        flag3=1;
                    }
                    printf ("%s, %d people\n", p->names, p->group);
                }
                if (i==3)
                {
                    if (flag4==0)
                    {
                        printf("list 4:\n");
                        flag4=1;
                    }
                    printf ("%s, %d people\n", p->names, p->group);
                }
            }
            p = p->next;
        }
    }
    if (wasFound==0)
        printf("No entries less than or equal to entered size\n");
    return;
}

int check_duplicate(char *name) // checks for repeat names
{
    int i;
    NODE *p;
    for (i=0;i<4;i++)
    {
        p=array[i].head;
        while (p != NULL)
        {
            if(strcmp(name, p->names) == 0)
                return 1;
            p = p->next;
        }
    }
    return 0;
}

void quit() // Free all the nodes before quitting
{
    int i;
    NODE *p;
    NODE *q;
    for(i = 0; i < 4; i++)
    {
        p = q = array[i].head;
        while (p != NULL)
        {
            q=p;
            p=p->next;
            free(q);
        }
    }
    printf("Exiting App\n");
    return;
}

void name_old_size_new_size()
{
    int i;
    char nameInput[20];
    int groupInput;
    NODE *p;
    NODE *q;
    NODE *temp;
    int flag=0;
    printf("What name?\n");
    scanf("%s", nameInput);
    for (i=0;i<4;i++)
    {
        p=q=array[i].head;
        while (p != NULL)
        {
            if(strcmp(p->names, nameInput) == 0)
            {
                flag=1;
                if(p == array[i].head)	//if delete first node
                    array[i].head = p->next;
                else if(p == array[i].tail)	//if delete last node
                {
                    array[i].tail = q;
                    q->next = NULL;
                }
                else if (p == array[i].head && p == array[i].tail) //if delete only node
                    array[i].tail = array[i].head = NULL;
                else	//if delete one of the middle nodes
                    q->next = p->next;
                temp = p;
                p = p->next;
            }
            else
            {
                q = p;
                p = p->next;
            }
        }
    }
    if (flag==0)
        printf("Name not found\n");
    else
    {
        strcpy (temp->names, nameInput);
        printf("What is new size?\n");
        scanf("%d", &groupInput);
        temp->group = groupInput; 
        printf("%s's group has changed to %d people\n", temp->names,temp->group);
        if (groupInput==1 || groupInput==2)
        {
            if(array[0].head==NULL)
            {
                array[0].tail=array[0].head=temp;
                array[0].tail->next=NULL;
            }
            else
            {
                array[0].tail->next=temp;
                array[0].tail=temp;
            }
        }
        if (groupInput==3 || groupInput==4)
        {
            if (array[1].head==NULL)
            {
                array[1].tail=array[1].head=temp;
                array[1].tail->next=NULL;
            }
            else
            {
                array[1].tail->next=temp;
                array[1].tail=temp;
            }
        }
        if (groupInput==5 || groupInput==6)
        {
            if (array[2].head==NULL)
            {
                array[2].tail=array[2].head=temp;
                array[2].tail->next=NULL;
            }
            else
            {
                array[2].tail->next=temp;
                array[2].tail=temp;
            }
        }
        if (groupInput>6)
        {
            if (array[3].head==NULL)
            {
                array[3].tail=array[3].head=temp;
                array[3].tail->next=NULL;
            }
            else
            {
                array[3].tail->next=temp;
                array[3].tail=temp;
            }
        }
    }
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
        printf("(5) Change size\n");
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
            case 5:
                name_old_size_new_size();
                break;
            case 0:
                quit();
                return 0;
            default:
                printf("bad option\n");
                break;
        }
    }
}