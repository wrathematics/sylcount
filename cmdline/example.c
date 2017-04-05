#include <stdio.h>
#include <string.h>

#include "hash.h"

typedef struct sylcount sylcount_t;

static inline void print_lookup(char *str)
{
  const sylcount_t *s = in_word_set(str, strlen(str));
  
  if (NULL == s)
    printf("%s: It's a mystery!\n", str);
  else
    printf("%s: %d\n", s->word, s->syls);
  
  return;
}



int main()
{
  print_lookup("once");
  print_lookup("asdf");
  print_lookup("side");
  print_lookup("banana");
  print_lookup("pictures");
  
  return 0;
}
