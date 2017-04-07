/* Automatically generated. Do not edit by hand. */

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h>

extern SEXP R_readability(SEXP s_);
extern SEXP R_sylcount(SEXP s_, SEXP counts_only_);
extern SEXP R_corpus_summary(SEXP s_);

static const R_CallMethodDef CallEntries[] = {
  {"R_readability", (DL_FUNC) &R_readability, 1},
  {"R_sylcount", (DL_FUNC) &R_sylcount, 2},
  {"R_corpus_summary", (DL_FUNC) &R_corpus_summary, 1},
  {NULL, NULL, 0}
};

void R_init_sylcount(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
