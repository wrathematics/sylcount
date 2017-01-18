#ifndef R_SYLCOUNT_H_
#define R_SYLCOUNT_H_

#include "RNACI.h"
#include <R_ext/Utils.h>

#include "safeomp.h"

#define CHARPT(x,i) ((char*)CHAR(STRING_ELT(x,i)))
#define THROW_MEMERR() error("unable to allocate memory")
#define CHECKMALLOC(s) if (s == NULL) THROW_MEMERR()

static inline void check_interrupt_fun(void *ignored)
{
  R_CheckUserInterrupt();
}

static bool check_interrupt()
{
  return (R_ToplevelExec(check_interrupt_fun, NULL) == FALSE);
}


#endif
