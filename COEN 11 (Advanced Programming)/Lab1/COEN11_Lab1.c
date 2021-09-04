/* Gabriel Do
COEN 11
Lab 1
Tuesday 2:15pm */

#include <stdio.h>

int division(int divisor, int quotient)
{
    int dividend = divisor*quotient;
    printf("%d / %d = ?\n", dividend, divisor);
    int input = 0;
    scanf("%d", &input);
    if (input==quotient)
        return 1;
    else 
        return 0;
}

int main()
{
    int counter=0;
    int i;
    srand ((int) time (NULL));
    for (i=0; i<10;i++)
    {
        int divisor = rand() % 12+1;
        int quotient = rand() % 13;
        int answer=division(divisor, quotient);
        if (answer==1)
        {
            printf("Right\n");
            counter++;
        }
        else
        {
            printf("Wrong\n");
            printf("Correct quotient: %d\n", quotient);
        }
    }
    printf("Score: %d/10", counter);
}

