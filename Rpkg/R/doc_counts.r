#' doc_counts
#' 
#' @description
#' Computes some basic document counts (see the 'Value' section below for
#' details).
#' 
#' The function is vectorized by document, and scores are computed in parallel
#' via OpenMP.  You can control the number of threads used with the
#' \code{nthreads} parameter.
#' 
#' @details
#' The function is essentially just \code{readability()} without the readability
#' scores.
#' 
#' @param s
#' A character vector (vector of strings).
#' @param nthreads
#' Number of threads to use. By default it will use the total number of
#' cores + hyperthreads.
#' 
#' @return
#' A dataframe containing:
#' \tabular{ll}{
#'   \code{chars}     \tab the total numberof characters \cr
#'   \code{wordchars} \tab the number of alphanumeric characters \cr
#'   \code{words}     \tab text tokens that are probably English language words \cr
#'   \code{nonwords}  \tab text tokens that are probably not English language words \cr
#'   \code{sents}     \tab the number of sentences recognized in the text \cr
#'   \code{sylls}     \tab the total number of syllables (ignores all non-words) \cr
#'   \code{polys}     \tab the total number of "polysyllables", or words with 3+ syllables \cr
#' }
#' 
#' @examples
#' library(sylcount)
#' a <- "I am the very model of a modern major general."
#' b <- "I have information vegetable, animal, and mineral."
#' 
#' doc_counts(c(a, b), nthreads=1)
#' 
#' @useDynLib sylcount R_corpus_summary
#' @seealso \code{\link{readability}}
#' @export
doc_counts <- function(s, nthreads=sylcount.nthreads())
{
  .Call(R_corpus_summary, s, nthreads)
}
