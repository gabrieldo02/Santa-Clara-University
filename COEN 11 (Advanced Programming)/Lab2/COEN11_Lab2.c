/* Gabriel Do
COEN 11
Lab 2
Tuesday 2:15pm */

#include <stdio.h>
#include <string.h>

int counter=0;
char names[10][20]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
int group[10]={0,0,0,0,0,0,0,0,0,0};

void insert()
{
    int i;
    char nameInput[20];
    int groupInput;
    if (counter==10)
        printf("waiting list full\n");
    else 
    {
        printf("What is your name?\n");
        scanf("%s", &nameInput);
        printf("How many people in your group?\n");
        scanf("%d", &groupInput);
        for(i=0;i<10;i++)
        {
            if(names[i][0]=='\0')
            {
                strcpy(names[i],nameInput);
                group[i]=groupInput;
                printf("%s has been added to the waiting list for %d people\n", names[i], group[i]);
                counter++;
                break;
            }
        }
    }
}

void cancel()
{
    int i;
    int size;
    int wasRemoved = 0;
    if (counter==0)
        printf("list is empty\n");
    else
    {
        printf("What size?\n");
        scanf("%d", &size);
    for(i=0;i<10;) 
        {
            if(group[i]<=size && names[i][0] != '\0')
            {
                wasRemoved = 1;
                size-=group[i];
                printf("%s's spot (for %d people) on the waiting list will be removed\n", names[i], group[i]);
                int j;
                for(j=i; j< counter-1; j++)
                {
                    strcpy(names[j], names[j+1]);
                    group[j]=group[j+1];
                }
                names[counter-1][0] = '\0';
                counter--;
            } 
            else 
                i++; 
        }
        if (wasRemoved==0)
            printf("No names on the waiting list fits that size\n");
    }
}
void list()
{
    int i;
    if (counter==0)
        printf("list is empty\n");
    else 
    {
        for (i=0; i<10; i++)
        {
            if (names[i][0]=='\0')
                printf("%d. empty\n",i+1);
            else 
                printf("%d. %s - %d people\n", i+1, names[i], group[i]);
        }	
    }
}
int main()
{
    int i=-1;
    while(i!=0)
    {
        printf("(1) Insert\n");
        printf("(2) Remove\n");
        printf("(3) List\n");
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
            case 0:
                printf("Exiting App\n");
                break;
            default:
                printf("bad option\n");
                break;
        }
    }
    return 0;
}