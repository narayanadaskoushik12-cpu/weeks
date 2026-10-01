# ShellForge - Operating Systems & Systems Programming

ShellForge is a Unix-like shell developed as part of the Operating Systems and Systems Programming (OSSP) Project-Based Learning course.

## Progressive Learning Roadmap
- [x] **Week 1**: REPL Loop, Project Setup & Makefile
- [x] **Week 2**: Dynamic Input Buffer (`malloc` / `realloc`)
- [x] **Week 3**: Command Parser & Tokenization (`argv[]`)
- [x] **Week 4**: Process Execution (`fork()` & `execvp()`)
- [x] **Week 5**: Built-in Commands (`cd`, `help`, `exit`) & Environment Variables
- [x] **Week 6**: Signals & Process Control (`SIGINT`, `SIGTSTP`, `SIGCHLD`)
- [x] **Final Project**: CPU Process Scheduling Simulator Integration (FCFS, SJF, RR, Priority)

---

## Features
- Interactive REPL prompt (`myshell>`)
- Dynamic input buffer supporting arbitrary length commands (`malloc()` & `realloc()`)
- Command tokenization (`strtok()`)
- Process creation and execution (`fork()`, `execvp()`, `waitpid()`)
- Built-in commands (`cd`, `pwd`, `clear`, `help`, `env`, `exit`)
- Asynchronous signal handling (`SIGINT`, `SIGCHLD`) & zombie cleanup
- Integrated CPU Process Scheduling Simulator (`sched create`, `sched list`, `sched run <fcfs|sjf|rr|priority>`, `sched gantt`, `sched stats`)

---

## How to Build & Run

Using Linux / WSL terminal:
```bash
make clean  # Clean old binaries
make        # Compiles binary to bin/shellforge
make run    # Runs the shell
```

---

## CPU Scheduler Commands
```text
sched create <pid> <burst> <priority> <arrival>   # Create simulated process
sched list                                       # List all simulated processes
sched run fcfs                                   # Run First-Come-First-Served
sched run sjf                                    # Run Shortest Job First
sched run rr <quantum>                           # Run Round Robin
sched run priority                               # Run Priority Scheduling
sched gantt                                      # View Gantt Chart
sched stats                                      # View Waiting & Turnaround statistics
sched clear                                      # Clear process queue
```
