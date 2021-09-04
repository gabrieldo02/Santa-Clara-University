/* Gabriel Do
 *  * * COEN 10
 *   * * Lab 6
 *    * * Monday 2:15pm
 *     * */
int main()
{
	int schedule[5]={0,0,0,0,0};
	int x;
	int timeslot=0;
	int counter=0;
	int i;
	while(x!=9)
	{
		printf("(1) schedule an appointment\n");
		printf("(2) cancel an appointment\n");
		printf ("(3) list the schedule\n");
		printf ("(9) quit\n");
		scanf ("%d",&x);
		if (x==1)
	 	{
			if (counter==5)
				printf ("come back tomorrow\n");
			else 
			{
				for (i=0; i<5; i++)
				{
					if (schedule[i]==0)
					{
					schedule[i]=i+1;
					counter++;
					printf("appointment made at time %d pm\n", schedule[i]);
					break;
					}
				}
			}
		
		}
		else if (x==2)
		{
			if (counter==0)
				printf("schedule is empty\n");
			else 
			{
				printf("Which time do you want to cancel? ");
				scanf("%d", &timeslot);
				if(schedule[timeslot-1]==0)
					printf("That time slot is already free\n");
				else
				{
					printf("Slot at %d pm has been canceled\n", timeslot);
					schedule[timeslot-1]=0;
					counter--;
				}
			}
			 
		}
		else if (x==3)
		{
			if (counter==0)
				printf("schedule is empty\n");
			else 
			{
				for (i=0; i<5; i++)
				{
					if (schedule[i]==0)
						printf("%d pm-free\n", i+1);
					else
						printf("%d pm-busy\n", i+1);
				}
			}
		}
		else if (x==9)
			printf("Exiting App");
		else 
			printf("bad option\n");
	}
	return 0;
}

