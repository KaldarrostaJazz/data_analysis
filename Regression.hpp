#ifndef REGRESSION_HPP
#define REGRESSION_HPP
#include <array>
#include <cmath>
#include <numeric>
#include <iostream>
#include <iomanip>

/////////////////////////////////////////////////|
// Class declaration ////////////////////////////|
/////////////////////////////////////////////////|

template <class Ptr>
class Regression {
 private:
  int n_points;
  Ptr* x_vector;
  Ptr* y_vector;

 public:
  Regression(int n, Ptr* x_values, Ptr*  y_values)
      : n_points{n}, x_vector{x_values}, y_vector{y_values} {}

  double x_sum = std::accumulate(x_vector, x_vector + n_points, 0.);
  double y_sum = std::accumulate(y_vector, y_vector + n_points, 0.);
  double x_sum2 = sum_squares(x_vector, x_vector + n_points, 0.);
  double xy_sum = sum_couple(n_points, x_vector, y_vector, 0.);
  double sum_squares(Ptr* first, Ptr* last, double init);
  double sum_couple(int n, Ptr* x_first, Ptr* y_first, double init);
  std::array<double, 2> parameters();
  void print_pretty(std::array<double, 2>& result);
};

/////////////////////////////////////////////////|
// Methods definitions //////////////////////////|
/////////////////////////////////////////////////|

template <class Ptr>
inline double Regression<Ptr>::sum_squares(Ptr* first, Ptr* last, double init) {
  for (; first != last; ++first) {
    init += std::pow(*first, 2);
  }
  return init;
}

template <class Ptr>
inline double Regression<Ptr>::sum_couple(int n, Ptr* x_first, Ptr* y_first, double init) {
  for (int i = 0; i != n; ++i) {
    double x = *x_first;
    double y = *y_first;  
    init += x * y;
    ++x_first;
    ++y_first;
  }
  return init;
}

template <class Ptr>
inline std::array<double, 2> Regression<Ptr>::parameters() {
  double delta = n_points * x_sum2 - x_sum * x_sum;
  if (delta == 0.) throw std::runtime_error("Vertical line!\n");
  double A = (y_sum * x_sum2 - x_sum * xy_sum) / delta;
  double B = (n_points * xy_sum - x_sum * y_sum) / delta;
  std::array<double, 2> result{A, B};
  return result;
}

template <class Ptr>
inline void Regression<Ptr>::print_pretty(std::array<double, 2>& result) {
	using namespace std;
	cout << left << setfill('-') << setw(25) << "+" << "+" << '\n';
	cout << setfill(' ') << setw(25) << "|Estimated parameters:" << "|" << '\n';
	cout << setw(11) << "|Costant =" << setw(14) << result[0] << "|" << '\n'; 
	cout << setw(11) << "|Slope =" << setw(14) << result[1] << "|" << '\n';
	cout << setfill('-') << setw(25) << "+" << "+" << '\n';
}

#endif
