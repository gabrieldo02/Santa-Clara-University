/* Gabriel Do
COEN 12
Lab 1
Wednesday 2:15pm */

#include <stdio.h>
#define MAX_WORD_LENGTH 30

int main(int argc, char *argv[]) // argc is the number of arguments, argv is the file name
{
    int counter=0; // declare counter
    char word[MAX_WORD_LENGTH];
    if (argc==1) // check if file name is inputted
    {
        printf("The name of the file is missing!\n");
        return 1;
    }
    FILE *fp;
    fp=fopen(argv[1], "r"); // opening file
    if (fp==NULL) // check if file is valid
    {
        printf("file does not exist\n");
        return;
    }
    while(fscanf(fp,"%s",word) == 1)
        counter++;
    fclose(fp);
    printf("%d total words\n", counter);
    return;
}