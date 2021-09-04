/* Gabriel Do
COEN 11
Lab 8
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

void insert(char nameInput[], int groupInput) // insert a node with the name and number of people specified in the corresponding list
{
    NODE *p;
    p = (NODE*)malloc(sizeof (NODE));  //malloc is used to create an unallocated node in memory to populate
    strcpy (p->names, nameInput);
    p->group = groupInput;
    p->next=NULL; 
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
    printf("Name\tGroup Size\n");
    printf("-----------------\n");	
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
                printf ("%s\t%d\n", p->names, p->group);
            }
            if (i==1)
            {
                if (flag2==0)
                {
                    printf("list 2:\n");
                    flag2=1;
                }
                printf ("%s\t%d\n", p->names, p->group);
            }
            if (i==2)
            {
                if (flag3==0)
                {
                    printf("list 3:\n");
                    flag3=1;
                }
                printf ("%s\t%d\n", p->names, p->group);
            }
            if (i==3)
            {
                if (flag4==0)
                {
                    printf("list 4:\n");
                    flag4=1;
                }
                printf ("%s\t%d\n", p->names, p->group);
            }
            p = p->next;
        }
    }
    return;
}

void search_size() // print the entries that have group <= size
{
    int flag=0;
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
                if(flag==0)
                {
                    printf("Name\tGroup Size\n");
                    printf("-----------------\n");
                    flag==1;
                }
                if (i==0)
                {
                    if (flag1==0)
                    {
                        printf("list 1:\n");
                        flag1=1;
                    }
                    printf ("%s\t%d\n", p->names, p->group);
                }
                if (i==1)
                {
                    if (flag2==0)
                    {
                        printf("list 2:\n");
                        flag2=1;
                    }
                    printf ("%s\t%d\n", p->names, p->group);
                }
                if (i==2)
                {
                    if (flag3==0)
                    {
                        printf("list 3:\n");
                        flag3=1;
                    }
                    printf ("%s\t%d\n", p->names, p->group);
                }
                if (i==3)
                {
                    if (flag4==0)
                    {
                        printf("list 4:\n");
                        flag4=1;
                    }
                    printf ("%s\t%d\n", p->names, p->group);
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

void quit(NODE *p) // Free all the nodes before quitting
{
    if(p == NULL)
        return;
    quit(p->next);	
    free(p);
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

void read_file(char *file_name)
{
    FILE *fp;
    char fileNames[20];
    int fileGroup;
    fp = fopen(file_name, "r");
    if (fp==NULL)
    {
        printf("file does not exist\n");
        return;
    }
    fseek(fp, 31, SEEK_SET);
    while(fscanf(fp, "%s %d\n", fileNames, &fileGroup) == 2)
        insert(fileNames, fileGroup);	
    fclose(fp);  
    return;
}

void save_file(char *file_name)
{
    FILE *fp;
    NODE *p;
    int i;
    fp = fopen(file_name, "w");
    if(fp==NULL)
    {
        printf("file does not exist\n");
        return;
    }
    fprintf(fp, "Name\tGroup Size\n");
    fprintf(fp, "---------------\n"); 
    for(i = 0; i < 4; i++)
    {
        p = array[i].head;
        while(p != NULL)
        {
            fprintf(fp, "%s\t%d\n", p->names, p->group);
            p = p->next;
        }
    }
    fclose(fp);
    return;
}

void reverseList(NODE *p)
{
    if(p == NULL)
        return;
    else
    {
        reverseList(p->next);
        printf ("%s\t%d\n", p->names, p->group);     
    }
    return;
}

void reverseWord(char *p)
{
    if(*p=='\0')
        return;
    reverseWord(p+1);
    printf("%c",*p);
    return;
}

void reverseNames(NODE *p)
{
    int i;
    if(p == NULL)
        return;
    reverseWord(p->names);
    printf("\n");
    reverseNames(p->next);
    return;
}

int main(int argc, char*argv[])
{
    int i;
    int input;
    char nameInput[20];
    int groupInput;
    NODE *p;
    if (argc==1)
    {
        printf("The name of the file is missing!\n");
        return 1;
    }
    read_file (argv[1]);
    while(1)
    {
        printf("(1) Insert\n");
        printf("(2) Remove\n");
        printf("(3) List\n");
        printf("(4) Show entries less than or equal to entered size\n");
        printf("(5) Show each list backwards\n");
        printf("(6) Show each name backwards\n");
        printf("(7) Change size\n");
        printf("(0) Quit\n");
        scanf ("%i",&input);
        switch (input)
        {
            case 1:
                printf("What is your name?\n");
                scanf("%s", nameInput);
                int check=check_duplicate(nameInput);
                if (check==1)
                {
                    printf("Name is already in use\n");
                    break;
                }
                printf("How many people in your group?\n");
                scanf("%d", &groupInput);
                insert(nameInput, groupInput);
                printf("%s has been added to the waiting list for %d people\n", nameInput, groupInput); 
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
                if (array[0].head==NULL && array[1].head==NULL && array[2].head==NULL && array[3].head==NULL) //if list is empty
                {
                    printf ("the list is empty\n");
                    break;
                }
                printf("Name\tGroup Size\n");
                printf("-----------------\n");
                for(i = 0; i < 4; i++)
                {
                    p = array[i].head;
                    if (p!=NULL)
                        printf("list %d:\n", i+1);
                    reverseList(p);
                }
                break;
            case 6:
                if (array[0].head==NULL && array[1].head==NULL && array[2].head==NULL && array[3].head==NULL) //if list is empty
                {
                    printf ("the list is empty\n");
                    break;
                }
                printf("Name\n");
                printf("-------\n");
                for(i = 0; i < 4; i++)
                {
                    p = array[i].head;
                    if (p!=NULL)
                        printf("list %d:\n", i+1);
                    reverseNames(p);
                }
                break;
            case 7:
                name_old_size_new_size();
                break;
            case 0:
                save_file(argv[1]);
                for(i = 0; i < 4; i++)
                {
                    p = array[i].head;
                    quit(p);
                }
                printf("Exiting App\n");
                return 0;
            default:
                printf("bad option\n");
                break;
        }
    }
}