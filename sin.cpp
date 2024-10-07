#include <math.h>

#include <cmath>
#include <iostream>

// Definite integral of sin(freq*x) over [lb-ub]
template <typename T>

T sin_at_freq_over_interval(T freq, T ub, T lb) {
  T a = M_2_PI / freq;
  return (-std::cos(ub * a)) - (-std::cos(lb * a));
}

// e.g. how much time passes over this number of samples?
// todo: try making this into a template...
// that way, if you switch to floats (you will)
// it won't matter so much.
// yes, above also.
template <typename T>
T time_ellapsed_over_num_samples(T num_samples, T sample_rate) {
  T time_per_sample = 1.0 / sample_rate;
  return num_samples * time_per_sample;
}

int main(void) {
  // given: sample_rate of requestor
  // given: number of samples
  //
  // we can compute how much time that is.
  // double sample_rate = 44100.0;
  double sample_rate = 1000.0;
  double samples_requested = 5.0;
  double pitch_freq = 440.0;
  double total_time =
      time_ellapsed_over_num_samples(samples_requested, sample_rate);
  double time_per_sample = 1.0 / sample_rate;
  double upper_bound = time_per_sample;
  double lower_bound = 0.;

  // TODO: ultimatley, we'll want to keep track of our i value
  // and restore the generation loop to the state held when silenced.
  // first interval is [0 time_per_sample];
  // the second interval is [time_per_sample timer_per_sample*2]
  // then the current interval is [time_per_sample*i time_per_sample*(i+1)]
  // and that for loop is how we build our shit.
  // guess what huck:
  // you're going to want to allocate memory for this.
  // don't. not yet.
  // baby steps.
  // or...
  // start with a fn sig like this
  // sin_generator.set_samples(num_samples, pointer_to_floats)
  // it can just write resulting floats to the pointer.
  // relax.

  // given pointer to location of floats and num_samples,
  // loop for i upto num_samples.
  // upper_bound = time_per_sample(i+1)
  // lower_bound = time_per_sample(i+1)
  // result = sin_at_freq_over_interval(freq, upper_bound, lower_bound)
  double result =
      sin_at_freq_over_interval(pitch_freq, upper_bound, lower_bound);

  std::cout << "total_time: " << total_time << std::endl;
  std::cout << "the : " << result << std::endl;
  return 0;
}
