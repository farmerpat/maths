#pragma once
#include <functional>
#include <gmpxx.h>
#include <iostream>
#include <string>
#include <vector>

// we want to be able to extend this class such that
// we call ->run and enter a repl.
// now, this class will have to know about parameters...
// it needs to know what to prompt for, what types the values are
// and what function to pass everything into once the user has
// entered everything.
// it might be very nice to be able to lock parameters from the repl...
// if we are using this for sequence experimentation (we are), then
// perhaps we'd like to lock a parameter without recompiling (we would).
enum class CrepplParamType {
  INT,
};

// TODO: this needs to be a template to sanely support additional types.
class CrepplParam {
public:
  CrepplParam();
  // TODO: hear me out. What if a third argument
  // was a collection of functions and strings for their names?
  //
  CrepplParam(std::string, CrepplParamType);
  ~CrepplParam();
  std::string prompt() const { return _prompt; }
  // unsigned long int value() const { return _value; }
  // void set_value(unsigned long int v) { _value = v; }
  mpz_class value() const { return _value; }
  void set_value(mpz_class v) { _value = v; }

protected:
  CrepplParamType _type;
  std::string _prompt;
  mpz_class _value{-1};
};

class CrepplFnSpec {
public:
  CrepplFnSpec() {}
  CrepplFnSpec(std::function<std::string(std::vector<CrepplParam>)>,
               std::string, std::string);
  std::string name() { return _name; }
  std::function<std::string(std::vector<CrepplParam>)> f() { return _fn; }

protected:
  std::function<std::string(std::vector<CrepplParam>)> _fn;
  std::string _short_name;
  std::string _name;
};

class Creppl {
public:
  bool TERMINUS = false;
  Creppl();
  Creppl(std::function<std::string(std::vector<CrepplParam>)>,
         std::vector<CrepplParam>);
  Creppl(std::vector<std::function<std::string(std::vector<CrepplParam>)>>,
         std::vector<CrepplParam>);
  Creppl(std::vector<CrepplFnSpec>);
  ~Creppl();
  std::vector<CrepplParam> params() const { return _params; }

  void run();

protected:
  // TODO: probably going...really probably consumed by FnSpec.
  std::vector<CrepplParam> _params;
  // std::vector<std::function<std::string(std::vector<CrepplParam>)>> _fns;
  std::vector<CrepplFnSpec> _fns;
  void read();
  void eval();
  void print();
  std::string _current_fn_short_name = "";
  mpz_class _current_param_value{-1};
  std::string _result;
  mpz_class _error_value{1};
};
