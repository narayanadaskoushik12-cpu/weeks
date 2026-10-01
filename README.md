# ShellForge - Operating Systems & Systems Programming

ShellForge is a Unix-like shell developed as part of the Operating Systems and Systems Programming (OSSP) Project-Based Learning course.

## Progressive Learning Roadmap
- [x] **Week 1**: REPL Loop, Project Setup & Makefile
- [x] **Week 2**: Dynamic Input Buffer (`malloc` / `realloc`)
- [x] **Week 3**: Command Parser & Tokenization (`argv[]`)
- [x] **Week 4**: Process Execution (`fork()` & `execvp()`)
- [x] **Week 5**: Built-in Commands (`cd`, `help`, `exit`) & Environment Variables
- [x] **Week 6**: Signals & Process Control (`SIGINT`, `SIGTSTP`, `SIGCHLD`)
- [ ] **Final Project**: CPU Process Scheduling Simulator Integration (FCFS, SJF, RR, Priority)

---

## Features (Week 6)
- Asynchronous signal handling for `SIGINT` (Ctrl+C) and `SIGCHLD`
- Prevents shell termination on Ctrl+C signal interrupts
- Non-blocking zombie process harvesting using `waitpid(-1, NULL, WNOHANG)`
- Modular signal handling module (`include/signals.h` and `src/signals.c`)

---

## How to Build & Run

Using Linux / WSL terminal:
```bash
make clean  # Clean old binaries
make        # Compiles binary to bin/shellforge
make run    # Runs the shell
```
