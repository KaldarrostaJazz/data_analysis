#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cassert>
#include <stdexcept>
#include <vector>
//////////////////////////////////////////////////
// Class declarations ////////////////////////////
//////////////////////////////////////////////////
class Fit {
 private:
  std::vector<double> observed;

 public:
  Fit(std::vector<double>& data) : observed{data} {
    if (observed.empty())
      throw std::runtime_error("The data vector is empty!\n");
  }
  double Chi_Square(std::vector<double>& expected);
  double RChi_Square(std::vector<double>& expected, int ndof);
};
//////////////////////////////////////////////////
// Methods definitions ///////////////////////////
//////////////////////////////////////////////////
inline double Fit::Chi_Square(std::vector<double>& expected) {
  assert(observed.size() == expected.size());
  int N = observed.size();
  double chi = 0.;
  for (int i = 0; i != N; ++i)
    chi += (observed[i] - expected[i]) * (observed[i] - expected[i]) / expected[i];
  assert(chi >= 0.);
  return chi;
}

inline double Fit::RChi_Square(std::vector<double>& expected, int ndof) {
  double chi = Chi_Square(expected);
  return chi / ndof;
}
#endif
