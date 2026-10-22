Stident Name: TEAV Encheng
Student ID: e20230138
Ubuntu username on the server: gic-teav-encheng
My values (oslab values lab1): file1 = bridge , file2 = lemon , count = 2
# Task1: Operating System Identification
Which number is the Kernel Version?
7.0.0 (or full release string 7.0.0-38-generic) is the Linux kernel version.

Which number is the Distribution Version?
The specific Ubuntu distribution version (e.g., Ubuntu 24.04 LTS, 26.04 LTS) is not explicitly listed in this output.

The numbers present in the command output refer to:

38 in #38-Ubuntu: The distribution-specific build/compilation revision of this kernel package.

7.0.0: The upstream Linux kernel release version.
# Task2: Essential Linux File and Directory Commands
File Operations Summary
Creation: Initial text files (bridge.txt and lemon.txt) were created and populated with text content using commands like echo or cat.

Copying: A duplicate file (bridge_copy.txt) was generated from bridge.txt using the cp command.

Renaming: The file lemon.txt was renamed to lemon_renamed.txt using the mv command.

Deleting: The copied file (bridge_copy.txt) was removed using the rm command.

What the Last ls Showed
The final ls command displayed the remaining files in the directory after the deletion step:

bridge.txt

lemon_renamed.txt
# Task3: Package Management Using APT
Detailed Observation Breakdown1. 
After Running sudo apt-get remove mcWhat happened: APT uninstalled the mc executable binary from /usr/bin/mc.   Configuration State: The system configuration directory /etc/mc was left untouched.   Why this is useful: If you reinstall mc later, your previous system settings and configuration options will still be preserved.2. 
After Running sudo apt-get purge mcWhat happened: APT printed Purging configuration files for mc and wiped out all remaining configuration files associated with the package.   Configuration State: Running ls -ld /etc/mc returned:ls: cannot access '/etc/mc': No such file or directory.   Why this is useful: It completely removes all traces of the package and its system configurations, leaving a clean slate.
# Task4: Programs vs Processes
1. Running and Finding a Background ProcessRunning: 
You started a background process by appending an ampersand (&) to the command:sleep 30 & (which assigned job ID [1] and PID 49597).   Finding: You captured the active processes using the ps command redirected into task4_process_list.txt, and inspecting it with cat revealed the sleep process running under PID 49597.   
2. Difference Between a Program and a ProcessProgram: A passive, static set of instructions stored on disk as a file (e.g., the binary executable file /usr/bin/sleep).Process: An active, dynamic instance of a program currently in execution by the operating system, possessing its own Process ID (PID), memory space, allocated resources, and execution state.
3. What You Saw Before, During, and AfterBefore / At Launch:
When you typed sleep 30 &, the shell immediately spawned the task in the background and returned control back to you, displaying the job control notification with its Process ID:Plaintext[1] 49597 ```
During Execution:
Running the ps command while the timer was still counting down showed the active sleep process actively listed in the process table alongside bash and ps:   Plaintext49597 pts/0    00:00:00 sleep```
After Completion:
Once the 30 seconds elapsed, running ps again automatically notified you that the background job had finished execution before clearing it out:Plaintext[1]+  Done                    sleep 30 ```
# Task5: Multitasking
1. Description of the MultitaskingYou launched three separate background tasks concurrently (sleep 300 & repeated three times). This allowed multiple independent instances of the sleep command to run at the same time without blocking your interactive shell session.   
2. Number of sleep Lines Shown by psThe ps command displayed 3 distinct sleep lines, corresponding to the three active background jobs (PIDs 49668, 49678, and 49688).   
3. What This Shows About the SystemIt demonstrates that your Linux OS is a multitasking operating system capable of managing multiple concurrent processes simultaneously within the process table.It shows that individual processes can run independently in the background while the shell (bash) remains responsive for other commands.   
4. What This Does Not Show About Processor SharingCPU Scheduling and Time-Slicing: It does not show how the kernel's scheduler allocates CPU core time slices, handles context switches, or whether these processes are running on separate hardware cores versus sharing a single core.CPU Activity / Load: Because all three processes are currently sleeping (idle), the TIME column shows 00:00:00. It does not reveal active CPU utilization or how processor cycles are dynamically distributed when processes are actively computing.
# Task6: Virtualization and Hypervisor Detection
This is confirmed by the two virtualization checks:systemd-detect-virt returned kvm.   lscpu | grep -i "hypervisor vendor" explicitly reported Hypervisor vendor: KVM.