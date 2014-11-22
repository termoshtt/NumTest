#pragma once

#include <string>
#include <mutex>

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
  size_t count;

public:
  Test(const char *name /** identifier of test */,
       const char *desc = "" /** description of test */,
       double eps = 1e-14 /** acceptable error */)
      : name(name), desc(desc), eps(eps), count(1) {}

  /** reset filename of the result XML */
  void reset_filename(const char *filename);

  /** reset acceptable error */
  void reset_eps(double eps_) { eps = eps_; }
  /** reset description */
  void reset_desc(std::string desc_) { desc = desc_; };
  /** get current description */
  std::string get_desc() const { return desc; }

  /** test two values are equal */
  template <typename T> void equal(T val, T ans);
  /** test two ranges are equal */
  template <typename Range>
  void range_equal(const Range &val, const Range 6ans);
};

} // namespace NumTest
