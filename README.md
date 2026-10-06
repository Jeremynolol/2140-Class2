# Homework 2 — Calendar Toolkit
> **Tip:** This file is written in Markdown. The raw view in the VS Code
> editor will show symbols such as `#`, `|`, and `` ``` `` instead of
> formatted headings, tables, and code blocks. For the formatted view,
> press **Ctrl+Shift+V** (macOS: **Cmd+Shift+V**) to open the rendered
> preview.

---

## Overview

This program is a menu-driven calendar toolkit for dates from 1 January
1900 through 31 December 2100. It validates dates, reports the day of the
week for any date, counts the days between two dates, and runs a seeded
weekday quiz. `main()` is already written for you; your job is to
implement the ten functions it relies on. See the full
assignment handout on Canvas for the complete problem statement, calendar
rules, required output formats, example interaction, and grading
breakdown — this README only summarizes the interface, setup, and
submission steps.

## Constraints

- Do **not** modify `main()`, the `Weekday` enumeration, the `MIN_YEAR` /
  `MAX_YEAR` constants, or any of the function declarations. Your code is
  tested both through `main()` and by calling each function directly, so
  every name, parameter list, and return type must match exactly.
- You may add your own helper functions.
- Permitted headers: `<iostream>`, `<cstdlib>`, `<cassert>`, and
  `<cmath>`. No other headers (in particular, not `<iomanip>`).
- Do not use arrays, `std::vector`, `std::string`, classes/structs, or
  global variables (global `const` named constants are allowed).
- Functions must satisfy the reuse constraints stated in their TODO
  comments and in the handout.
- Enforce the preconditions marked "Enforce this with assert" using
  `assert`.
- `srand` is called only once, by the provided `main()`. None of your
  functions may call `srand`.
- All output goes to `std::cout`. Print functions must match the formats
  in the handout exactly.
- Every value-returning function must execute a `return` on every path.
- The program must compile with no errors using
  `g++ -std=c++11 main.cpp -o main`.

## Function Interface

| Function | Parameters | Returns | Behavior |
|---|---|---|---|
| `isLeapYear` | `int year` | `bool` | True exactly when `year` is a Gregorian leap year. |
| `daysInMonth` | `int month, int year` | `int` | Returns the number of days in that month of that year; asserts that the month is 1–12. |
| `isValidDate` | `int day, int month, int year` | `bool` | True exactly when the date exists and its year is within `MIN_YEAR`–`MAX_YEAR`. |
| `daysSince1900` | `int day, int month, int year` | `int` | Returns the number of days from 1 January 1900 to the date; asserts that the date is valid. |
| `dayOfWeek` | `int day, int month, int year` | `Weekday` | Returns the day of the week of the date; asserts that the date is valid. |
| `printWeekdayName` | `Weekday weekday, bool abbreviated = false` | `void` | Prints the full or three-letter weekday name with no spaces or newline. |
| `printDate` | `int day, int month, int year` | `void` | Prints the date as `YYYY-MM-DD` with no spaces or newline. |
| `daysBetween` | `int day1, int month1, int year1, int day2, int month2, int year2` | `int` | Returns the signed number of days from the first date to the second. |
| `randomInRange` | `int low, int high` | `int` | Returns a pseudorandom integer from `low` to `high`, inclusive, using `rand()`. |
| `randomDate` | `int& day, int& month, int& year, int minYear, int maxYear` | `void` | Sets the date to a pseudorandom valid date with a year from `minYear` to `maxYear`. |

The complete contract of each function — preconditions, postconditions,
output format, and constraints — is in the TODO comment above its
definition in `main.cpp`.

## Files in This Repository

| File | Purpose |
|---|---|
| `main.cpp` | Your program. Fill in the file header, then complete each TODO function below `main()`. |
| `README.md` | This file. |
| `.gitignore` | Excludes compiled binaries and IDE files from version control. |

## Compiling and Running

```
g++ -std=c++11 main.cpp -o main
./main            # macOS / Linux
.\main.exe        # Windows
```

The template compiles and runs as provided: every function is a
placeholder that returns a fixed value, so the menu works but the results
are wrong until you implement the functions. Choose option 4 to exit, or
signal end-of-file (`Ctrl+D` on macOS/Linux, `Ctrl+Z` then `Enter` on
Windows).

Compiling with warnings enabled (`g++ -std=c++11 -Wall main.cpp -o main`)
is strongly recommended; it reports problems such as a missing `return`.

## Submission Checklist

- [ ] Filled in the file header at the top of `main.cpp` (name, student ID, section).
- [ ] Did not modify `main()`, the `Weekday` enumeration, `MIN_YEAR`, `MAX_YEAR`, or any function declaration.
- [ ] Program compiles with no errors using `g++ -std=c++11 main.cpp -o main`.
- [ ] Tested every function on its own — not just through the menu — including leap years, month and year boundaries, the first and last supported dates, and invalid dates.
- [ ] Used only the permitted headers and none of the prohibited features.
- [ ] Code is commented and consistently formatted.
- [ ] Committed and pushed all changes to GitHub (not just once, right before the deadline).
- [ ] Submitted through Gradescope by selecting this repository and the correct branch.
- [ ] Submitted the Part A Concept Check answers as a PDF on Canvas.

## Academic Integrity

Write this code independently. Do not copy code from another student,
share your submission files with classmates, or use an AI tool to
generate, complete, modify, or correct any part of this program. See
the course syllabus, Section B, for the full policy. Keep this
repository private for the entire semester.
