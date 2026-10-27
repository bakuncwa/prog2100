# PROG2100 - Programming C++ Lab Repository

**Course:** PROG2100 - Programming C++ 700
**Instructor:** David Russell, Nova Scotia Community College

## Repository Index

I. [Google Docs Compilation](https://docs.google.com/document/d/16ri7GDgUtfdCiVKpOHqgr6GGHGwZNShl-bMN5w0YCcs/edit?usp=sharing)

II. [NotebookLM](https://notebook.google.com/notebook/bca85061-a2f6-47d6-8f1b-7a0f44ef7f18)

## Weekly Files

| Week | File | Description |
|------|------|--------------|
| Week 1 | [prog2100_wk1/io.cpp](prog2100_wk1/io.cpp) | I/O basics |
| Week 2 | [prog2100_wk2/concepts.cpp](prog2100_wk2/concepts.cpp) | Core C++ concepts |
| Week 2 | [prog2100_wk2/valid.cpp](prog2100_wk2/valid.cpp) | Input validation (name, age, regex) |
| Week 2 | [prog2100_wk2/regex_cadpostal.cpp](prog2100_wk2/regex_cadpostal.cpp) | Canadian postal code validation using regex |
| Week 3 | [prog2100_w3/main.cpp](prog2100_w3/main.cpp) | Pointer basics |
| Week 3 | [prog2100_w3/poem.cpp](prog2100_w3/poem.cpp) | Pointer basics (poem example) |
| Week 4 | [prog2100_wk4/exceptions.cpp](prog2100_wk4/exceptions.cpp) | Exceptions demo (standard, divide by zero, programmer-defined) |
| Week 4 | [prog2100_wk4/exceptions_lab.cpp](prog2100_wk4/exceptions_lab.cpp) | Practice Exceptions Lab (struct exceptions, catch order, rethrow) |
| Assignment 1 | [prog2100_assign1/OriginalCPP.cpp](prog2100_assign1/OriginalCPP.cpp) | Original source file to be converted |
| Assignment 1 | [prog2100_assign1/main.cpp](prog2100_assign1/main.cpp) | C++ to HTML file converter (regex path validation) |
| Assignment 1 | [prog2100_assign1/TESTING.md](prog2100_assign1/TESTING.md) | Compile, test and zip steps |
| Data Structures | [prog2100_datastruct/main.cpp](prog2100_datastruct/main.cpp) | Linked list (NumberList) demo |
| Week 7 | [prog2100_wk7/unit1_charlie_cat.cpp](prog2100_wk7/unit1_charlie_cat.cpp) | M2 U1 - Intro to classes (stack vs heap objects) |
| Week 7 | [prog2100_wk7/unit1_knight_vs_dragon.cpp](prog2100_wk7/unit1_knight_vs_dragon.cpp) | M2 U1 - Knight vs Dragon (aggregate classes) *Windows only (conio.h)* |
| Week 7 | [prog2100_wk7/unit2_complex_number.cpp](prog2100_wk7/unit2_complex_number.cpp) | M2 U2 - Operator overloading and friend functions |
| Week 7 | [prog2100_wk7/unit2_myownmath/](prog2100_wk7/unit2_myownmath/) | M2 U2 - Header/implementation split *Windows only (conio.h)* |
| Week 7 | [prog2100_wk7/unit2_gcd.cpp](prog2100_wk7/unit2_gcd.cpp) | M2 U2 - Greatest common divisor sample |
| Week 7 | [prog2100_wk7/unit3_string_rule_of_three.cpp](prog2100_wk7/unit3_string_rule_of_three.cpp) | M2 U3 - Custom String class (rule of three) |
| Week 7 | [prog2100_wk7/unit3_string_rule_of_five.cpp](prog2100_wk7/unit3_string_rule_of_five.cpp) | M2 U3 - Custom string class (rule of five) *MSVC only (strncpy_s)* |
| Week 7 | [prog2100_wk7/unit3_pfarray.cpp](prog2100_wk7/unit3_pfarray.cpp) | M2 U3 - Partially filled array (copy constructor, assignment) |
| Week 7 | [prog2100_wk7/unit3_string_tokenizing.cpp](prog2100_wk7/unit3_string_tokenizing.cpp) | M2 U3 - String tokenizing *Windows only (conio.h)* |
| Week 8 | [prog2100_wk8/unit4_polyvehicles/](prog2100_wk8/unit4_polyvehicles/) | M2 U4 - Inheritance and polymorphism (Vehicle, Boat, Bicycle) *Windows only (conio.h)* |
| Week 8 | [prog2100_wk8/unit5_color.cpp](prog2100_wk8/unit5_color.cpp) | M2 U5 - Console colour *Windows only (windows.h)* |
| Week 8 | [prog2100_wk8/unit5_shuffle_vector.cpp](prog2100_wk8/unit5_shuffle_vector.cpp) | M2 U5 - Shuffle a vector |
| Week 8 | [prog2100_wk8/unit5_timer.cpp](prog2100_wk8/unit5_timer.cpp) | M2 U5 - Timers (endless tick loop, Ctrl+C to stop) |

## Compiling on macOS

### 1. Install the command line tools (first time only)

macOS ships with `clang` via the Xcode Command Line Tools, which also provides a `g++` alias. If you don't have them yet:

```bash
xcode-select --install
```

### 2. Compile a source file

```bash
g++ -std=c++17 -Wall <filename>.cpp -o <output_name>
```

Example:

```bash
cd prog2100_wk2
g++ -std=c++17 -Wall regex_cadpostal.cpp -o regex_cadpostal
```

### 3. Run the compiled program

```bash
./regex_cadpostal
```