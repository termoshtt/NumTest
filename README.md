NumTest
=======

Test framework for Numerical Simulations

Features
--------
 - fuzzy floating comparison
 - class-base and without CPP macro
 - output result into a XML

Usage 
-----

### install

Import this project into your cmake project using git-submodule:

```command
git submodule add https://github.com/termoshtt/NumTest
```

And then run `NumTest/init.sh`:

```command
cd NumTest
./init.sh
```

This downloads bootstrap and jQuery.

### write test

Single value comparison:

```cpp
#include "NumTest/Test.hpp"

int main() {
  NumTest::Test t("test",        // test name
                  "sample test", // description
                  1e-7           // eps (acceptable error)
                  );
  t.equal(1.0 + 1e-8, 1.0) << "enough small"; // success
  t.equal(1.0 - 1e-6, 1.0) << "large";        // failed
  return t; // return the number of failed tests
}
```

Range value comparison:

```cpp
#include "NumTest/Test.hpp"

int main() {
  NumTest::Test t("test"); // description and eps can be omitted out
  std::vector<double> a(10), b(10);
  /* set a, b */
  t.range_equal(a, b); // compare range value
  return t; // return the number of failed tests
}
```

### cmake setting

Include `NumTest.cmake` script in your script:

```cmake:CMakeLists.txt
include(NumTest/NumTest.cmake)
```

you have to set a path `NUMTESTXML` in `CMakeLists.txt` or `ccmake`, `cmake-gui`.

```cmake
set(NUMTESTXML /path/of/your/project/NumTest.xml)
```

This script serves following commands:

- add_num_test        : register executable
- add_num_test_long   : register executable which needs much time
- add_num_test_short  : register executable which finish in a minute

and targets:

- num_test        : compile and execute all registered tests
- num_test_long   : compile and execute tests registered via add_num_test_long
- num_test_short  : compile and execute tests registered via add_num_test_short
- new_num_test    : compile, remove old XML and execute all

You can add your test code `test1.cpp` using `add_num_test`:
We use identifier `S`(`L`) as short (long) test,
i.e. following two commands are equal:

```cmake
# short test
add_num_test(test1 S test1.cpp)
add_num_test_short(test1 test1.cpp)
# long test
add_num_test(test1 L test1.cpp)
add_num_test_long(test1 test1.cpp)
```

Then you can build and execute your tests using the targets noted above:

```command
make num_test
```

Tests will be executed by ctest command.
The results of tests are appended at the end of the XML file.
If you want to create new XML and do tests in one command,
another target exists:

```command
make new_num_test
```

Yielded XML can be converted into XHTML using `NumTest/xhtml.xslt`

```command
xsltproc NumTest/xhtml.xslt NumTest.xml > NumTest/dist/index.html
```

License
--------
MIT License
