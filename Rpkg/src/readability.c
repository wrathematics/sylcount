#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#include "R_sylcount.h"
#include "hashtable/sylcount.h"

#define BUFLEN 64

static inline bool is_sentend(const char c)
{
  return (c=='.' || c==';' || c=='!' || c=='?');
}

static inline int is_wordend(const char c)
{
  return (isspace(c) || ispunct(c) || c == '\0');
}

// Flesch reading ease
static inline double re_score(const uint32_t tot_words, const uint32_t tot_sents, const uint32_t tot_sylls)
{
  return 206.835 - 1.015*((double) tot_words/tot_sents) - 84.6*((double) tot_sylls/tot_words);
}

// Flesch-Kincaid grade level
static inline double gl_score(const uint32_t tot_words, const uint32_t tot_sents, const uint32_t tot_sylls)
{
  return 0.39 * ((double) tot_words/tot_sents) + 11.8 * ((double) tot_sylls/tot_words) - 15.59;
}



SEXP R_readability(SEXP s_)
{
  SEXP ret, ret_names;
  SEXP words, nw, sents, sylls, re, gl;
  const int len = LENGTH(s_);
  
  if (TYPEOF(s_) != STRSXP)
    error("input must be a vector of strings");
  
  newRvec(words, len, "int");
  newRvec(nw, len, "int");
  newRvec(sents, len, "int");
  newRvec(sylls, len, "int");
  newRvec(re, len, "dbl");
  newRvec(gl, len, "dbl");
  
  char buf[BUFLEN];
  
  for (int i=0; i<len; i++)
  {
    uint32_t tot_words = 0;
    uint32_t tot_nonwords = 0;
    uint32_t tot_sents = 0;
    uint32_t tot_sylls = 0;
    
    const char *const s = CHARPT(s_, i);
    const int slen = strlen(s);
    
    int start = 0;
    int end;
    
    for (int j=0; j<=slen; j++)
    {
      if (is_wordend(s[j]))
      {
        end = j;
        if (end-start > BUFLEN)
        {
          tot_nonwords++;
          continue;
        }
        else
          tot_words++;
        
        memcpy(buf, s+start, end-start);
        buf[end-start] = '\0';
        tot_sylls += count_syllables(buf, end-start);
        
        if (is_sentend(s[j]))
          tot_sents++;
        
        while (ispunct(s[j]) || isspace(s[j]))
          j++;
        
        start = j;
      }
    }
    
    INT(words, i) = tot_words;
    INT(nw, i) = tot_nonwords;
    INT(sents, i) = tot_sents;
    INT(sylls, i) = tot_sylls;
    DBL(re, i) = re_score(tot_words, tot_sents, tot_sylls);
    DBL(gl, i) = gl_score(tot_words, tot_sents, tot_sylls);
  }
  
  ret_names = make_list_names(6, "words", "nonwords", "sentences", "syllables", "reading.ease", "grade.level");
  ret = make_dataframe(RNULL, ret_names, 6, words, nw, sents, sylls, re, gl);
  
  R_END;
  return ret;
}