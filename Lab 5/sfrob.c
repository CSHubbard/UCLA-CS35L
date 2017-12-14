//Cody Hubbard
//004843389
//CS35l Week 4 HW
#include<stdio.h>
#include<stdlib.h>
#include <errno.h>

char decodeChar(const char c)
{
	return c^42;
}

int frobcmp(char const *a1, char const *b1)
{
	for(;; a1++, b1++)
	{
		if(*a1 == ' ' && *b1 == ' ') { return 0; }
		
		else if (*a1 == ' ')
			return -1;
		else if (decodeChar(*a1) < decodeChar(*b1))
		    return -1;
		
		else if (*b1 == ' ')
			return 1;
		else if (decodeChar(*a1) > decodeChar(*b1))
			return 1;
	}
}

int cmp( const void* a, const void* b) 
{
	const char* a1 = *(const char **)a;
	const char* b1 = *(const char **)b;
	return frobcmp(a1, b1);
}

int main(void)
{

  char* c_arr = (char*)malloc(sizeof(char));
  char** word_list = (char**)malloc(sizeof(char*));
  
  if(c_arr == NULL || word_list == NULL)
	{
		fprintf(stderr, "MEMORY ERROR");
		exit(1);
	}
  
  int wsize = 0;
  int wcnt = 0;
  
  char ch = getchar(); 
  char nch = getchar();
  
  while(ch != EOF)
  {
  	c_arr[wsize] = ch;
	char* temparr = realloc(c_arr, sizeof(char)*(wsize+2));
  	if(temparr == NULL)
	{
		fprintf(stderr, "MEMORY ERROR");
		exit(1);
	}
	c_arr = temparr;



	if(ch == ' ')
	{
		word_list[wcnt] = c_arr;
		
		char** temp_list = realloc(word_list, sizeof(char*)*(wcnt+2));
		
		if (temp_list == NULL)
		{
			fprintf(stderr, "MEMORY ERROR");
			exit(1);
		}
		
		word_list = temp_list;
		wcnt++;
		
		c_arr=NULL;
		c_arr = (char*)malloc(sizeof(char));
		
		if(c_arr == NULL)
		{
			fprintf(stderr, "MEMORY ERROR");
			exit(1);
		}
		
		
		wsize = -1;
	}
	
	if (ch == ' ' && nch == EOF)
		break;
	
	else if (ch != ' ' && nch == EOF)
	{
		ch = ' ';
		wsize++;
		continue;
	}
	
	ch = nch;
	nch = getchar();
	wsize++;
  }
  
  qsort(word_list, wcnt, sizeof(char*), cmp);

  for(int i = 0; i < wcnt; i++)
  {
  	for(int j = 0; ;j++)
	{
	    putchar(word_list[i][j]);
		if (word_list[i][j] == ' ')
			break;
	}
  }
  
  for(int k = 0; k < wcnt; k++)
	  free(word_list[k]);
  free(word_list);
  exit(0);
}