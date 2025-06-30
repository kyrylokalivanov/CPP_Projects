# Rational Number Class

## Project Description

This project implements a rational number class (`wymierna`) in C++ (C++11 standard) within the `obliczenia` namespace. The class represents rational numbers as fractions (numerator and denominator), ensuring the denominator is always positive and the fraction is in its simplest form (greatest common divisor of numerator and denominator is 1). The implementation includes:

- Constructors for initializing rational numbers from integers or fractions.
- Arithmetic operators: binary (`+`, `-`, `*`, `/`, `+=`, `-=`, `*=`, `/=`) and unary (`-`, `!` for negation and reciprocal).
- Conversion operators to `double` and `int`.
- A stream output operator for displaying rational numbers as decimals, with repeating decimals enclosed in parentheses (e.g., `2359348/99900` as `23.61(709)`).
- A custom exception hierarchy derived from `std::logic_error` for handling overflow (`przekroczenie_zakresu`) and division by zero (`dzielenie_przez_0`).

The project is modular, split into header (`wymierna.h`) and source (`wymierna.cpp`) files, with comprehensive tests in `main.cpp` to verify functionality, including copy semantics and exception handling. The project was developed as part of an object-oriented programming course, focusing on robust implementation and error handling.

## File Structure

- **wymierna.h**: Header file defining the `wymierna` class, exception hierarchy, and function declarations.
- **wymierna.cpp**: Source file containing the implementation of the `wymierna` class, including arithmetic operations, normalization, and decimal output formatting.
- **main.cpp**: Test file with functions to verify constructors, arithmetic operations, unary operations, type conversions, copy semantics, and periodic decimal representation.

## Usage

1. Compile the program using a C++11-compliant compiler (e.g., `g++ -std=c++11 wymierna.cpp main.cpp -o rational`).
2. Run the executable (`./rational` on Unix-like systems or `rational.exe` on Windows).
3. The program executes a series of tests defined in `main.cpp`, demonstrating:
   - Constructor behavior (default, integer, fraction, and division by zero).
   - Arithmetic operations (`+`, `-`, `*`, `/`, and compound assignments).
   - Unary operations (negation and reciprocal).
   - Type conversions to `double` and `int`.
   - Copy constructor and copy assignment.
   - Decimal representation with repeating parts (e.g., `23.61(709)`).
4. Output is displayed in the console, including any caught exceptions.

## Requirements

- C++11-compliant compiler (e.g., GCC, Clang, MSVC)
- Standard C++ library

## Notes

- The implementation ensures fractions are always normalized (simplified) using the Euclidean algorithm for GCD.
- Overflow checks are performed using `long long` intermediates to prevent integer overflow in arithmetic operations.
- The stream output operator handles repeating decimals by detecting periodicity in the decimal expansion.
- The test suite in `main.cpp` covers edge cases, such as division by zero and large numbers that may cause overflow.
- The code is designed for modularity and could be extended with additional features, such as comparison operators or support for other numeric types.

## License

This project is for educational purposes and does not include a specific license. Feel free to use and modify the code for learning or personal projects.
