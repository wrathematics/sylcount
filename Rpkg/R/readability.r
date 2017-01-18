#' readability
#' 
#' TODO
#' 
#' @details
#' TODO
#' 
#' @param s
#' A character vector (vector of strings).
#' 
#' @references
#' TODO
#' 
#' @export
readability <- function(s) .Call(R_readability, s)
