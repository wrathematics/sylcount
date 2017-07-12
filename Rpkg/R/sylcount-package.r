#' sylcount: Syllable Counting and Readability Measurements
#' 
#' An English language syllable counter, plus readability score
#' measure-er.  The package has been carefully optimized and should be very
#' efficient, both in terms of run time performance and memory consumption.
#' The main methods are vectorized by document, and scores for multiple
#' documents are computed in parallel via OpenMP.
#' 
#' @useDynLib sylcount R_readability R_sylcount R_corpus_summary R_sylcount_nthreads
#' 
#' @name sylcount-package
#' @docType package
#' @author Drew Schmidt \email{wrathematics AT gmail.com}
#' @keywords Package
NULL
