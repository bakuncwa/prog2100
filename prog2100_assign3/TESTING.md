# Assignment 3 - Rational: Live Demo Commands

## Phase 1 - Compile

*Spec: a Rational class split into a .h and a .cpp.*

**Terminal:**
```bash
cd ~/Desktop/prog2100/prog2100_assign3
g++ -std=c++14 -Wall -Wextra main.cpp Rational.cpp -o rational
```

**Expected:** no output (no errors, no warnings). A `rational` executable is created.

---

## Phase 2 - Validation and the string constructor

*Spec: the string constructor accepts "-1/3" or a whole number such as 5. Tests meant to make the program malfunction must fail safely.*

**Terminal:**
```bash
./rational
```

**Program** - one line at a time:

| Prompt | Type | Expected reply |
|---|---|---|
| First number | *(press Return)* | `Error: Input cannot be empty.` |
| First number | `1.5` | `Error: Invalid number. Expected a fraction (-1/2) or a whole number (5).` |
| First number | `abc` | Same invalid number error |
| First number | `1/2/3` | Same invalid number error |
| First number | `- 1/2` | Same invalid number error (space after the sign) |
| First number | `1/` | Same invalid number error |
| First number | `1/0` | `Error: Denominator cannot be zero.` |
| First number | `99999999999999999999` | `Error: Value out of range. Use -2147483647 to 2147483647.` |
| First number | `-2147483648` | Same out of range error |
| First number | `1/2` | Asks for the second number |
| Second number | `2/4` | Shows the results |

---

## Phase 3 - Normalization, math and logical operators

*Spec: answers are a single normalized fraction (1/2, not 2/4). <, > and == return a Boolean. The driver uses the operators on Rational objects (result = first + second, cout << result), and each one prints that it fired.*

**Expected (automatic)** for `1/2` and `2/4`:
```
=== Values as stored (normalized) ===
  1/2                           = 1/2  [operator<< fired]
  2/4                           = 1/2  [operator<< fired]

=== Arithmetic ===
  [default constructor fired]
  [operator+ fired]
  [two-argument constructor fired]
  [operator= fired]
  1/2 + 2/4                     = 1/1  [operator<< fired]
  [operator- fired]
  [two-argument constructor fired]
  [operator= fired]
  1/2 - 2/4                     = 0/1  [operator<< fired]
  [operator* fired]
  [two-argument constructor fired]
  [operator= fired]
  1/2 * 2/4                     = 1/4  [operator<< fired]
  [operator/ fired]
  [two-argument constructor fired]
  [operator= fired]
  1/2 / 2/4                     = 1/1  [operator<< fired]

=== Comparisons ===
  [operator< fired]
  1/2 < 2/4                     = false
  [operator> fired]
  1/2 > 2/4                     = false
  [operator== fired]
  1/2 == 2/4                    = true
```

---

## Phase 4 - Other constructors, = and <<

*Spec: the default constructor gives 0/1, the whole number constructor gives whole/1, and the two-argument constructor sets any legitimate value. Each constructor prints that it fired. Values print with toString() and cout << RNObj.*

**Expected (automatic):**
```
=== Other constructors and operators ===
  [default constructor fired]
  Rational()                    = 0/1  [operator<< fired]
  [whole number constructor fired]
  Rational(5)                   = 5/1  [operator<< fired]
  [two-argument constructor fired]
  Rational(4, -8)               = -1/2  [operator<< fired]
  [two-argument constructor fired]
  Rational(1, 0)                = Error: Denominator cannot be zero.
  [operator= fired]
  result = 1/2                  = 1/2  [operator<< fired]
  1/2.toString()                = 1/2
  [whole number constructor fired]
  [operator+ fired]
  [two-argument constructor fired]
  [operator= fired]
  2 + 1/2                       = 5/2  [operator<< fired]
```

Each arithmetic row shows the chain that produced it: the operator, the two-argument constructor that builds the normalized answer, `operator=` storing it in `result`, then `operator<<`. `2 + 1/2` also starts with the whole number constructor converting the `2` to `2/1`. Each typed number shows `[string constructor fired]`.

---

## Phase 5 - Loop back with negatives

*Spec: negative numbers and a negative denominator are normalized.*

**Program:**

| Prompt | Type | Expected reply |
|---|---|---|
| Calculate again? | `maybe` | `Error: Invalid response. Expected Y or N.` |
| Calculate again? | `y` | Asks for the first number |
| First number | `-3/4` | Asks for the second number |
| Second number | ` 1 / -3 ` | Shows the results |

**Expected:** `1 / -3` is stored as `-1/3`, then `-13/12`, `-5/12`, `1/4`, `9/4`, and `<` is `true`.

---

## Phase 6 - Division by zero

**Program:**

| Prompt | Type |
|---|---|
| Calculate again? | `y` |
| First number | `+6/+8` |
| Second number | `0` |

**Expected:** `+6/+8` is stored as `3/4`, `0` is stored as `0/1`, and the division row shows `Error: Division by zero.` The program keeps running.

---

## Phase 7 - Answers outside int range

**Program:**

| Prompt | Type |
|---|---|
| Calculate again? | `y` |
| First number | `2147483647` |
| Second number | `2147483647` |

**Expected:** `+` and `*` show `Error: Value out of range. Use -2147483647 to 2147483647.`, while `-` gives `0/1` and `/` gives `1/1`. `2 + 2147483647` shows the same range error.

**Program:**
```
n
```

**Expected:** the program exits.

---

## Phase 8 - Full scripted run

*Every test above plus one more round (`5` and `-10/4`), from [demo_input.txt](demo_input.txt).*

**Terminal** - the inputs, numbered:
```bash
cat -n demo_input.txt
```

**Terminal** - the whole run:
```bash
./rational < demo_input.txt
```

**Terminal** - error count:
```bash
./rational < demo_input.txt | grep -c 'Error'
```

**Expected:** `19` (9 rejected inputs, 1 bad Y/N answer, 5 `Rational(1, 0)` rows, 1 division by zero, 3 out of range answers).

---

## Phase 9 - Show the code (if asked)

**Terminal** - header guards and the two int members:
```bash
grep -nE 'ifndef|define|endif|int numerator|int denominator' Rational.h
```

**Terminal** - where every value is normalized:
```bash
sed -n '/^void Rational::set/,/^}/p' Rational.cpp
```

**Terminal** - toString() and the output operator that uses it:
```bash
sed -n '/^string Rational::toString/,/^}/p; /^ostream& operator<</,/^}/p' Rational.cpp
```

**Terminal** - every constructor and overload prints that it fired:
```bash
grep -n 'fired' Rational.cpp
```

**Terminal** - the operators used directly on Rational objects:
```bash
grep -n 'result = ' main.cpp
```
