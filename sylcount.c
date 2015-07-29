#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include "sylcount.h"


#define MAX(a,b) (a<b?b:a)


static inline bool isvowel(const char c)
{
  if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' ||
      c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y')
    return true;
  else
    return false;
}

static inline int count_syllables(char *str, const int len)
{
  int nsyls;
  str[len+1] = '\0'; // SHOULDN'T HAVE TO DO THIS, FUCKING GPERF GARBAGE
  sylcount_t *s = in_word_set(str, len+1);
  
  if (NULL == s)
  {
    nsyls = 0;
    for (int i=0; i<=len; i++)
    {
      if (isvowel(str[i]) && !isvowel(str[i-1]))
        nsyls++;
    }
  }
  else
    nsyls = s->syls;
  
  return MAX(1, nsyls);
}



static inline int findword(const char *str, const int len, int *start, int *end)
{
  int i;
  
  // find word start
  for (i=*start; i<len; i++)
  {
    if (isalpha(str[i]))
    {
      *start = i;
      break;
    }
  }
  
  if (*start == len)
    return -1;
  
  // find word end
  for (i=*start; i<len; i++)
  {
    if (!isalpha(str[i]))
    {
      *end = i-1;
      break;
    }
  }
  
  return *end - *start;
}



static inline void print_counts(char *buf, int start, int end, int nsyls)
{
  for (int j=start; j<=end; j++)
    putchar(buf[j]);
  
  printf(": %d\n", nsyls);
}



#define HAS_NEWLINE ((readlen > 0) && (buf[readlen-1] == '\n'))

static int process(const char *input)
{
  FILE *fp;
  char *buf;
  size_t readlen;
  uint32_t buflen = BUFLEN;
  int start, end, wordlen, nsyls;
  
  fp = fopen(input, "r");
  if (!fp)
    return READ_FAIL;
  
  buf = malloc(buflen * sizeof(*buf));
  
  
  while (fgets(buf, BUFLEN, fp) != NULL)
  {
    readlen = strnlen(buf, BUFLEN);
    if (!HAS_NEWLINE)
    {
      fseek(fp, -buflen, SEEK_CUR);
      buflen *= 2;
      buf = realloc(buf, buflen);
    }
    
    start = 0;
    for (int i=0; i<readlen; i++)
    {
      wordlen = findword(buf, readlen, &start, &end);
      if (wordlen == -1)
        continue;
      
      nsyls = count_syllables(buf+start, wordlen);
      
      print_counts(buf, start, end, nsyls);
      
      start = end+1;
    }
    
/*    printf("NEWLINE\n");*/
  }
  
  
  cleanup:
    fclose(fp);
    free(buf);
  
  return 0;
}



int main(int argc, char **argv)
{
  if (argc == 1)
  {
    printf("ERROR: you must supply a text file to process\n");
    exit(-1);
  }
  else if (argc > 2)
  {
    printf("ERROR: invalid arguments\n");
    exit(-1);
  }
  
  process(argv[1]);
  
  return 0;
}


