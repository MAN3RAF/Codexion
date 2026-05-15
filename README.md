*This project has been created as part of the 42 curriculum by lsebar.*

# Codexion

## Description

Codexion is a complex multi-threaded simulation inspired by the classic Dining Philosophers problem, adapted to a computing environment. The goal of this project is to model asynchronous behavior and resource sharing among threads. In this simulation, Coders (threads) must compete for limited shared resources known as Dongles (mutexes/conditions) to perform their work. They cycle through different phases: Compiling, Debugging, and Refactoring. A Coder will *"burn out"* (die) if they do not compile their code within a given timeframe.

The project demonstrates advanced threading concepts, custom schedulers (FIFO / EDF - Earliest Deadline First), state monitoring, and strict data-race prevention.

## Instructions

### Compilation

The project comes with a `Makefile`. To compile the project, simply run:

```bash
make
```

This will compile the source files and generate an executable named `codexion`. Other available mechanisms include `make clean` (to remove object files), `make fclean` (to remove objects and the executable), and `make re` (to recompile the entire project). Note that the compilation involves `-pthread` and potentially `-fsanitize=thread` flags to ensure thread safety analysis.

### Execution

The program takes exactly 8 parameters:

```bash
./codexion <num_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <num_compiles_req> <dongle_cooldown> <scheduler>
```

* **num_coders**: The number of coders (must be > 1).
* **time_to_burnout**: Time (in milliseconds) before a coder burns out if they haven't re-compiled.
* **time_to_compile**: Time (in ms) it takes to compile (requires 2 dongles).
* **time_to_debug**: Time (in ms) it takes to debug code.
* **time_to_refactor**: Time (in ms) it takes to refactor.
* **num_compiles_req**: Number of times each coder must compile to finish successfully.
* **dongle_cooldown**: Milliseconds a dongle cannot be acquired after being released.
* **scheduler**: Scheduling algorithm for dongles, either `fifo` or `edf`.

Example:

```bash
./codexion 5 800 200 200 200 5 10 fifo
```

## Resources

* **Threads documentation:** Guidelines on how to leverage pthreads for multithrading. [multithreading_in_c](https://www.geeksforgeeks.org/c/multithreading-in-c/)
* **Dining Philosophers Problem:** Fundamental computer science problem showcasing deadlocks and starvation. [Dining_philosophers_problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
* **Scheduling Algorithms:** Concepts behind FIFO and EDF (Earliest Deadline First) task schedulers. [edf_cpu_scheduling_algorithm](https://www.geeksforgeeks.org/operating-systems/earliest-deadline-first-edf-cpu-scheduling-algorithm/)
* **AI Usage:** AI was used conceptually to assist with resolving scheduling logic, brainstorming deadlock prevention (Coffman's conditions applications), and constructing parts of this README to clearly communicate the technical achievements.

## Blocking cases handled

The simulation efficiently handles several concurrency issues ensuring absolute stability:

* **Deadlock prevention (Coffman's conditions):** Handled through resource hierarchy. A Coder will always pick up their lower-indexed dongle before the higher-indexed dongle. This effectively breaks the Circular Wait condition.
* **Starvation prevention:** Implemented through custom schedulers (Earliest Deadline First or FIFO) and priority management on Dongles. The `waiting_room` structure and `min_heap` queue assure that coders do not starve indefinitely.
* **Cooldown handling:** Managed accurately using system timestamps. Coders check the last drop time of a dongle against the required `dongle_cooldown`.
* **Precise burnout detection:** Achieved using a standalone `monitor` thread that continuously parses through all active coders, verifying if current time minus `last_compile` exceeds `time_to_burnout`, minimizing the overhead on worker threads.
* **Log serialization:** Print operations are heavily guarded using a dedicated `print_lock` mutex to prevent jumbled lines or torn writes on stdout, ensuring that simulation logs are correctly ordered and uncorrupted.

## Thread synchronization mechanisms

The core of Codexion is built upon rigorous synchronization primitives to safely coordinate shared state:

* `pthread_mutex_t`: Extensively used to protect shared data points. Mutexes include `dongle_lock` (preventing simultaneous access to the same resource), `system_lock` (protecting general constants or end-states), `coder_lock` (to modify coder stats safely), and `print_lock` (for thread-safe terminal reporting).
* `pthread_cond_t`: Used for advanced thread signaling. Utilizing a `waiting_room` variable allows Coders that are waiting for a dongle to sleep instead of actively spinning (busy-waiting) and wasting CPU cycles, being awoken conditionally when a resource frees up. They are also used at the start line to synchronize the initialization so all coders fire exactly at the same `start_time_ms`.
* **Custom Event Management:** By synchronizing the mutexes with the condition variables, codexion provides race-condition immune access to memory (e.g., picking and dropping dongles synchronously, communicating death states to the monitor). Every state write operation is secured to guarantee no two threads mutate shared heap elements simultaneously.
