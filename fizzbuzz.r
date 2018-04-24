fizzbuzz <- function(n) {
  if ((n %% 3 == 0) & (n %% 5 == 0)) {
    return("FizzBuzz")
  } else if (n %% 3 == 0) {
    return("Fizz")
  } else if (n %% 5 == 0) {
    return("Buzz")
  } else {
    return(n)
  }
}

for (n in 1:20) {
  print(fizzbuzz(n))
}
