# Scheme-like Interpreter

A lightweight Scheme-like interpreter implemented in C++. The project demonstrates how to parse and evaluate basic Scheme-style expressions using a single self-contained source file.

---

## Overview

This interpreter supports:

* Basic arithmetic expressions
* Symbols, numbers, booleans, and lists
* `define`, `if`, `cond`, and simple built-in operations
* Reading and evaluating expressions from an input file

All logic is implemented inside **`OurScheme.cpp`**.

Test input files are provided in the **`Test_data/`** folder.

---

## Project Structure

```
Scheme-like-Interpreter/
├── OurScheme.cpp       # Main interpreter implementation
└── Test_data/          # Example input files
```

---

## Build

Compile using g++:

```bash
g++ -std=c++17 -O2 -o ourscheme OurScheme.cpp
```

---

## Run

The program expects an input file named **`test1.txt`** by default.

### Option 1 — Replace the default input file

```bash
cp Test_data/input_1.txt test1.txt
./ourscheme
```

### Option 2 — Modify the source code

Change the following line in `main()`:

```cpp
ifs.open("test1.txt");
```

to a file you want to test:

```cpp
ifs.open("Test_data/input_1.txt");
```

Recompile and run.

---

## Example

```bash
# Build
g++ -std=c++17 -O2 -o ourscheme OurScheme.cpp

# Run with a test file
cp Test_data/input_1.txt test1.txt
./ourscheme
```

---

