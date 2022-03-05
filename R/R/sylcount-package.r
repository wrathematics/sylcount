#' sylcount: Syllable Counting and Readability Measurements
#' 
#' An English language syllable counter, plus readability score measure-er. For
#' readability, we support Flesch Reading Ease and Flesch-Kincaid Grade Level
#' (Kincaid et al. 1975), Automated Readability Index (Senter and Smith 1967),
#' Simple Measure of Gobbledygook (McLaughlin 1969), and Coleman-Liau (Coleman
#' and Liau 1975). The package has been carefully optimized and should be very
#' efficient, both in terms of run time performance and memory consumption. The
#' main methods are vectorized by document, and scores for multiple documents
#' are computed in parallel via OpenMP.
#' 
#' @name sylcount-package
#' @docType package
#' @author Drew Schmidt
#' @keywords Package
NULL
