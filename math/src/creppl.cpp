#include "creppl.hpp"

#include <string>

inline std::string rtrim(std::string &s) {
  std::string trimmed;
  int first_non_wite_on_the_right = -1;
  int end = s.length() - 1;
  for (int i = end; i >= 0; i--) {
    if (!std::isspace(s[i])) {
      first_non_wite_on_the_right = i;
      break;
    }
  }

  if (first_non_wite_on_the_right != -1) {
    return s.substr(0, first_non_wite_on_the_right + 1);
  }

  return s;
}

CrepplParam::CrepplParam() {}
CrepplParam::CrepplParam(std::string prompt, CrepplParamType type) {
  _prompt = prompt;
  _type = type;
}

CrepplParam::~CrepplParam() {}

Creppl::Creppl() {}

Creppl::Creppl(std::function<std::string(std::vector<CrepplParam>)> fn,
               std::vector<CrepplParam> params) {
  _fn = fn;
  _params = params;
}

Creppl::~Creppl() {}

void Creppl::read() {
  std::cout << std::endl;

  for (int i = 0; i < _params.size(); i++) {
    CrepplParam this_param = _params[i];
    std::cout << this_param.prompt() + " ";
    std::string input;
    std::getline(std::cin, input);

    if (rtrim(input) == "Q" || rtrim(input) == "q") {
      TERMINUS = true;
      break;
    }

    _params[i].set_value(std::stoi(input));
  }
}

void Creppl::eval() { _result = _fn(_params); }

void Creppl::print() { std::cout << _result << std::endl; }

void Creppl::run() {
  while (!TERMINUS) {
    read();
    if (TERMINUS) break;
    eval();
    print();
  }
}
