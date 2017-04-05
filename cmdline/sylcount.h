#ifndef SYLCOUNT_H_
#define SYLCOUNT_H_


#include <string.h>
#include "hash.h"

typedef struct sylcount sylcount_t;

#define SYLCOUNT_MAX(a,b) (a<b?b:a)


#define BUFLEN         4096
#define WORD_OVERFLOW   128

#define READ_FAIL     -1
#define WRITE_FAIL    -2
#define LONGWORD_FAIL -3


#endif
