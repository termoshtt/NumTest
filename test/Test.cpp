
#include "../Test.hpp"

using NumTest::Test;

int main(int argc, char const *argv[]) {
  Test t("test1");

  // int
  t.reset_desc("sample test for integer");
  t.equal(1, 1);  // success
  t.equal(1, -1); // failed
  t.equal(1, 0);  // failed
  t.equal(0, 0);  // success

  // double
  t.reset_desc("simple test for float");
  t.equal(1.0, 1.0);             // success
  t.equal(1.0, -1.0);            // failed
  t.equal(1.0, 0.0);             // failed
  t.equal(0.0, 0.0);             // success
  t.equal(1.0 / 0.0, 1.0 / 0.0); // failed

  // mix
  // t.equal(1.0, 0); // fails

  std::cout << t.num_failed_tests() << std::endl;
  return 0;
}
