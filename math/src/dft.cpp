#include <math.h>

#include <cmath>
#include <complex>
#include <iostream>
#include <limits>

#include "Eigen/Dense"
#include "Eigen/src/Core/Matrix.h"

#define FREQ_ROWS 20000
#define FREQ_COLS 256
// using Eigen::MatrixXd;
// using Eigen::Matrix;
using Eigen::MatrixXf;
// using Eigen::seqN;
// using Eigen::VectorXf;
using Eigen::VectorXcf;
using std::complex;

void dft(float f, Eigen::Vector<float, FREQ_COLS> little_h_samples) {
  complex<float> summation = 0.f;
  complex<float> little_n = 0.f;
  complex<float> big_n = 256.f;
  complex<float> little_j;
  // welp.
  little_j.imag(1.f);
  little_j.real(1);

  // complex<float> little_k = 440.f;
  complex<float> little_k = (complex<float>)f;

  for (int n = 0; n < 256; n += 1) {
    little_n = (complex<float>)n;
    complex<float> x_sub_n = little_h_samples(n);
    complex<float> x_part =
        (-2.f * (complex<float>)M_PI * little_k * little_n) / (big_n);
    complex<float> cos_part = std::cos(x_part);
    complex<float> sin_part = little_j * std::sin(x_part);

    summation += x_sub_n * (cos_part + sin_part);
  }

  std::cout << "_little k: " << little_k << std::endl;
  std::cout << "summation: " << summation << std::endl;
  std::cout << "magnitude: " << std::abs(summation) << std::endl;
}

int main(int argc, char **argv) {
  int num_samples = 256;
  float freq = 440.f;

  Eigen::Vector<float, FREQ_COLS> little_h_samples;

  float sample_rate = 48000.f;
  float dt = 1 / sample_rate;
  int sample_count = 0;
  float phase = 0.0f;
  float result = 0.f;

  for (int idx = 0; idx < FREQ_COLS; ++idx, phase += dt) {
    result = sin(M_PI * 2 * freq * phase);
    little_h_samples(idx) = result;
  }

  // THis is too large to be stacked...
  // Eigen::Vector<std::complex<float>, FREQ_ROWS + 1> big_h_samples;
  // Eigen::Vector<std::complex<float>, FREQ_ROWS + 1> big_h_samples;

  VectorXcf big_h_samples(FREQ_ROWS + 1);
  complex<float> two_pi_i;
  two_pi_i.real(2.f * M_PI);
  two_pi_i.imag(1.f);

  complex<float> n_minus_one;
  n_minus_one.real(FREQ_COLS - 1.f);
  complex<float> LITTLE_I;
  LITTLE_I.real(1.f);
  LITTLE_I.imag(1.f);

  complex<float> sum = 0.f;
  complex<float> delta = 1.f / 48000.f;
  complex<float> big_n = 256.f;

  // TODO: maybe it makes sense to try it for one frequency...
  // or like...reproducing a known example...yeah...
  for (int f = 0; f < FREQ_ROWS + 1; ++f) {
    sum = 0.f;
    for (int k = 0; k < FREQ_COLS / 4; k++) {
      complex<float> J = 1.f;
      J.imag(1.f);
      complex<float> F = (complex<float>)f;
      complex<float> LITTLE_K = (complex<float>)k;
      complex<float> N = 256.f;
      complex<float> TWO_PI = (complex<float>)M_PI;
      complex<float> MINUS_ONE = -1.f;
      complex<float> LITTLE_N = F;

      TWO_PI *= 2.f;

      // HERE: ...complex multiplication trustworthy?
      // complex<float> exponent = -1.f * two_pi_i * F * (K / big_n);
      complex<float> exponent =
          MINUS_ONE * J * (TWO_PI / N) * LITTLE_N * LITTLE_K;

      // complex<float> sin_part;
      // sin_part.real(sin(2 * M_PI * k * f / FREQ_COLS));
      // sin_part.imag(1.f);
      // complex<float> result =
      //     little_h_samples(k) *
      //     (complex<float>)(cos(2 * M_PI * k * f / FREQ_COLS)) * sin_part;
      //
      complex<float> result = std::exp(exponent) * little_h_samples(k);
      sum += result;
    }

    // NOTE: I don't think DFT is meant to depend on delta (e.g. time) at all.
    // big_h_samples(f) = delta * sum;
    big_h_samples(f) = sum;
  }

  // for (int i = 0; i < big_h_samples.size() / 4; i++) {
  //   complex<float> sample = big_h_samples(i);
  //   float r = sample.real();
  //   float img = sample.imag();
  //
  //   std::cout << i << " " << sample << std::sqrt(r * r + img * img)
  //             << std::endl;
  // }

  // NOTE:
  //...if there is an even number of time samples
  // (always is in our case...256), then we need
  // N/2 + 1 slots in our result...

  float sum_of_samps = 0.f;

  for (int idx = 0; idx < FREQ_COLS; ++idx, phase += dt) {
    sum_of_samps += little_h_samples(idx);
  }

  std::cout << "sum_of_samps: " << sum_of_samps << std::endl;

  // TODO: simple reproduction of example, eh?
  // specify sample rate, etc...

  // {
  //   complex<float> summation = 0.f;
  //   complex<float> little_n = 0.f;
  //   complex<float> big_n = 256.f;
  //   complex<float> little_j;
  //   // welp.
  //   little_j.imag(1.f);
  //   little_j.real(1);
  //
  //   // complex<float> little_k = 440.f;
  //   complex<float> little_k = 540.f;
  //
  //   for (int n = 0; n < 256; n += 1) {
  //     little_n = (complex<float>)n;
  //     complex<float> x_sub_n = little_h_samples(n);
  //     complex<float> x_part =
  //         (-2.f * (complex<float>)M_PI * little_k * little_n) / (big_n);
  //     complex<float> cos_part = std::cos(x_part);
  //     complex<float> sin_part = little_j * std::sin(x_part);
  //
  //     summation += x_sub_n * (cos_part + sin_part);
  //   }
  //
  //   std::cout << "_little k: " << little_k << std::endl;
  //   std::cout << "summation: " << summation << std::endl;
  //   std::cout << "magnitude: " << std::abs(summation) << std::endl;
  // }

  dft(420.f, little_h_samples);
  std::cout << std::endl;
  dft(430.f, little_h_samples);
  std::cout << std::endl;
  dft(440.f, little_h_samples);
  std::cout << std::endl;
  dft(445.f, little_h_samples);
  std::cout << std::endl;
  dft(455.f, little_h_samples);
  std::cout << std::endl;
  dft(1000.f, little_h_samples);
  std::cout << std::endl;

  return 0;
}

// #define EIGEN_MAKE_TYPEDEFS_ALL_SIZES(Type, TypeSuffix) \
EIGEN_MAKE_TYPEDEFS(std::complex<float>, cf, Dynamic, X) \

//#define EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, Size, SizeSuffix)   \
// SizeSuffix == X
// Size == Dynamic
// TypeSuffix = cf
// Type = std::complex<float>
//
// typedef Matrix<Type, Size, 1>    Vector##SizeSuffix##TypeSuffix;  \
// typedef Matrix<Type, Size, 1>    == VectorXcf;
