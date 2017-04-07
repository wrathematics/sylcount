#' readability
#' 
#' @description
#' Computes some basic "readability" measurements, includeing Flesch Reading
#' Ease, Flesch-Kincaid grade level, Automatic Readability Index, and the
#' Simple Measure of Gobbledygook.  The function is vectorized.
#' 
#' The function will have some difficulty on poorly processed and cleaned data.
#' For example, if all punctuation is stripped out, then the number of sentences
#' detected will always be zero.  However, we do recommend removing quotes
#' (single and double), as contractions can confuse the parser.
#' 
#' @details
#' The return is split into words and non-words.  A non-word is some block
#' of text more than 64 characters long with no spaces or sentence-ending
#' punctuation inbetween.  The number of non-words is returned mostly
#' for error-checking/debugging purposes.  If you have a lot of 
#' non-words, you probably didn't clean your text properly.  The word/non-word
#' division is made in an attempt to improve run-time and memory performance.
#' 
#' For implementation details, see the Details section of \code{?sylcount}.
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
#'   \code{re}        \tab Flesch reading ease score \cr
#'   \code{gl}        \tab Flesch-Kincaid grade level score \cr
#'   \code{ari}       \tab Automatic Readability Index score \cr
#'   \code{smog}      \tab Simple Measure of Gobbledygook (SMOG) score \cr
#'   \code{cl}        \tab the Coleman-Liau Index score \cr
#' }
#' 
#' @param s
#' A character vector (vector of strings).
#' 
#' @references
#' Kincaid, J. Peter, et al. Derivation of new readability formulas (automated
#' readability index, fog count and flesch reading ease formula) for navy
#' enlisted personnel. No. RBR-8-75. Naval Technical Training Command
#' Millington TN Research Branch, 1975.
#' 
#' Senter, R. J., and Edgar A. Smith. Automated readability index. CINCINNATI
#' UNIV OH, 1967.
#' 
#' Mc Laughlin, G. Harry. "SMOG grading-a new readability formula." Journal of
#' reading 12.8 (1969): 639-646.
#' 
#' Coleman, Meri, and Ta Lin Liau. "A computer readability formula designed for
#' machine scoring." Journal of Applied Psychology 60.2 (1975): 283.
#' 
#' @examples
#' library(sylcount)
#' a <- "I am the very model of a modern major general."
#' b <- "I have information vegetable, animal, and mineral."
#' 
#' readability(a)
#' 
#' # One at a time
#' readability(c(a, b))
#' # Both at once
#' readability(paste0(a, b, collapse=" "))
#' 
#' @seealso \code{\link{doc_counts}}
#' @export
readability <- function(s) .Call(R_readability, s)
