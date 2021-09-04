/*Gabriel Do
COEN 10
Lab 9
Monday 2:15pm
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int counter;
char word[10][20];
int length[10];

void input()
{
    int i;
    int j;
    printf("Enter up to 10 names\n");   // print message
    while(counter<=10) // loop until we have reached 10 words
    {
        char wordInput[10][20];
        int a =scanf("%s", wordInput[counter]); // scan input
        if(a <=0) // if the input is ^D, we break the loop
        {     
            break;
        }
        if (counter>=10)
        {
            printf("You can only input up to 10 words\n");
            break;
        }
        int j = counter;
        while(j>0 && strcmp(wordInput[counter],word[j-1])<0)
        {
            strcpy(word[j], word[j-1]);
            j--;
        }
        strcpy(word[j], wordInput[counter]);
        counter++;    
    }
    output();
}
void reverse()
{       
    int i;
    int j;
    char temp[10][20];
    for (i=0,j=counter-1;i<j;i++,j--)
    {
        strcpy(temp[i],word[i]);
        strcpy(word[i],word[j]);
        strcpy(word[j],temp[i]);
    }
    output();
}
void convert()
{
    int i;
    char *p=word;
    for(i= 0; i < 10; i++)
    {
        p = &word[i];
        while (*p != '\0' && p !=NULL)
        {
            length[i]++;
            *p = toupper(*p);
            p++;
        }
    }
    output();
}
void info()
{
    int i;
    int j=0;
    int k=0;
    int shortword=length[0];
    int longword=length[0];
    for (i=0; i<counter; i++)
    {
        if (length[i]<shortword)
        {
            shortword=length[i];
            j=i;
        }
        if(length[i]>longword)
        {
            longword=length[i];
            k=i;
        }
    }
    printf("Shortest word: %s\n", word[j]);
    printf("Longest word: %s\n", word[k]);
    int sum=0;
    for (i=0; i<counter; i++)
        sum+=length[i];
    int average = sum/counter;
    printf("Average length of words: %d\n", average);
    int arr[counter];
    for (i=0; i<counter; i++)
    {
        arr[i]=isalpha(word[i][0]);
    }
    printf("Words starting w/o letter: ");
    for (i=0; i<counter;i++)
    {
        if (arr[i]==0)
            printf("%s ", word[i]);
    }
}
void output()
{
    int i;
    for (i=0; i<counter; i++)
        printf("%s ", word[i]);
}
int main()
{
    input();
    printf("\n");
    reverse();
    printf("\n");
    convert();
    printf("\n");
    info();
    return 0;
}
