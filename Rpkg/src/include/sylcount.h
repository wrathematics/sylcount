#ifndef SYLCOUNT_H_
#define SYLCOUNT_H_


#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "hash.h"

typedef struct sylcount sylcount_t;

#define SYLCOUNT_MAX(a,b) ((a)<(b)?(b):(a))


static inline bool isvowel(const char c)
{
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' ||
          c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y');
}

static inline int count_syllables(const char *const restrict str, const int len)
{
  int nsyls;
  const sylcount_t *const restrict s = in_word_set(str, len);
  
  if (NULL == s)
  {
    if (len == 1)
      nsyls = 1;
    else
    {
      nsyls = isvowel(str[0]);
      for (int i=1; i<len; i++)
      {
        if (isvowel(str[i]) && !isvowel(str[i-1]))
          nsyls++;
      }
    }
  }
  else
    nsyls = s->syls;
  
  printf("%s %d %d\n", str, nsyls, NULL==s);
  
  return SYLCOUNT_MAX(1, nsyls);
}


#endif
