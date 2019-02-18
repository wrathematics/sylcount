library(sylcount)

test = readability("", nthreads=1)
truth = 
data.frame(
  chars = 0L,
  wordchars = 0L,
  words = 0L,
  nonwords = 0L,
  sents = 0L,
  sylls = 0L,
  polys = 0L,
  re = NaN,
  gl = NaN,
  ari = NA_integer_,
  smog = NaN,
  cl = NaN
)

stopifnot(identical(test, truth))



test = doc_counts("", nthreads=1)
truth = truth[, 1:7]
stopifnot(identical(test, truth))



test = sylcount("")
truth = list(NA_integer_)
stopifnot(identical(test, truth))
