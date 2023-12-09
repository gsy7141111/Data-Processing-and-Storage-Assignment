# Data-Processing-and-Storage-Assignment

This project implements a simple in-memory key-value store with support for transactions. The database allows you to start a transaction, make changes to the data, and either commit these changes to the main state or roll them back.

## How to Run

To compile and run this program, you will need a C++17 compatible compiler. The following steps should guide you through the process:

1. Compile the program with C++17 support:

   ```shell
   g++ -std=c++17 -o Main main.cpp
   ```

2. Run the executable:

   ```shell
   ./Main
   ```

On Windows: .\Main.exe ((ensure you have MinGW or a similar gcc compiler installed).

Ensure that you have `g++` installed on your system. On Unix-based systems, you can typically install it using your package manager (for example, `apt` on Ubuntu or `brew` on macOS).

## Future Assignment Improvements

For future iterations of this assignment, it would be beneficial to:

1. Clarify the expected behavior in edge cases, such as attempts to read, update, or delete keys within and outside of transactions.
2. Include a test suite with a comprehensive set of automated tests to facilitate grading and ensure that all edge cases are covered.
3. Provide a standardized way for handling null or nonexistent keys, possibly incorporating modern C++ features like `std::optional` if C++17 or later standards can be used.