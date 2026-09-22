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
| Assignment 1 | [prog2100_assign1/OriginalCPP.cpp](prog2100_assign1/OriginalCPP.cpp) | Original source file to be converted |
| Assignment 1 | [prog2100_assign1/main.cpp](prog2100_assign1/main.cpp) | C++ to HTML file converter |
| Assignment 1 | [prog2100_assign1/main_alt.cpp](prog2100_assign1/main_alt.cpp) | Alternate implementation (regex + filesystem) |
| Data Structures | [prog2100_datastruct/main.cpp](prog2100_datastruct/main.cpp) | Linked list (NumberList) demo |

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