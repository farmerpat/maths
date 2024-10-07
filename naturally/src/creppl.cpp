#include "creppl.hpp"
#include <exception>
#include <gmpxx.h>
#include <stdexcept>

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

CrepplFnSpec::CrepplFnSpec(
    std::function<std::string(std::vector<CrepplParam>)> fn,
    std::string short_name, std::string name)
    : _fn(fn), _short_name(short_name), _name(name) {}

CrepplParam::CrepplParam() {}
CrepplParam::CrepplParam(std::string prompt, CrepplParamType type) {
  _prompt = prompt;
  _type = type;
}

CrepplParam::~CrepplParam() {}

Creppl::Creppl() {}

Creppl::Creppl(std::function<std::string(std::vector<CrepplParam>)> fn,
               std::vector<CrepplParam> params) {
  std::vector<std::function<std::string(std::vector<CrepplParam>)>> fns{fn};
  // TODO:
  // _fns = fns;
  _params = params;
}

Creppl::Creppl(
    std::vector<std::function<std::string(std::vector<CrepplParam>)>> fns,
    std::vector<CrepplParam> params) {
  // TODO:
  // _fns = fns;
  _params = params;
}

Creppl::Creppl(std::vector<CrepplFnSpec> fns) : _fns(fns) {
  // default to first one.
  if (_fns.size() > 0) {
    _current_fn_short_name = _fns[0].name();
  }

  std::vector<CrepplParam> params{CrepplParam{"n:", CrepplParamType::INT}};
  _params = params;
}

Creppl::~Creppl() {}

// NOTE: assume single param for all for now.
void Creppl::read() {
  // HERE:
  std::cout << std::endl;

  auto param = _params[0];

  std::cout << param.prompt();
  std::string input;
  std::getline(std::cin, input);

  // TODO: see if it matches a fn short name.
  if (rtrim(input) == "Q" || rtrim(input) == "q") {
    TERMINUS = true;

    // TODO: else if it matches the shortname of any fn, set that shit.

  } else {
    try {
      mpz_class v{input};
      _current_param_value = v;

    } catch (std::invalid_argument e) {
      std::cout << "error: invalid_argument..." << std::endl;
      std::cout << e.what() << std::endl;
      _current_param_value = _error_value.get_ui();

    } catch (std::out_of_range e) {
      std::cout << "error: out_of_range..." << std::endl;
      std::cout << e.what() << std::endl;
      _current_param_value = _error_value.get_ui();

    } catch (std::runtime_error e) {
      std::cout << "runtime_error..." << std::endl;
      std::cout << e.what() << std::endl;
      _current_param_value = _error_value.get_ui();
    }
  }

  // for (int i = 0; i < _params.size(); i++) {
  //   CrepplParam this_param = _params[i];
  //   std::cout << this_param.prompt() + " ";
  //   std::string input;
  //   std::getline(std::cin, input);
  //
  //   // TODO: "m/M" for menu. create a library of functions to call.
  //   // variable number of params...consider god/universe/monad object,
  //   // some collection containing variables created from repl...
  //   // e.g. imagine a true repl. some sub language could be created s.t.
  //   // z n = 1
  //   // creates mpz_class{1} and sticks it in a hash table under "n" or
  //   // something.
  //   // how about simply <variable_name>{<init_value>} like
  //   // n{1}
  //   // isn't that enough?
  //   if (rtrim(input) == "Q" || rtrim(input) == "q") {
  //     TERMINUS = true;
  //     break;
  //   }
  //
  //   try {
  //     mpz_class v{input};
  //     _params[i].set_value(v);
  //   } catch (std::out_of_range e) {
  //     std::cout << "error: out_of_range..." << std::endl;
  //     std::cout << e.what() << std::endl;
  //     _params[i].set_value(_error_value.get_ui());
  //   } catch (std::runtime_error e) {
  //     std::cout << "runtime_error..." << std::endl;
  //     std::cout << e.what() << std::endl;
  //     _params[i].set_value(_error_value.get_ui());
  //   }
  // }
}

void Creppl::eval() {
  // apply it to one of the fns... which one is selected? how do we know?
  // grab the current fn given short_name. apply single value to the thing...
  CrepplFnSpec current_fn;

  for (int i = 0; i < _fns.size(); i++) {
    auto fn = _fns[i];
    if (fn.name() == _current_fn_short_name) {
      current_fn = fn;
      break;
    }
  }

  _params[0].set_value(_current_param_value);

  // TODO: assume it doesn't care about params rn...
  // _result = current_fn.f()(_params);
  _result = current_fn.f()(_params);
}

void Creppl::print() { std::cout << _result << std::endl; }

void Creppl::run() {
  while (!TERMINUS) {
    read();
    if (TERMINUS)
      break;
    eval();
    print();
  }
}
