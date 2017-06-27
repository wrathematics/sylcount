#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../sylcount.h"


#define BAD_POINTER    -1
#define BAD_STR_LOOKUP -2
#define BAD_SYL_COUNT  -3


int main()
{
  sylcount_t *s;
  
  char *x = "asdf";
  s = in_word_set(x, strlen(x));
  if (NULL != s)
    exit(BAD_POINTER);
  
  char *y = "side";
  s = in_word_set(y, strlen(y));
  if (NULL == s)
    exit(BAD_POINTER);
  else if (strcmp(s->word, y) != 0)
    exit(BAD_STR_LOOKUP);
  else if (s->syls != 1)
    exit(BAD_SYL_COUNT);
  
  printf("All tests passed\n");
  
  return 0;
}
