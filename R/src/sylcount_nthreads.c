#include "include/common.h"
#include "include/RNACI.h"

#ifdef _OPENMP
#include <omp.h>
#endif

static inline int num_threads()
{
  int n = 0;
  
#ifdef _OPENMP
  int nth, tl;
  #pragma omp parallel
  {
    nth = omp_get_num_threads();
    tl = omp_get_thread_limit();
  }
  
  n = SYLCOUNT_MIN(nth, tl);
#else
  n = 1;
#endif
  
  return n;
}



SEXP R_sylcount_nthreads()
{
  SEXP nth;
  newRvec(nth, 1, "int");
  
  INT(nth) = num_threads();
  
  R_END;
  return nth;
}
