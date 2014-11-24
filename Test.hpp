#pragma once

#include <string>
#include <iostream>
#include <cmath>

/*!
 * @namespace NumTest
 * @brief test library for Numerical Simulation
 *
 * Features
 * --------
 *  - utilize for floating comparison
 *  - class-base and without CPP macro
 *  - output result into a XML
 *
 * Usage (C++ code)
 * ----------------
 *  1. initiate global instance of NumTest::Result
 *  2. create Test instance
 *  3. do test
 *
 * Usage (command)
 * --------------
 *  0. (remove or backup old XML)
 *  1. do test using ctest
 *  2. parse XML
 *
 */
namespace NumTest {

class Test {
  std::string name, desc;
  double eps;
  size_t count, failed_count;

public:
  Test(const char *name /** identifier of test */,
       const char *desc = "" /** description of test */,
       double eps = 1e-14 /** acceptable error */)
      : name(name), desc(desc), eps(eps), count(0), failed_count(0) {}

  /** reset filename of the result XML */
  void reset_filename(const char *);

  /** reset acceptable error */
  void reset_eps(double eps_) { eps = eps_; }
  /** reset description */
  void reset_desc(std::string desc_) { desc = desc_; };
  /** get current description */
  std::string get_desc() const { return desc; }

  /** test two values are equal */
  template <typename T> void equal(T val, T ans) {
    double res;
    if ((double)ans == 0.0) {
      res = std::abs(val);
    } else {
      res = std::abs((val - ans) / ans);
    }
    if (res > eps || !std::isfinite(val)) {
      failed_count++;
      std::clog << "Name  : " << name << "\n"
                << "Type  : Value\n"
                << "Index : " << count << "\n"
                << "Desc  : " << desc << "\n"
                << "Result: Failed\n"
                << "Res   : " << res << "\n"
                << "Eps   : " << eps << std::endl;
    } else {
      std::clog << "Name  : " << name << "\n"
                << "Type  : Value\n"
                << "Index : " << count << "\n"
                << "Desc  : " << desc << "\n"
                << "Result: Success\n"
                << "Res   : " << res << "\n"
                << "Eps   : " << eps << std::endl;
    }
    count++;
  }
  /** test two ranges are equal */
  template <typename Range>
  void range_equal(const Range &val, const Range &ans) {
    auto b = std::begin(val);
    auto e = std::end(val);
    auto a = std::begin(ans);
    size_t N = e - b;
    double res, sum;
    for (; b != e; ++b, ++a) {
      sum += std::abs(a);
      res += std::abs(*b - *a);
    }
    if (sum > 0.0)
      res /= sum;
    if (res > N * eps || !std::isfinite(res)) {
      failed_count++;
      std::clog << "Name  : " << name << "\n"
                << "Type  : Range\n"
                << "Index : " << count << "\n"
                << "Desc  : " << desc << "\n"
                << "Result: Failed\n"
                << "Res   : " << res << "\n"
                << "Eps   : " << eps << std::endl;
    } else {
      std::clog << "Name  : " << name << "\n"
                << "Type  : Value\n"
                << "Index : " << count << "\n"
                << "Desc  : " << desc << "\n"
                << "Result: Success\n"
                << "Res   : " << res << "\n"
                << "Eps   : " << eps << std::endl;
    }
  }

  /** return the number of failed tests */
  size_t num_failed_tests() const { return failed_count; }
};

} // namespace NumTest
