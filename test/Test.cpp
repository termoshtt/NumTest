
#include "../Test.hpp"

using NumTest::Test;

size_t test1() {
  Test t("test1", "sample test 1");

  // int
  t.equal(1, 1);  // success
  t.equal(1, -1); // failed
  t.equal(1, 0);  // failed
  t.equal(0, 0);  // success
  t.equal(3, 2);  // failed

  // double
  t.equal(1.0, 1.0);             // success
  t.equal(1.0, -1.0);            // failed
  t.equal(1.0, 0.0);             // failed
  t.equal(0.0, 0.0);             // success
  t.equal(1.0 / 0.0, 1.0 / 0.0); // failed

  // mix
  t.equal(1.0, 0); // failed

  return t.num_failed_tests();
}

size_t test2() {
  Test t("test2", "sample test 2", 1e-7);
  t.equal(1.0 + 1e-8, 1.0); // success
  t.equal(1.0 - 1e-6, 1.0); // failed
  return t.num_failed_tests();
}

int main(int argc, char const *argv[]) {
  Test t("NumTest", "test for NumTest.Test");
  auto res1 = test1();
  t.equal(res1, 7);

  auto res2 = test2();
  t.equal(res2, 1);
  return t.num_failed_tests();
}
