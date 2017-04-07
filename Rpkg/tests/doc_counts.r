library(sylcount)
a <- "I am the very model of a modern major general."
b <- "I have information vegetable, animal, and mineral."

test = doc_counts(c(a, b))
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
