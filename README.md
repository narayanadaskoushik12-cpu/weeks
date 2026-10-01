# ShellForge - Operating Systems & Systems Programming

ShellForge is a Unix-like shell developed as part of the Operating Systems and Systems Programming (OSSP) Project-Based Learning course.

## Progressive Learning Roadmap
- [x] **Week 1**: REPL Loop, Project Setup & Makefile
- [x] **Week 2**: Dynamic Input Buffer (`malloc` / `realloc`)
- [x] **Week 3**: Command Parser & Tokenization (`argv[]`)
- [x] **Week 4**: Process Execution (`fork()` & `execvp()`)
- [x] **Week 5**: Built-in Commands (`cd`, `help`, `exit`) & Environment Variables
- [x] **Week 6**: Signals & Process Control (`SIGINT`, `SIGTSTP`, `SIGCHLD`)
- [x] **Week 7**: Anonymous Pipes (`pipe()`, `dup2()`, Inter-Process Communication)
- [x] **Week 8**: Memory Management, Debugging (Valgrind, GDB & AddressSanitizer)
- [x] **Final Project**: CPU Process Scheduling Simulator Integration (FCFS, SJF, RR, Priority)

---

## Week 7 Features
- Anonymous pipes using `pipe()`
- Input/Output redirection using `dup2()`
- Two-command pipeline execution (e.g. `cat sample.txt | grep hello`)
- Inter-Process Communication (IPC) using file descriptors

---

## Week 8 Features
- Memory leak detection using Valgrind
- Interactive debugging using GDB (`-g` flag)
- AddressSanitizer support (`make asan`)
- Defensive programming practices & pointer validation
- Leak-free memory management (`0 errors` in Valgrind)

---

## How to Build & Run

Using Linux / WSL terminal:
```bash
make clean  # Clean old binaries
make        # Compiles binary to bin/shellforge
make asan   # Compiles with AddressSanitizer enabled
make run    # Runs the shell
```

To run Valgrind memory leak check:
```bash
valgrind --leak-check=full ./bin/shellforge
```
