# ShellForge - Operating Systems & Systems Programming

ShellForge is a Unix-like shell developed as part of the Operating Systems and Systems Programming (OSSP) Project-Based Learning course.

## Progressive Learning Roadmap
- [x] **Week 1**: REPL Loop, Project Setup & Makefile
- [x] **Week 2**: Dynamic Input Buffer (`malloc` / `realloc`)
- [x] **Week 3**: Command Parser & Tokenization (`argv[]`)
- [x] **Week 4**: Process Execution (`fork()` & `execvp()`)
- [ ] **Week 5**: Built-in Commands (`cd`, `help`, `exit`) & Environment Variables
- [ ] **Week 6**: Signals & Process Control (`SIGINT`, `SIGTSTP`)
- [ ] **Final Project**: CPU Process Scheduling Simulator Integration (FCFS, SJF, RR, Priority)

---

## Features (Week 4)
- Process creation using `fork()`
- External program execution using `execvp()`
- Parent-child process synchronization using `waitpid()`
- Error handling using `perror()`
- Modular process management module (`include/process.h` and `src/process.c`)

---

## How to Build & Run

Using Linux / WSL terminal:
```bash
make clean  # Clean old binaries
make        # Compiles binary to bin/shellforge
make run    # Runs the shell
```
