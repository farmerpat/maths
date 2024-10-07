// g++ -o siz sizeof.cpp
// ~/.local/share/nvim/mason/bin/clang-format --style Google --dump-config >
// .clang-format but default is K&r
#define SAMPLE_RATE 48000.0
// TODO: probably this ought to be 1/SR. explicate 2pi in call to sin for rad
// conversion.
#define STEP_SIZE (1.0 / SAMPLE_RATE)

#include <math.h>

#include <climits>
#include <cmath>
#include <iostream>

class Oscillator {
 public:
  Oscillator();
  // pitch freq and  sample_rate
  Oscillator(float, float);
  ~Oscillator();
  void tick();
  float get_sin();

 protected:
  float _frequency;
  float _sample_rate;
  // inverse of _sample_rate;
  float _phase;
  float _dt;
};

Oscillator::Oscillator() {
  _frequency = 1.f;
  _sample_rate = 256.f;
  _dt = 1.f / _sample_rate;
  _phase = 0.0;
}

Oscillator::Oscillator(float frequency, float sample_rate) {
  _frequency = frequency;
  _sample_rate = sample_rate;
  _dt = 1.f / _sample_rate;
  _phase = 0.0;
}

Oscillator::~Oscillator() {}

float Oscillator::get_sin() { return sinf(2 * M_PI * _frequency * _phase); }

void Oscillator::tick() {
  _phase += _dt;
  if (_phase >= 1.0f) {
    // NOTE: why not set to zero?
    // is there really a difference?
    _phase -= 1.f;
  }
}

int main(void) {
  float result;
  unsigned long ticker = 0;

  const float TWO_PI = M_PI * 2;

  float sample_rate = 48000.0;
  int samples_to_process = 256;
  float frequency = 440.f;
  float step = 0.0;

  Oscillator osc(440.f, 48000.0f);

  for (int i = 0; i < samples_to_process; i++) {
    result = osc.get_sin();
    std::cout << result << std::endl;
    osc.tick();
  }

  return 0;
}
