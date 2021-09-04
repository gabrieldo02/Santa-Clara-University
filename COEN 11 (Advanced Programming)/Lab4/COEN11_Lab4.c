/* Gabriel Do
COEN 11
Lab 4
Tuesday 2:15pm */

#include <stdio.h>
#include <string.h>

typedef union extraInfo
{
    char phone[20]; // phone number of adult
    int minAge; // age of youngest person
    float average; // average age of group
} EXTRAINFO;

typedef struct info
{
    char names[20];
    int group; // size of group
    int maxAge; // flag that tells what is inside extrainfo
    EXTRAINFO extra;
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
        printf("How old are you?\n");
        scanf("%d", &p->maxAge);
        if (p->maxAge<18)
        {
            printf("What is your parent's or guardian's phone number?\n");
            scanf("%s", p->extra.phone);
            printf("%s (is a minor(age<18); parent/guardian phone number: %s) has been added to the waiting list for %d people\n", p->names, p->extra.phone, p->group); 
        }
        else if (p->maxAge>65)
        {
            printf("What is the age of the youngest person in your group?\n");
            scanf("%d", &p->extra.minAge);
            printf("%s (is a senior(age>65); age of youngest in group: %d) has been added to the waiting list for %d people\n", p->names, p->extra.minAge, p->group);
        }
        else
        {
            printf("What is the average age of your group?\n");
            scanf("%f", &p->extra.average);
            printf("%s (is neither minor/senior; average age of group: %f) has been added to the waiting list for %d people\n", p->names, p->extra.average, p->group);
        } //depending on what value was stored into the maxAge variable, the function will ask different questions and save the values into the union
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
                    q->maxAge=(q+1)->maxAge;
                    q->extra=(q+1)->extra;
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
        {
            printf("%d. %s - %d people\n", i+1, p->names, p->group);
            if (p->maxAge<18)
                printf("%d years old(is a minor); parent/guardian phone number: %s\n",p->maxAge,p->extra.phone);
            else if (p->maxAge>65)
                printf("%d years old(is a senior); age of youngest person in group: %d\n",p->maxAge,p->extra.minAge);
            else
                printf("%d years old(neither minor/senior); average age of group: %f\n",p->maxAge,p->extra.average);
        } // depending on the maxAge variable, the function will print out different things
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