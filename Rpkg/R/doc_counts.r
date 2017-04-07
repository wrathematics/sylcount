#' doc_counts
#' 
#' 
#' 
#' @details
#' The function is essentially just \code{readability()} without the readability
#' scores.
#' 
#' @param s
#' A character vector (vector of strings).
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
#' \dontrun{
#' library(sylcount)
#' a <- "I am the very model of a modern major general."
#' b <- "I have information vegetable, animal, and mineral."
#' 
#' doc_counts(c(a, b))
#' }
#' 
#' @seealso \code{\link{readability}}
#' @export
doc_counts <- function(s) .Call(R_corpus_summary, s)
