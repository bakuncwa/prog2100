# Assignment 2 - Courses: Live Demo Commands

`Student.h` and `Student.cpp` are the class. `main.cpp` is the driver. `demo_input.txt` is a scripted run.

Phases 2-7 are one continuous run, so stay in the program until Phase 7 says otherwise.

## Phase 1 - Compile

*Spec: the solution implements header files.*

**Terminal:**
```bash
cd ~/Desktop/prog2100/prog2100_assign2
g++ -std=c++14 -Wall -Wextra main.cpp Student.cpp -o courses
```

**Expected:** no output (no errors, no warnings). A `courses` executable is created.

---

## Phase 2 - First student

*Spec: default constructor, mutator and add. Keep asking until the student is finished, without asking for a count up front or allowing blank entries.*

**Terminal:**
```bash
./courses
```

**Expected first:** `[default constructor called on ""]`, then an empty name and `Number of courses: 0`.

**Program** - one line at a time:

| Prompt | Type | Expected reply |
|---|---|---|
| First student full name | *(press Return)* | `Error: Input cannot be empty.` |
| First student full name | `Bob Smith` | Asks for the ID |
| Student ID | `12345` | `Error: Invalid student ID format. Expected W#######.` |
| Student ID | `w0123456` | Lists the 4 schools |
| School code | `XX` | `Error: Invalid code. Select a code from the list.` |
| School code | `at` | Lists the 14 campuses |
| Campus code | `tr` | Asks for a course |
| Course name | *(press Return)* | `Error: Input cannot be empty.` |
| Course name | `PROG2100` | `[add called...]` and `[courseList resized from 0 to 1 by deep copy]` |
| Add another course? | `maybe` | `Error: Invalid response. Expected Y or N.` |
| Add another course? | `y` | Asks for a course |
| Course name | `DBAS1007` | `[courseList resized from 1 to 2 by deep copy]` |
| Add another course? | `n` | Moves to step 2 |

---

## Phase 3 - print() and <<

*Spec: both output the name and list of all courses, and both identify themselves.*

**Expected (automatic):** `[print called...]` and `[operator<< called...]`, each followed by the same details:
```
Name: Bob Smith (W0123456) - School of Applied Technology and Innovation, Truro Campus, Nova Scotia Community College
Courses (2):
  1. PROG2100
  2. DBAS1007
```

---

## Phase 4 - Copy constructor

*Spec: copy the first student's courses and write in a new name.*

**Expected first:** `[copy constructor called...]`.

**Program:**

| Prompt | Type |
|---|---|
| Second student full name | `Sue Jones` |
| Student ID | `W0234567` |
| School code | `AB` |
| Campus code | `IV` |

**Expected:** `[print called...]`, then Sue's name with Bob's 2 courses.

---

## Phase 5 - Reset and deep copy

*Spec: resetting the first student must not change the second.*

**Expected (automatic):**
- Step 4 shows `[reset called...]`, then Bob with `Number of courses: 0`.
- Step 5 shows Sue with `Number of courses: 2`, still listing both courses.

---

## Phase 6 - String constructor and assignment operator

*Spec: enter a third student, then 3rd student = 2nd student.*

**Program:**

| Prompt | Type |
|---|---|
| Third student full name | `Amy Lee` |
| Student ID | `W0345678` |
| School code | `HH` |
| Campus code | `AK` |
| Course name | `WEBD3000` |
| Add another course? | `n` |

**Expected:** `[string constructor called...]`, Amy with `WEBD3000`, `[assignment operator called...]`, then Sue's details and 2 courses.

Step 7 proves the assignment made a deep copy:

| Prompt | Type |
|---|---|
| Third student's new full name | `Amy Chen` |
| Student ID | `W0456789` |
| School code | `ST` |
| Campus code | `SW` |
| Course to add to third student only | `MATH1000` |

**Expected:** Amy Chen has 3 courses and Sue still has 2.

---

## Phase 7 - Loop back

*Spec: allow looping back to the beginning.*

**Program:**
```
y
```

**Expected:** three destructor calls (Amy Chen, Sue, Bob), then step 1 starts again.

Press **Control+C** to leave the program.

---

## Phase 8 - Exit and destructor count

*Spec: some destructor calls only show when the program exits.*

**Terminal** - runs two full passes from the script and shows the end of the run:
```bash
./courses < demo_input.txt | tail -4
```

**Expected:** the step 8 heading, the `Run again? (y/n):` prompt, then the last three destructor calls (Mia Park, Lee Roy, Kai Ng). Every call happens after the final `N`.

**Terminal** - total destructor calls:
```bash
./courses < demo_input.txt | grep -c 'destructor called'
```

**Expected:** `6` (3 students on each of 2 passes).

---

## Phase 9 - Memory leaks

*Spec: the destructor frees memory without leaks.*

**Terminal:**
```bash
leaks --atExit -- ./courses < demo_input.txt | grep 'leaks for'
```

**Expected:** a line ending in `0 leaks for 0 total leaked bytes.`

A `Process ... is not debuggable` warning may print first. That's a macOS security notice, not a failure.

---

## Phase 10 - Show the code (if asked)

**Terminal** - header guards:
```bash
grep -nE 'ifndef|define|endif' Student.h
```

**Terminal** - destructor with the not-null test and null assignment:
```bash
sed -n '/^Student::~Student/,/^}/p' Student.cpp
```

**Terminal** - the resize in add:
```bash
sed -n '/^void Student::add/,/^}/p' Student.cpp
```

**Terminal** - confirms no vector or list:
```bash
grep -nE 'vector|<list>' *.h *.cpp
```

**Expected:** no output from the last command.

---

## Phase 11 - Submit

**Terminal:**
```bash
zip prog2100_assign2_w0544360.zip Student.h Student.cpp main.cpp
```

Upload the zip, then click **Submit**.
