#' sylcount
#' 
#' A simple, vectorized syllable counter for English language text.
#' 
#' @details
#' The syllable counter uses a hash table of known, mostly "irregular" (with
#' respect to syllable counting) words.  If the word is not known to us
#' (i.e., not in the hash table), then we try to "approximate" the number
#' of syllables by counting the number of non-consecutive vowels in a word.
#' 
#' So for example, using this scheme, each of "to", "too", and "tool" would be
#' classified as having one syllable.  However, "tune" would be classified as
#' having 2.  Fortunately, "tune" is in our table, listed as having 1 syllable.
#' 
#' The hash table uses a perfect hash generated by gperf.
#' 
#' @param s
#' A character vector (vector of strings).
#' @param counts.only
#' Should only counts be returned, or words + counts.
#' 
#' @return
#' A list of dataframes.
#' 
#' @examples
#' library(sylcount)
#' a <- "I am the very model of a modern major general."
#' b <- "I have information vegetable, animal, and mineral."
#' 
#' sylcount(c(a, b)) # counts.only=TRUE
#' sylcount(c(a, b), counts.only=FALSE)
#' 
#' @seealso \code{\link{readability}}
#' @export
sylcount <- function(s, counts.only=TRUE) .Call(R_sylcount, s, counts.only)
