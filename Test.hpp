#pragma once

#include <string>
#include <iostream>
#include <cmath>
#include <boost/filesystem.hpp>
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
  boost::property_tree::ptree root, &tc;

  size_t count, failed_count;
  double max_res;

public:
  Test(const char *name /** identifier of test */,
       const char *desc = "" /** description of test */,
       double eps = 1e-14 /** acceptable error */)
      : name(name), desc(desc), eps(eps), tc(root.add("testClass", "")),
        count(0), failed_count(0), max_res(0.0) {
    tc.put("name", name);
    tc.put("description", desc);
    tc.put("eps", eps);
  }
  ~Test() {
    boost::property_tree::ptree pt;
#ifdef NUMTESTXML
#define EVAL(f, v) f(v)
#define TO_STR_IMPL(s) #s
#define TO_STR(s) EVAL(TO_STR_IMPL, s)
    std::string xml_fn = TO_STR(NUMTESTXML);
    if (boost::filesystem::exists(xml_fn))
      read_xml(xml_fn, pt);
    else
      pt.add("NumTest", "");
#undef EVAL
#undef TO_STR_IMPL
#undef TO_STR
#else
    std::string xml_fn = name + ".xml";
    pt.add("NumTest", "");
#endif
    tc.put("failedCount", failed_count);
    tc.put("maxResidual", max_res);
    pt.add_child("NumTest.testClass", tc);
    write_xml(xml_fn, pt);
  }

  /** reset filename of the result XML */
  void reset_filename(const char *);

  /** reset acceptable error */
  void reset_eps(double eps_) { eps = eps_; }
  /** reset description */
  void reset_desc(std::string desc_) { desc = desc_; }
  /** get current description */
  std::string get_desc() const { return desc; }

  /** test two values are equal */
  template <typename T, typename U> void equal(T val, U ans) {
    double res;
    if ((double)ans == 0.0) {
      res = std::abs(val);
    } else {
      res = std::abs((val - ans) / (double)ans);
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
    max_res = std::max(res, max_res);
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
      sum += std::abs(*a);
      res += std::abs(*b - *a);
    }
    if (sum > 0.0)
      res /= sum;
    auto &t = tc.add("test", "");
    t.put("type", "range");
    t.put("index", count);
    t.put("N", N);
    t.put("residual", res);
    count++;
    if (res > N * eps || !std::isfinite(res)) {
      failed_count++;
      t.put("result", "failed");
    } else {
      t.put("result", "success");
    }
    max_res = std::max(res, max_res);
  }

  /** return the number of failed tests */
  size_t num_failed_tests() const { return failed_count; }
};

} // namespace NumTest
