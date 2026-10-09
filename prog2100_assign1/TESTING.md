# Assignment 1 - Conversion: Compile, Test & Submit

`main.cpp` is the program. `OriginalCPP.cpp` is sample input.

## Phase 1 - Compile

**Terminal:**
```bash
cd ~/Desktop/prog2100/prog2100_assign1
g++ -std=c++14 -Wall -Wextra main.cpp -o conversion
```

**Expected:** no output (no errors, no warnings). A `conversion` executable is created.

---

## Phase 2 - Convert the sample file

*Spec: reads a .cpp file, converts `<` / `>`, adds `<PRE>` / `</PRE>`, outputs an .html file.*

**Terminal:**
```bash
./conversion
```

**Program** - first prompt, then second prompt:
```
OriginalCPP.cpp
OriginalCPP.html
```

**Expected:** `Done. Wrote OriginalCPP.html`, then the Terminal prompt returns.

---

## Phase 3 - Check the output

*Spec: the browser shows the original source; "view source" shows the tag modifications.*

**Terminal:**
```bash
open OriginalCPP.html
cat OriginalCPP.html
```

**Expected in the browser:** identical to `OriginalCPP.cpp`, including `#include <iostream>`.

**Expected from `cat`** (or browser View Source, ⌥⌘U):
```
<PRE>
#include &lt;iostream&gt;
using namespace std;

int main()
{
   int x=4;
   if (x&lt;3) x++;
   cout &lt;&lt; x &lt;&lt; endl;
   return 0;
}
</PRE>
```

---

## Phase 4 - File name validation (Windows rules)

*Spec: only valid Windows file names may be processed, even on a Mac.*

**Terminal:**
```bash
./conversion
```

**Program** - first prompt, one line at a time:

| Type | Expected reply (then asks again) |
|---|---|
| `bob.txt` | `Expected a .cpp file.` |
| `CON.cpp` | `"CON" is a reserved Windows device name.` |
| `lpt1.cpp` | `"lpt1" is a reserved Windows device name.` |
| `bo?b.cpp` | `character '?' is not allowed.` |
| `bob*.cpp` | `character '*' is not allowed.` |
| `bob<x.cpp` | `character '<' is not allowed.` |

Then press **Control+C**.

---

## Phase 5 - Path validation and missing files

*Spec: ask the user again if the path is incorrect or the file is not available, e.g. `c:\bobFile.cpp`.*

**Terminal:**
```bash
./conversion
```

**Program** - first prompt, one line at a time:

| Type | Expected reply (then asks again) |
|---|---|
| `1:\bob.cpp` | `drive must be a single letter followed by a colon` |
| `c:\my\|dir\bob.cpp` | `folder "my\|dir": character '\|' is not allowed.` |
| `c:\AUX\bob.cpp` | `folder "AUX": "AUX" is a reserved Windows device name.` |
| `c:\dir.\bob.cpp` | `folder "dir.": name can't end with a space or a period.` |
| `c:\dir\\bob.cpp` | `path contains an empty folder name (doubled separator).` |
| `c:\bobFile.cpp` | `Could not open the source file. Check that it exists and try again.` |

Then type `OriginalCPP.cpp` and continue to Phase 6 (stay in the program).

---

## Phase 6 - Output (.html) validation

*Spec: validation applies to the source (.cpp) **or** target (.html) file.*

**Program** - second prompt, one line at a time:

| Type | Expected reply |
|---|---|
| `out.htm` | `Expected a .html file.` |
| `PRN.html` | `"PRN" is a reserved Windows device name.` |
| `out>.html` | `character '>' is not allowed.` |
| `nofolder/out.html` | `Could not create the output file. Check that the folder exists and try again.` |
| `out.html` | `Done. Wrote out.html` - Terminal prompt returns |

---

## Phase 7 - Harder conversion (optional)

**Terminal:**
```bash
cat > Tricky.cpp <<'EOF'
#include <vector>
template <typename T> bool lt(T a, T b) { return a < b && b >= a; }
int main() {
    std::vector<std::vector<int>> v;
    int x = 8 >> 1, y = 1 << 3;
    const char* s = "<b>not bold</b>";
    return x -> y;
}
EOF
./conversion
```

**Program:**
```
Tricky.cpp
Tricky.html
```

**Terminal:**
```bash
open Tricky.html
```

**Expected:** `"<b>not bold</b>"` appears as plain text, **not** bold - the tags were escaped.