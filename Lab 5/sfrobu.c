//Cody Hubbard
//004843389
//CS35l Week 5 HW

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

//Global record for -f option
int f_flag = 0;

char decodeChar (const char c)
{
    if (f_flag == 0)
    {
        return c^42;
    }
    else
    {
        unsigned int temp;
        temp = (unsigned int) c^42;
        if ( (f_flag == 1) && (temp > 64) && (temp < 91))
        {
            temp = toupper(temp);
            char temp_c = (char) temp;
            return temp_c^42;
        }
        return
            c^42;
    }
}

int frobcmp (char const *a1, char const *b1)
{
  for (;; a1++, b1++)
    {
      if (*a1 == ' ' && *b1 == ' ')
        return 0;
        
    else if (*a1 == ' ')
	    return -1;
	else if (decodeChar (*a1) < decodeChar (*b1))
	    return -1;

    else if (*b1 == ' ')
        return 1;
    else if (decodeChar (*a1) > decodeChar (*b1))
        return 1;
    }
}

int cmp (const void *a, const void *b)
{
  const char *a1 = *(const char **) a;
  const char *b1 = *(const char **) b;
  return frobcmp (a1, b1);
}

int main (int argc, char **argv)
{
    int return_val = 0;

    if((return_val = getopt(argc, argv, "f")) != -1) 
    {
        if (return_val == 'f') 
            f_flag = 1;
    }
    
  char *f_arr;

  char *c_arr = (char*)malloc(sizeof(char));
  char **word_list = (char**)malloc(sizeof(char*));

  int wsize = 0;
  int wcnt = 0;

  char ch;
  char nch;
  
  struct stat m_File;
  fstat (0, &m_File);

  if (S_ISREG (m_File.st_mode))
    {
      f_arr = (char*)malloc(sizeof(char)*(m_File.st_size+2));
      read(0, f_arr, m_File.st_size);
      
      ch = f_arr[0];
      nch = f_arr[1];
      
      for (int i=2; i < m_File.st_size+2; i++)
      {
          c_arr[wsize] = ch;
          char *temparr = realloc(c_arr, sizeof(char)*(wsize+2));
          if (temparr == NULL)
          {
              fprintf(stderr, "MEMORY ERROR");
              exit (1);
          }
          
          c_arr = temparr;
          
          if (ch == ' ')
          {
              word_list[wcnt] = c_arr;
              char** temp_list = realloc(word_list, sizeof(char*)*(wcnt+2));
              
              if (temp_list == NULL)
              {
                  fprintf (stderr, "MEMORY ERROR");
                  exit (1);
              }
              
              word_list = temp_list;
              wcnt++;
              
              c_arr = NULL;
              c_arr = (char*)malloc(sizeof(char));
              
              if (c_arr == NULL)
              {
                  fprintf (stderr, "MEMORY ERROR");
                  exit (1);
              }
              wsize = -1;
          }
          
        if (ch == ' ' && (i >= m_File.st_size))
          break;
        
        else if (ch != ' ' && (i >= m_File.st_size))
        {
            ch = ' ';
            wsize++;
            continue;
        }
        
        ch = nch;
        nch = f_arr[i];
        wsize++;
      }
    }
    
    c_arr = NULL;
    c_arr = (char*)malloc(sizeof(char));
    
    int file_state1 = read(0, &ch, 1);
    int file_state2 = read(0, &nch, 1);
    
    wsize = 0;
    
    while(file_state1 > 0)
    {
        c_arr[wsize] = ch;
        char *temparr = realloc(c_arr,sizeof(char)*(wsize+2));
        
        if (temparr == NULL)
        {
            fprintf (stderr, "MEMORY ERROR");
            exit (1);
        }
        c_arr = temparr;
        
        if (ch == ' ')
          {
              word_list[wcnt] = c_arr;
			  
              char** temp_list = realloc(word_list, sizeof(char*)*(wcnt+2));
              
              if (temp_list == NULL)
              {
                  fprintf (stderr, "MEMORY ERROR");
                  exit (1);
              }
              
              word_list = temp_list;
              wcnt++;
              
              c_arr = NULL;
              c_arr = (char*)malloc(sizeof(char));
              
              if (c_arr == NULL)
              {
                  fprintf(stderr, "MEMORY ERROR");
                  exit (1);
              }
              
              wsize = -1;
          }
        
        if (ch == ' ' && file_state2 < 1)
          break;
          
        else if (ch != ' ' && file_state2 < 1)
        {
            ch = ' ';
            wsize++;
            continue;
        }
        
        ch = nch;
        file_state2 = read(0, &nch, 1);
        wsize+=1;
    }
    
    
    qsort(word_list, wcnt, sizeof(char*), cmp);
    
    /*for(int i = 0; i < wcnt; i++)
    {
        int length = 0;
        for(int j = 0; ;j++)
        {
            length++;
            if (word_list[i][j] == ' ')
            break;
        }
        write(1,word_list[i],length);
    }*/
    
    for(int i = 0; i < wcnt; i++)
    {
        int j = -1;
        while (word_list[i][j] != ' ')
        {
         j++;    
         write(1,&word_list[i][j],1);
        }
    }
  
  for(int k = 0; k < wcnt; k++)
    {
        free(word_list[k]);
    }
    free(word_list);
    free(f_arr);
    exit(0);
}