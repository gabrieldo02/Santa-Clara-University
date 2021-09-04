/* Gabriel Do
COEN 11
Lab 3
Tuesday 2:15pm */

#include <stdio.h>
#include <string.h>

typedef struct info
{
    char names[20];
    int group;
} INFO;
INFO position[10];
int counter=0;

void insert()
{
    int i;
    char nameInput[20];
    int groupInput;
    INFO *p=position;
    if (counter<10)
    {
        p+=counter;
        printf("What is your name?\n");
        scanf("%s", &nameInput);
        i=check_duplicate(nameInput);
        if (i==1)
        {
            printf("Name is already in use\n");
            return;
        }
        printf("How many people in your group?\n");
        scanf("%d", &groupInput);
        strcpy(p->names,nameInput);
        p->group = groupInput; 
        printf("%s has been added to the waiting list for %d people\n", p->names, p->group); 
        counter++;
    }
    else 
        printf("waiting list full\n");
}

void cancel()
{
    int i;
    int j;
    int size;
    int wasRemoved = 0;
    INFO *p=position;
    if (counter==0)
        printf("list is empty\n");
    else
    {
        printf("What size?\n");
        scanf("%d", &size);
    for(i=0;i<counter;) 
        {
            if(p->group <=size)
            {
                wasRemoved = 1;
                size-=p->group;
                printf("%s's spot (for %d people) on the waiting list will be removed\n", p->names, p->group);
                INFO *q=position;
                for(j=i; j< counter-1; j++)
                {
                    strcpy(q->names, (q+1)->names);
                    q->group=(q+1)->group;
                    q++;
                }
                counter--;
            } 
            else 
            {
                i++; 
                p++;
            }
        }
        if (wasRemoved==0)
            printf("No names on the waiting list fits that size\n");
    }
}

void list()
{
    INFO *p=position; 
    int i;
    if (counter==0)
        printf("list is empty\n");
    else 
    {
        for (i=0; i<counter; i++,p++)
            printf("%d. %s - %d people\n", i+1, p->names, p->group);
    }
}

void search_size()
{
    INFO *p = position;
    int i;
    int size;
    int wasFound=0;
    printf("What size?\n");
    scanf("%d", &size);
    for (i=0; i<counter; i++,p++)
    {
        if(p->group <=size)
            {
                wasFound=1;
                printf("%d. %s - %d people\n", i+1, p->names, p->group);
            }
    }
    if (wasFound==0)
        printf("No entries less than or equal to entered size\n");
}

int check_duplicate(char *name)
{
	INFO *p = position;
	int i;
	for(i=0;i<counter;i++)
	{
		if(strcmp(name,p->names)==0)   
			return 1;
        else
            p++;        
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