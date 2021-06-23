#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iomanip>
#include <iostream>

#include "Regression.hpp"
#include "doctest.h"

TEST_CASE("TEST N. 1") {
  double x_values[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  double y_values[10]{2.03, 3.82,   6.4,    7.6,    11.2,
                      12.1, 14.008, 15.992, 19.002, 20.2};
  Regression<double> reg{10, x_values, y_values};
  auto result = reg.parameters();
  CHECK(result[0] == doctest::Approx(-0.0277333));
  CHECK(result[1] == doctest::Approx(2.04781));
  CHECK(reg.x_sum == doctest::Approx(55));
  CHECK(reg.y_sum == doctest::Approx(112.352));
  CHECK(reg.x_sum2 == doctest::Approx(385));
  CHECK(reg.xy_sum == doctest::Approx(786.88));
  reg.print_pretty(result);
}
TEST_CASE("TEST N. 2") {
  int x_values[5]{1, 2, 3, 4, 5};
  int y_values[5];
  for (int i = 0; i != 5; ++i) {
    y_values[i] = 2 * x_values[i] + 3;
  }
  Regression<int> reg{5, x_values, y_values};
  auto result = reg.parameters();
  CHECK(result[0] == doctest::Approx(3));
  CHECK(result[1] == doctest::Approx(2));
  reg.print_pretty(result);
}

/*TEST_CASE("TEST N. 3") {
        std::vector<double> x_values{1, 2, 3};
        std::vector<double> y_values;
        for (int i = 0; i != 3; ++i) {
                y_values[i] = -3.99 + 4 * x_values[i];
        }
        Regression<std::vector<double>> reg{3, x_values, y_values};
        auto result = reg.parameters();
        CHECK(result[0] == doctest::Approx(-3.99));
        CHECK(result[1] == doctest::Approx(4));
}*/
