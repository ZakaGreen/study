# Programming Coursework

My university exercises in **C, C++, Java and R**, collected during my Applied Informatics studies at FEI STU in Bratislava.

This is a collection of separate assignments rather than one application. The examples show my practice with programming fundamentals, data structures, object-oriented programming and statistics.

Pointers and structures in C were difficult for me to picture at first. Studying how computer memory works helped them make sense, and I eventually worked through the assignments myself. The C example below is one part of that practice. My [xv6 lab work](https://github.com/ZakaGreen/xv6-labs-2026) continues into operating-system concepts, with the coursework also kept on [GitLab](https://gitlab.com/ilushkalubotin/xv6-xliubotin-2026).

## Start here

| Example | What it covers |
| --- | --- |
| **[Army simulation in C](C_studying/Programming_2/zadanie4)** | Structures, pointers, equipment data, input validation and turn-based combat logic. |
| **[Inventory exercises in Java](Java_studying/OOP/zadanie7)** | Inheritance, interfaces, collections, exceptions, sorting and loading/saving product data. Includes assignment tests. |
| **[Programming techniques in C++](C%2B%2B_studying/PT)** | A sequence of exercises in C++ and object-oriented programming. |
| **[Mathematical statistics in R](R_studying/MatStat)** | Statistics exercises and data analysis practice. |

## Run the C example

With GCC installed, run these commands from the repository root:

```bash
cd C_studying/Programming_2/zadanie4
gcc -std=c11 -Wall -Wextra z4.c data.c -o army-simulation
./army-simulation 0
```

For a small input example, enter:

```text
1
Alice sword
1
Bob axe
```

The first number is the size of the first army, followed by its units and equipment. The second army uses the same format. `0` prints the initialized armies without running combat. Equipment names and attributes are defined in [data.c](C_studying/Programming_2/zadanie4/data.c).

This direct GCC command and the sample input were checked on Linux. The original CMake configuration expects a different directory layout, so use the command above for the files as stored here.

## Repository map

| Directory | Contents |
| --- | --- |
| [C_studying](C_studying) | C programming and computer architecture exercises. |
| [C++_studying](C%2B%2B_studying) | C++ and programming techniques. |
| [Java_studying](Java_studying) | Object-oriented programming assignments and exam practice. |
| [R_studying](R_studying) | Mathematical statistics exercises. |
| [MPPI_studying](MPPI_studying) | Additional C coursework. |
| [TZI_studying](TZI_studying) | Automata and theoretical computer science coursework. |

## Notes

- Assignments are at different stages and have their own requirements; the whole repository does not share one build or test command.
- Course-provided scaffolding, data and tests are kept alongside my solutions. Their presence does not imply that I authored every file or that every test passes.
- Original file names and Slovak/Russian comments are retained to match the coursework.

For my Python and machine learning exercises, see [AI_studying](https://github.com/ZakaGreen/AI_studying).
