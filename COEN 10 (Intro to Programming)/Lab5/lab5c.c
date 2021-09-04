/* Gabriel Do
 * * COEN 10
 * * Lab 4
 * * Monday 2:15pm
 * */
#include <stdio.h>

int main ()
{
	int counter = 0;
	for (int i = 0; i < 10; i++)
	{
		srand ((int) time (NULL));
		int randomNum1 = rand () % 13;
		int randomNum2 = rand () % 13;
		printf("%d x %d = ", randomNum1, randomNum2);
		int input = 0;
		scanf("%d", &input);
		if(input == randomNum1*randomNum2) 
		{
			printf("Yay\n");
			counter++;
		}
	else printf("Not Yay\n");
	}
	printf("correct: %d/10", counter);
return 0;
}
