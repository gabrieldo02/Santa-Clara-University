/* Gabriel Do
 *  * COEN 10
 *   * Lab 7
 *    * Monday 2:15pm
 *     */
int main()
{
	char names[5][20] = {'\0','\0','\0','\0','\0'};
	int timeslot=0;
	int counter=0;
	int i;
	char nameInput[20];
	while(i!=9)
	{
		printf("(1) schedule an appointment\n");
		printf("(2) cancel an appointment\n");
		printf ("(3) list the schedule\n");
		printf ("(4) show names\n");
		printf ("(9) quit\n");
		scanf ("%i",&i);
		switch(i)
		{
			case 1:
				if (counter==5)
					printf ("come back tomorrow\n");
				else 
				{
					scanf ("%s",&nameInput);
					for (i=0; i<5; i++)
					{
						if (names[i][0]=='\0')
						{
							strcpy (names[i], nameInput);
							counter++;
							printf("appointment made at time %d pm for %s\n", i+1, names[i]);
							break;
						}
					}
				}
			break;
			case 2:
				if (counter==0)
					printf("schedule is empty\n");
				else 
				{
					printf("Whose name do you want to cancel? ");
					scanf ("%s",&nameInput);
					for (i=0;i<5;i++)
					{
						if (strcmp(names[i], nameInput)==0)
						{
							printf("%s's appointment will be cancelled", nameInput);
							int j;
							for(j=i; j< counter-1; j++)
							{
								strcpy(names[j], names[j+1]);
							}
							names[counter-1][0] = '\0';
							counter--;
							break;
						}
					}
					if (i==5)
						printf("That person does not have an appointment\n");		
				}
			break;
			case 3:
				if (counter==0)
					printf("schedule is empty\n");
				else 
				{
					for (i=0; i<5; i++)
					{
						if (names[i][0]=='\0')
							printf("%d pm-free\n", i+1);
						else
							printf("%d pm-%s\n", i+1, names[i]);
					}
				}
			break;
			case 4:
				if (counter==0)
					printf("schedule is empty\n");
				else 	
				{	
					printf("What letter do you want?\n");
					char s;
					scanf ("%s",&s);	
					for (i=0; i<5; i++)
						if (names[i][0]==s)
							printf("%s\n", names[i]);
				}
			break;
			case 9:
				printf("Exiting App");
			break;
			default:
				printf("bad option\n");
			break;
		}	
	}
	return 0;
}

