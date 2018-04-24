function fizzbuzz(n) {
  if ((n % 3 == 0) && (n % 5 == 0)) {
    return 'FizzBuzz';
  } else if (n % 3 == 0) {
    return 'Fizz';
  } else if (n % 5 == 0) {
    return 'Buzz';
  } else {
    return n;
  }
}

for (var n = 1; n <= 20; n++) {
  print(fizzbuzz(n));
}
