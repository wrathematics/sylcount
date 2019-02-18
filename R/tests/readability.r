library(sylcount)
a <- "I am the very model of a modern major general."
b <- "I have information vegetable, animal, and mineral."

test = doc_counts(c(a, b), nthreads=1)
truth = 
data.frame(
  chars = c(46L, 50L), 
  wordchars = c(36L, 41L),
  words = c(10L, 7L), 
  nonwords = c(0L, 0L), 
  sents = c(1L, 1L), 
  sylls = c(16L, 17L), 
  polys = c(1L, 4L)
)

stopifnot(identical(test, truth))



test = readability(paste0(a, b, collapse=" "), nthreads=1)
stopifnot(all.equal(round(test$re), 34))
stopifnot(all.equal(round(test$gl), 11))
stopifnot(all.equal(test$ari, 5L))
stopifnot(all.equal(round(test$smog), 12))
stopifnot(all.equal(round(test$cl), 7))
