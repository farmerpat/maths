#include <iostream>
#include <ostream>
#include <string>
#include <vector>

// TODO: into IntUtil
class IntToWords {
 public:
  IntToWords(int n) { _int = n; }

  std::string to_words() {
    int n = _int;
    std::string result = "";

    if (n > 1000 || n < 1) return "";
    if (n == 1000) return "one thousand ";

    if (n >= 100) {
      int how_many_hundreds = n / 100;
      std::string huns_name = _ones_word(how_many_hundreds);
      result += huns_name + " hundred ";
      n -= how_many_hundreds * 100;
      if (n > 0) {
        result += " and";
      }
    }

    if (n >= 20) {
      int how_many_tens = n / 10;
      std::string tens_name = _tens_word(how_many_tens);
      result += tens_name;
      n -= how_many_tens * 10;
    } else if (n >= 10) {
      if (n % 10 == 0) {
        result += " ten ";
      } else {
        switch (n) {
          case 11:
            result += " eleven ";
            break;
          case 12:
            result += " twelve ";
            break;
          case 13:
            result += " thirteen ";
            break;
          case 14:
            result += " fourteen ";
            break;
          case 15:
            result += " fifteen ";
            break;
          case 16:
            result += " sixteen ";
            break;
          case 17:
            result += " seventeen ";
            break;
          case 18:
            result += " eighteen ";
            break;
          case 19:
            result += " nineteen ";
            break;
        }
      }
      n -= n;
    }

    if (n > 0) {
      result += _ones_word(n);
    }

    return result;
  }

 protected:
  int _int;
  std::string _tens_word(int n) {
    if (n > 10 || n < 2) return "";
    switch (n) {
      case 2:
        return " twenty ";
      case 3:
        return " thirty ";
      case 4:
        return " forty ";
      case 5:
        return " fifty ";
      case 6:
        return " sixty ";
      case 7:
        return " seventy ";
      case 8:
        return " eighty ";
      case 9:
        return " ninety ";
    }
    return "";
  }

  std::string _ones_word(int n) {
    if (n >= 10) return "";
    switch (n) {
      case 1:
        return " one ";
      case 2:
        return " two ";
      case 3:
        return " three ";
      case 4:
        return " four ";
      case 5:
        return " five ";
      case 6:
        return " six ";
      case 7:
        return " seven ";
      case 8:
        return " eight ";
      case 9:
        return " nine ";
    }
    return "";
  }
};

/* --------------------------------------------------
If the numbers 1 to 5 are written out in words:
one, two, three, four, five, then there are
3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand)
inclusive were written out in words, how many
letters would be used?

NOTE:: Do not count spaces or hyphens.
For example, 342 (three hundred and forty-two)
contains 23 letters and 115 (one hundred and fifteen)
contains 20 letters. The use of "and" when writing
out numbers is in compliance with British usage.
 * --------------------------------------------------
 */
int main(void) {
  unsigned long result = 0;
  std::vector<std::string> all_numbers;
  for (int i = 1; i <= 1000; i++) {
    IntToWords itw(i);
    std::string words = itw.to_words();
    all_numbers.push_back(words);
  }

  for (int i = 0; i < all_numbers.size(); i++) {
    auto num = all_numbers[i];
    for (int j = 0; j < num.length(); j++) {
      char this_char = num[j];
      if (this_char == ' ' || this_char == '-') {
        continue;
      }
      ++result;
    }
  }

  std::cout << "The number of characters in the strings representing "
            << std::endl
            << "the set of the first 1000 natural numbers is " << std::endl
            << result << std::endl;
  return 0;
}

/*
Congratulations, the answer you gave to problem 17 is correct.
You are the 159136th person to have solved this problem.
This problem has a difficulty rating of 5%.
The highest difficulty rating you have solved remains at 5%.
*/
