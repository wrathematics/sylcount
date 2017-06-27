#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>


#include "include/RNACI.h"
#include "include/sylcount.h"

#define BUFLEN 64
#define ITER_PER_CHECK 256

#define CHARPT(x,i) ((char*)CHAR(STRING_ELT(x,i)))
#define THROW_MEMERR error("unable to allocate memory")
#define CHECKMALLOC(s) if (s == NULL) THROW_MEMERR

#define CHECK_IS_FLAG(x, argname) \
  if (TYPEOF(x) != LGLSXP || LENGTH(x) != 1 || LOGICAL(x)[0] == NA_LOGICAL){ \
    error("argument '%s' must be a flag", argname);}

#define CHECK_IS_STRINGS(s) \
  if(LENGTH(s) < 1 || TYPEOF(s) != STRSXP){ \
    error("argument 's' must be a vector of strings\n");}

// #include <R_ext/Utils.h>
// static inline void check_interrupt_fun(void *ignored)
// {
//   R_CheckUserInterrupt();
// }
// 
// static bool check_interrupt()
// {
//   return (R_ToplevelExec(check_interrupt_fun, NULL) == FALSE);
// }

static inline bool is_sentend(const char c)
{
  return (c=='.' || c==';' || c=='!' || c=='?');
}

static inline bool is_wordend(const char c)
{
  return (isspace(c) || ispunct(c) || c == '\0');
}


// -------------------------------------------------------
// Various "readability" score-ers
// -------------------------------------------------------

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

// Automated Readability Index
static inline int ari_score(const uint32_t tot_chars, const uint32_t tot_words, const uint32_t tot_sents)
{
  return (int) ceil(4.71 * ((double) tot_chars/tot_words) + 0.5 * ((double) tot_words/tot_sents) - 21.43);
}

// Simple Measure of Gobbledygook
static inline double smog_score(const uint32_t tot_polys, const uint32_t tot_sents)
{
  return 1.043 * sqrt(30.0 * ((double) tot_polys/tot_sents)) + 3.1291;
}

// Coleman-Lau
static inline double cl_score(const uint32_t tot_chars, const uint32_t tot_words, const uint32_t tot_sents)
{
  return 0.0588 * ((double) 100.0 * tot_chars/tot_words) - 0.296 * ((double) 100.0 * tot_sents/tot_words) - 15.8;
}



SEXP R_readability(SEXP s_)
{
  SEXP ret, ret_names;
  SEXP chars, wordchars, words, nw, sents, sylls, polys;
  SEXP ari, re, gl, smog, cl;
  const int len = LENGTH(s_);
  
  CHECK_IS_STRINGS(s_);
  
  newRvec(chars, len, "int");
  newRvec(wordchars, len, "int");
  newRvec(words, len, "int");
  newRvec(nw, len, "int");
  newRvec(sents, len, "int");
  newRvec(sylls, len, "int");
  newRvec(polys, len, "int");
  newRvec(re, len, "dbl");
  newRvec(gl, len, "dbl");
  newRvec(ari, len, "int");
  newRvec(smog, len, "dbl");
  newRvec(cl, len, "dbl");
  
  
  #pragma omp parallel
  {
    char buf[BUFLEN];
    
    #pragma omp for
    for (int i=0; i<len; i++)
    {
      uint32_t tot_wordchars = 0;
      uint32_t tot_words = 0;
      uint32_t tot_nonwords = 0;
      uint32_t tot_sents = 0;
      uint32_t tot_sylls = 0;
      uint32_t tot_polys = 0;
      
      const char *const s = CHARPT(s_, i);
      const int slen = strlen(s);
      
      int start = 0;
      int end;
      
      for (int j=0; j<=slen && slen>0; j++)
      {
        if (isalnum(s[j]))
          tot_wordchars++;
        else if (is_sentend(s[j]))
          tot_sents++;
        
        if (is_wordend(s[j]))
        {
          // try to account for acronyms
          while (ispunct(s[j]) && !isspace(s[j+1]))
            j++;
          
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
          
          uint32_t word_sylls = count_syllables(buf, end-start);
          tot_sylls += word_sylls;
          if (word_sylls > 2)
            tot_polys++;
          
          if (is_sentend(s[j]))
            tot_sents++;
          
          while (ispunct(s[j]) || isspace(s[j]))
            j++;
          
          start = j;
          if (isalnum(s[j]))
            tot_wordchars++;
        }
      }
      
      INT(chars, i) = slen;
      INT(wordchars, i) = tot_wordchars;
      INT(words, i) = tot_words;
      INT(nw, i) = tot_nonwords;
      INT(sents, i) = tot_sents;
      INT(sylls, i) = tot_sylls;
      INT(polys, i) = tot_polys;
      DBL(re, i) = re_score(tot_words, tot_sents, tot_sylls);
      DBL(gl, i) = gl_score(tot_words, tot_sents, tot_sylls);
      INT(ari, i) = ari_score(tot_wordchars, tot_words, tot_sents);
      DBL(smog, i) = smog_score(tot_polys, tot_sents);
      DBL(cl, i) = cl_score(tot_wordchars, tot_words, tot_sents);
    }
  }
  
  
  make_list_names(ret_names, 12, "chars", "wordchars", "words", "nonwords", "sents", "sylls", "polys", "re", "gl", "ari", "smog", "cl");
  make_dataframe(ret, RNULL, ret_names, 12, chars, wordchars, words, nw, sents, sylls, polys, re, gl, ari, smog, cl);
  
  R_END;
  return ret;
}



// -------------------------------------------------------
// Syllable counter
// can not be put into separate file because gperf data isn't guarded correctly
// -------------------------------------------------------

static inline int count_words(const int len, const char*const restrict buf)
{
  int nw = 0;
  
  for (int i=0; i<=len; i++)
  {
    if (is_wordend(buf[i]))
    {
      nw++;
      
      while (ispunct(buf[i]) || isspace(buf[i]))
        i++;
    }
  }
  
  return nw;
}



// NOTE: not thread safe because of the R object memory allocations
static SEXP R_sylcount_countsAndWords(SEXP s_)
{
  SEXP ret;
  
  const int len = LENGTH(s_);
  newRlist(ret, len);
  
  for (int i=0; i<len; i++)
  {
    SEXP localdf, localdf_names;
    SEXP word, sylls;
    const char*const s = CHARPT(s_, i);
    const int slen = strlen(s);
    
    int nwords = count_words(slen, s);
    
    newRvec(word, nwords, "str");
    newRvec(sylls, nwords, "int");
    make_list_names(localdf_names, 2, "word", "syllables");
    make_dataframe(localdf, RNULL, localdf_names, 2, word, sylls);
    SET_VECTOR_ELT(ret, i, localdf);
    
    int start = 0;
    int end;
    
    int words_found = 0;
    
    for (int j=0; j<=slen; j++)
    {
      if (is_wordend(s[j]))
      {
        end = j;
        const int wordlen = end-start;
        
        SET_STRING_ELT(word, words_found, mkCharLen(s+start, wordlen));
        
        if (wordlen > BUFLEN)
          INT(sylls, words_found) = NA_INTEGER;
        else
          INT(sylls, words_found) = count_syllables(CHARPT(word, words_found), wordlen);
        
        while (ispunct(s[j]) || isspace(s[j]))
          j++;
        
        start = j;
        words_found++;
      }
    }
    
    UNPROTECT(5);
  }
  
  
  // R_END;
  UNPROTECT(1);
  return ret;
}



// NOTE: not thread safe because of the R object memory allocations
static SEXP R_sylcount_countsOnly(SEXP s_)
{
  SEXP ret;
  
  char buf[BUFLEN];
  
  const int len = LENGTH(s_);
  newRlist(ret, len);
  
  for (int i=0; i<len; i++)
  {
    SEXP sylls;
    const char*const s = CHARPT(s_, i);
    const int slen = strlen(s);
    
    if (slen == 0)
    {
      SET_VECTOR_ELT(ret, i, ScalarInteger(NA_INTEGER));
      continue;
    }
    
    
    int nwords = count_words(slen, s);
    
    newRvec(sylls, nwords, "int");
    SET_VECTOR_ELT(ret, i, sylls);
    
    int start = 0;
    int end;
    
    int words_found = 0;
    
    for (int j=0; j<=slen; j++)
    {
      if (is_wordend(s[j]))
      {
        end = j;
        const int wordlen = end - start;
        
        if (wordlen > BUFLEN)
          INT(sylls, words_found) = NA_INTEGER;
        else
        {
          memcpy(buf, s+start, wordlen);
          buf[wordlen] = '\0';
          INT(sylls, words_found) = count_syllables(buf, wordlen);
        }
        
        while (ispunct(s[j]) || isspace(s[j]))
          j++;
        
        start = j;
        words_found++;
      }
    }
    
    UNPROTECT(1);
  }
  
  
  // R_END;
  UNPROTECT(1);
  return ret;
}



SEXP R_sylcount(SEXP s, SEXP counts_only)
{
  CHECK_IS_STRINGS(s);
  CHECK_IS_FLAG(counts_only, "counts.only");
  
  if (INT(counts_only))
    return R_sylcount_countsOnly(s);
  else
    return R_sylcount_countsAndWords(s);
}



// -------------------------------------------------------
// Basic text document count summaries
// -------------------------------------------------------

SEXP R_corpus_summary(SEXP s_)
{
  SEXP ret, ret_names;
  SEXP chars, wordchars, words, nw, sents, sylls, polys;
  const int len = LENGTH(s_);
  
  CHECK_IS_STRINGS(s_);
  
  newRvec(chars, len, "int");
  newRvec(wordchars, len, "int");
  newRvec(words, len, "int");
  newRvec(nw, len, "int");
  newRvec(sents, len, "int");
  newRvec(sylls, len, "int");
  newRvec(polys, len, "int");
  
  
  #pragma omp parallel
  {
    char buf[BUFLEN];
    
    #pragma omp for
    for (int i=0; i<len; i++)
    {
      uint32_t tot_wordchars = 0;
      uint32_t tot_words = 0;
      uint32_t tot_nonwords = 0;
      uint32_t tot_sents = 0;
      uint32_t tot_sylls = 0;
      uint32_t tot_polys = 0;
      
      const char *const s = CHARPT(s_, i);
      const int slen = strlen(s);
      
      int start = 0;
      int end;
      
      for (int j=0; j<=slen && slen>0; j++)
      {
        if (isalnum(s[j]))
          tot_wordchars++;
        else if (is_sentend(s[j]))
          tot_sents++;
        
        if (is_wordend(s[j]))
        {
          // try to account for acronyms
          while (ispunct(s[j]) && !isspace(s[j+1]))
            j++;
          
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
          
          uint32_t word_sylls = count_syllables(buf, end-start);
          tot_sylls += word_sylls;
          if (word_sylls > 2)
            tot_polys++;
          
          if (is_sentend(s[j]))
            tot_sents++;
          
          while (ispunct(s[j]) || isspace(s[j]))
            j++;
          
          start = j;
          if (isalnum(s[j]))
            tot_wordchars++;
        }
      }
      
      INT(chars, i) = slen;
      INT(wordchars, i) = tot_wordchars;
      INT(words, i) = tot_words;
      INT(nw, i) = tot_nonwords;
      INT(sents, i) = tot_sents;
      INT(sylls, i) = tot_sylls;
      INT(polys, i) = tot_polys;
    }
  }
  
  make_list_names(ret_names, 7, "chars", "wordchars", "words", "nonwords", "sents", "sylls", "polys");
  make_dataframe(ret, RNULL, ret_names, 7, chars, wordchars, words, nw, sents, sylls, polys);
  
  R_END;
  return ret;
}
