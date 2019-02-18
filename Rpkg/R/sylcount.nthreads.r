#' sylcount.nthreads
#' 
#' Returns the number of cores + hyperthreads on the system.  The function
#' respects the environment variable \code{OMP_NUM_THREADS}.
#' 
#' @return
#' An integer; the number of threads.
#' 
#' @useDynLib sylcount R_sylcount_nthreads
#' @export
sylcount.nthreads <- function()
{
  .Call(R_sylcount_nthreads)
}
