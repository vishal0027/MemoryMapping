# MemoryMapping

Write two small pieces of code that run as different processes, yet they share part of
their memory. The memory is shared by mapping it to the same file. Create a file 100
bytes in size which is big enough for this purpose. You can use dd if=/dev/zero
of=sharedfile count=10 bs=10 to create the file.
The one process, we call sender opens the file and memory maps it (use
mmap(2)) to an array. Then modifies it by reading user input and copying the user input
to the mapped array. After every modification it sends (with kill(2)) a SIGUSR signal
to the other process. Repeats the cycle of reading, copying and sending a signal until the
mapped array is full and then exits after sending a kill signal SIGTERM to terminate the
other processes. The program takes one argument, the pid of the other process.
The other process which we call receiver, prints out its pid to be used in the
command line of the other process, maps the same file and then sets up a signal handler
(use sigaction(2)) after which it blocks with sigsuspend until it receives the signal
SIGUSR. All the new characters that were added to the mapped array are printed to
the standard output. Make sure that SIGUSR is blocked going into sigsuspend and
unblocks in sigsuspend. The process catches the SIGTERM signal and exits gracefully.
Submit one tar file that includes as first target all that compiles both programs and
creates the shared file, appropriate targets to compile the components of the assignment, a
target clean to clean up, and a target tar to create the tar file.
To start, have a look into the manual pages of mmap(2), stat(2), open(2) and
signal(7)
