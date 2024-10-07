#pragma once

#include <gmpxx.h>

mpz_class hanoi_r(mpz_class n) {
  if (n == 0) {
    return 0;
  } else {
    return 2 * (hanoi_r(n - 1)) + 1;
  }
}

mpz_class hanoi_i(mpz_class n) {
  // T(0)
  if (n == 0) {
    return 0;
  }

  mpz_class sum(1);

  // T(n) = 2T(n-1) + 1
  // at this point, sum === T(n-1).
  // which is the same now as T(1).
  // this means that we possess T(1)
  // thus we loop n-1 times.
  for (mpz_class i(1); i < n; i++) {
    sum = 2 * sum + 1;
  }

  // then I understand how this code explicates the recurrence relation
  // detailed in CM's Hanoi example. But I don't understand how it's 2^n-1.
  // I understand I gives the same results. I'm missing something.
  // I think I have to figure it out.

  return sum;
}

// You is programmer.
// Look at what you're doing.
// This is how you understand.
// Grand.
mpz_class two_to_the_n_minus_one(unsigned long pow) {
  mpz_class result(1);
  unsigned long base = 2;
  mpz_ui_pow_ui(result.get_mpz_t(), base, pow);
  result -= 1;
  return result;
}

mpz_class two_to_the_n_minus_one_plus_one(unsigned long pow) {
  mpz_class result(1);
  unsigned long base = 2;
  mpz_ui_pow_ui(result.get_mpz_t(), base, pow - 1);
  result += 1;
  return result;
}
