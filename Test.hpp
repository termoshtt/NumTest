#pragma once

#include <string>
#include <iostream>
#include <cmath>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

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
  boost::property_tree::ptree root, &tc;

public:
  Test(const char *name /** identifier of test */,
       const char *desc = "" /** description of test */,
       double eps = 1e-14 /** acceptable error */)
      : name(name), desc(desc), eps(eps), count(0), failed_count(0),
        tc(root.add("testClass", "")) {
    tc.put("name", name);
    tc.put("description", desc);
    tc.put("eps", eps);
  }
  ~Test() { write_xml(name + ".xml", root); }

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
    auto &t = tc.add("test", "");
    t.put("type", "value");
    t.put("residual", res);
    t.put("index", count);
    count++;
    if (res > eps || !std::isfinite(val)) {
      failed_count++;
      t.put("result", "failed");
    } else {
      t.put("result", "success");
    }
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
    auto &t = tc.add("test", "");
    t.put("type", "range");
    t.put("index", count);
    t.put("N", N);
    t.put("residual", res);
    if (res > N * eps || !std::isfinite(res)) {
      failed_count++;
      t.put("result", "failed");
    } else {
      t.put("result", "success");
    }
  }

  /** return the number of failed tests */
  size_t num_failed_tests() const { return failed_count; }
};

} // namespace NumTest