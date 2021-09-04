/*Gabriel Do
COEN 10
Lab 8
Monday 2:15pm
*/
#include <stdio.h>
#include <string.h>

char names[5][20]={'\0','\0','\0','\0','\0'};
char phone[5][20]={'\0','\0','\0','\0','\0'};
int pets[5]={0,0,0,0,0};
int timeslot=0;
int counter=0;
int i;
char nameInput[20];
char phoneNum[20];
int petsNum;
void requestAppointment ()
{
    if (counter==5)
        printf ("come back tomorrow\n");
    else 
    {
        int nameUsed=1;
        while(nameUsed==1) 
        {
            nameUsed=0;
            printf ("What is your name?\n");
            scanf ("%s",&nameInput);
            for (i=0; i<5; i++) 
            {
                if (strcmp(names[i], nameInput)==0)
                {
                    printf("That name is already in use\n");
                    nameUsed=1; 
                    break;
                }
            }
        }
        for (i=0; i<5; i++) 
        {
            if (names[i][0]=='\0')
            {
                strcpy (names[i], nameInput);
                printf("appointment made at time %d pm for %s\n", i+1, names[i]);
                break;
            }
        }
        printf ("How many pets?\n");
        scanf("%d", &petsNum);
        pets[i]=petsNum;
        while(petsNum > 4 || petsNum <1) 
        {
            printf("You can only have an appointment for 1 to 4 pets\n");
            printf ("How many pets?\n");
            scanf("%d", &petsNum);
            pets[i]=petsNum;
        }
        printf ("What is your phone number?\n");
        scanf("%s", &phoneNum);
        strcpy (phone[i], phoneNum);
        printf("%d pets and %s phone number have been added\n", pets[i],phone[i]);
        counter++;
    }
}
void cancelAppointment ()
{
	if (counter==0)
		printf("schedule is empty\n");
	else 
	{
		printf("Whose name do you want to cancel?\n");
		scanf ("%s",&nameInput);
		for (i=0;i<5;i++)
		{
			if (strcmp(names[i], nameInput)==0)
			{
				printf("%s's appointment will be cancelled\n", nameInput);
				int j;
				for(j=i; j< counter-1; j++)
				{
					strcpy(names[j], names[j+1]);
					strcpy(phone[j], phone[j+1]);
					pets[j]=pets[j+1];
					printf("%s's (phone number: %s) appointment has changed to %d pm\n",names[j],phone[j],j+1);
				}
				names[counter-1][0] = '\0';
				counter--;
				break;
			}
        }
		if (i==5)
			printf("That person does not have an appointment\n");		
	}
}
void listAppointments()
{
    if (counter==0)
        printf("schedule is empty\n");
    else 
    {
        for (i=0; i<5; i++)
        {
            if (names[i][0]=='\0')
                printf("%d pm-free\n", i+1);
            else
                printf("%d pm-%s,%s phone number,%d pets\n", i+1, names[i],phone[i],pets[i]);
        }
    }
}
void showNamesStartingWithLetter()
{
    if (counter==0)
        printf("schedule is empty\n");
    else 	
    {	
        printf("What letter do you want?\n");
        char s;
        scanf ("%s",&s);	
        for (i=0; i<5; i++)
            if (names[i][0]==s)
                printf("%s for %d pm\n", names[i], i+1);
    }
}
void showNamesStartingWithNumberOfPets()
{
    if (counter==0)
        printf("schedule is empty\n");
    else 
    {
        printf("How many pets?\n");
        int d;
        scanf ("%d",&d);
        for (i=0; i<5; i++)
            if (pets[i]==d)
                printf("%s for %d pm\n", names[i], i+1);
    }
}
int main()
{
	while(i!=9)
	{
		printf("(1) Request an appointment\n");
		printf("(2) Cancel an appointment\n");
		printf("(3) List the schedule\n");
		printf("(4) Show names starting with a letter\n");
        	printf("(5) Show names starting with a certain number of pets\n");
		printf ("(9) quit\n");
		scanf ("%i",&i);
		switch(i)
		{
			case 1:
				requestAppointment();
				break;
			case 2:
				cancelAppointment();
				break;
			case 3:
				listAppointments();
				break;
			case 4:
				showNamesStartingWithLetter();
				break;
			case 5:
				showNamesStartingWithNumberOfPets();
				break;
			case 9:
				printf("Exiting App\n");
				break;
			default:
				printf("bad option\n");
				break;
        	}
	}
	return 0;
}
