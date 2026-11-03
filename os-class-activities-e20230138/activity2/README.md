# Class Activity 2 — Processes & Inter-Process Communication

- **Student Name:** TEAV ENCHENG
- **Student ID:** e20230138
- **Date:** 03/11/2026

---

## Task 1: Process Creation on Linux (fork + exec)

### Compilation & Execution

Screenshot of compiling and running `forkchild.c`:

![Task 1 - Compile & Run](screenshots/task1_compile_run.png)

### Process Tree

Screenshot of the parent-child process tree (using `ps --forest`, `pstree`, or `htop` tree view):

![Task 1 - Process Tree](screenshots/task1_process_tree.png)

### Output

```
[Paste the content of result_forkchild.txt here]
```

### Questions

1. **What does `fork()` return to the parent? What does it return to the child?**

   > fork() returns the child process ID (PID) to the parent, and 0 to the child process. It returns -1 if process creation fails.

2. **What happens if you remove the `waitpid()` call? Why might the output look different?**

   > The parent process might finish and exit before the child completes, turning the child into an orphan adopted by init/systemd. Consequently, terminal prompts may interleave with the child process output.

3. **What does `execlp()` do? Why don't we see "execlp failed" when it succeeds?**

   > execlp() replaces the current process memory space with a new executable program. When it succeeds, the entire original code is overwritten, so execution never reaches the error-handling lines following execlp().

4. **Draw the process tree for your program (parent → child). Include PIDs from your output.**

   > [Your answer / diagram]

5. **Which command did you use to view the process tree (`ps --forest`, `pstree`, or `htop`)? What information does each column show?**

   > Used ps --forest. Columns typically indicate USER (process owner), PID (process ID), PPID (parent PID), %CPU (processor usage), %MEM (memory usage), TTY (terminal type), STAT (process state), and COMMAND (command line string).

---

## Task 2: Process Creation on Windows

### Compilation & Execution

Screenshot of compiling and running `winprocess.c`:

![Task 2 - Compile & Run](screenshots/task2_compile_run.png)

### Task Manager Screenshots

Screenshot showing process tree in the **Processes** tab (mspaint nested under your program):

![Task 2 - Task Manager Tree](screenshots/task2_taskmanager_tree.png)

Screenshot showing PID and Parent PID in the **Details** tab:

![Task 2 - Task Manager Details](screenshots/task2_taskmanager_details.png)

### Questions

1. **What is the key difference between how Linux creates a process (`fork` + `exec`) and how Windows does it (`CreateProcess`)?**

   > Linux creates a process by duplicating the parent process address space via fork() and then replacing it with a new executable using exec(). Windows initializes a new process directly from an executable file in a single step using CreateProcess().

2. **What does `WaitForSingleObject()` do? What is its Linux equivalent?**

   > It pauses the execution of the calling thread until the specified object (e.g., child process handle) enters a signaled state (terminates). Its Linux equivalent is wait() or waitpid().

3. **Why do we need to call `CloseHandle()` at the end? What happens if we don't?**

   > It releases kernel handle references to prevent system resource leaks. If omitted, system memory and object handles remain allocated until the parent process terminates.

4. **In Task Manager, what was the PID of your parent program and the PID of mspaint? Do they match your program's output?**

   > Parent PID: 1344324, mspaint PID: 1344325. Yes, both match the handle and ID output printed by the program console.

5. **Compare the Processes tab (tree view) and the Details tab (PID/PPID columns). Which view makes it easier to understand the parent-child relationship? Why?**

   > The Processes tab (tree view) is easier to read because it visually nests child processes beneath parent processes using an indented hierarchical tree structure.
   
---

## Task 3: Shared Memory IPC

### Compilation & Execution

Screenshot of compiling and running `shm-producer` and `shm-consumer`:

![Task 3 - Compile & Run](screenshots/task3_compile_run.png)

### Output

```
[Paste the content of result-shm-ipc.txt here]
```

### Questions

1. **What does `shm_open()` do? How is it different from `open()`?**

   > shm_open() creates or opens a POSIX shared memory object. Unlike standard open(), which creates/opens files on persistent disk storage, shm_open() manages memory objects residing entirely in volatile memory (RAM).

2. **What does `mmap()` do? Why is shared memory faster than other IPC methods?**

   > mmap() maps shared memory objects into the process's virtual address space. Shared memory is faster than other IPC techniques because data transfers occur directly in shared RAM without requiring kernel system call overhead or redundant buffer copies.

3. **Why must the shared memory name match between producer and consumer?**

   > The shared memory name acts as a unique global identifier within the OS kernel namespace, ensuring both independent processes access the exact same segment of physical memory.

4. **What does `shm_unlink()` do? What would happen if the consumer didn't call it?**

   > shm_unlink() removes the shared memory name from the system. If omitted, the memory object persists in system RAM until the system reboots or all references close.

5. **If the consumer runs before the producer, what happens? Try it and describe the error.**

   > [Your answer]

---

## Task 4: Message Queue IPC

### Compilation & Execution

Screenshot of compiling and running `sender` and `receiver`:

![Task 4 - Compile & Run](screenshots/task4_compile_run.png)

### Output

```
[Paste the content of result-mq-ipc.txt here]
```

### Questions

1. **How is a message queue different from shared memory? When would you use one over the other?**

   > Message queues exchange structured messages managed by the kernel with implicit synchronization. Shared memory provides raw memory spaces requiring explicit synchronization (e.g., semaphores). Use message queues for discrete task messaging and shared memory for high-performance bulk data streaming.

2. **Why does the queue name in `common.h` need to start with `/`?**

   > POSIX standards require shared memory and message queue object names to start with a forward slash (/) for valid system-wide namespace identification.

3. **What does `mq_unlink()` do? What happens if neither the sender nor receiver calls it?**

   > mq_unlink() destroys the message queue name and schedules it for deletion. If neither process calls it, the queue persists in kernel memory after execution ends.

4. **What happens if you run the receiver before the sender?**

   > By default, the receiver blocks (waits) until the sender pushes a message into the queue (unless initialized with O_NONBLOCK).

5. **Can multiple senders send to the same queue? Can multiple receivers read from the same queue?**

   > Yes, POSIX message queues support multiple concurrent senders and receivers, delivering messages atomically based on arrival order and priority.
---

## Reflection

What did you learn from this activity? What was the most interesting difference between Linux and Windows process creation? Which IPC method do you prefer and why?

> Through this activity, I gained practical knowledge on operating system process creation mechanisms and inter-process communication (IPC). The key contrast between operating systems lies in process spawning: Linux utilizes a two-step fork() + exec() mechanism leveraging copy-on-write, while Windows uses a single unified CreateProcess() API call. Regarding IPC, shared memory offers maximum efficiency for large data transfers, whereas message queues provide a structured and synchronized interface for discrete message passing.