/*  Copyright (c) 2017 Drew Schmidt
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    
    1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
  
  return SYLCOUNT_MAX(1, nsyls);
}


#endif
