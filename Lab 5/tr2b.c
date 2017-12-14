//Cody Hubbard - 004843389
//Lab week 5

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main ( int argc, char *argv[])
{
char* from;
from = argv[1];
char* to;
to = argv[2];

int fromsize = strlen(from);
int tosize = strlen(to);

//int fromsize = sizeof argv[1] / sizeof argv[1][0];
//int tosize = sizeof argv[2] / sizeof argv[2][0];

if (fromsize != tosize)
    exit(0);

for (int i = 0; i < fromsize-1; i++)
{
    for(int j = i+1; j < fromsize-1; j++)
    {
        if (from[i]==from[j])
            exit(0);
        if (to[i]==to[j])
            exit(0);
    }
}

int ch = getchar();

while (ch != EOF)
{
    int k;
    int check = 0;
    
    for (k=0; k<tosize; k++)
    {
        if (from[k] == ch)
        {
            putchar(to[k]);
            check = 1;
            break;
        }
        
    }
    
    if (check == 0)
        putchar(ch);
		
	ch = getchar();
}
}
