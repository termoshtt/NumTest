#pragma once

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

class Test;

class SubTest;

} // namespace NumTest
