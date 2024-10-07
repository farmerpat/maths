#include <functional>
#include <iostream>
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
  CrepplParam(std::string, CrepplParamType);
  ~CrepplParam();
  std::string prompt() const { return _prompt; }
  int value() const { return _value; }
  void set_value(int v) { _value = v; }

 protected:
  CrepplParamType _type;
  std::string _prompt;
  int _value;
};

class Creppl {
 public:
  bool TERMINUS = false;
  Creppl();
  Creppl(std::function<std::string(std::vector<CrepplParam>)>,
         std::vector<CrepplParam>);
  ~Creppl();
  std::vector<CrepplParam> params() const { return _params; }

  void run();

 protected:
  std::vector<CrepplParam> _params;
  std::function<std::string(std::vector<CrepplParam>)> _fn;
  void read();
  void eval();
  void print();
  std::string _result;
};
