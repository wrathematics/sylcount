library(sylcount)

a = "I am the very model of a modern major general."
b = "I have information vegetable, animal, and mineral."
x = c(a, b)
y = paste0(a, b, collapse=" ")



test = sum(sylcount(a)[[1]])
truth = 16L
stopifnot(identical(truth, test))

test = sum(sylcount(b)[[1]])
truth = 17L
stopifnot(identical(truth, test))



test = sylcount(x)
truth = list(
  as.integer(c(1, 1, 1, 2, 2, 1, 1, 2, 2, 3)),
  as.integer(c(1, 1, 4, 4, 3, 1, 3))
)
stopifnot(identical(test, truth))

test = sylcount(y)[[1]]
stopifnot(identical(test, unlist(truth)))



truth <- data.frame(
  word=c("I", "am", "the", "very", "model", "of", "a", "modern", "major", "general", "I", "have", "information", "vegetable", "animal", "and", "mineral"),
  syllables = test,
  stringsAsFactors=FALSE
)
test = sylcount(y, counts.only=FALSE)
stopifnot(identical(truth, test[[1]]))
