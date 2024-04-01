# OS-Producer-Consumer-Project-1
 C++ Multi-Process/Multi-Thread Producer Consumer Solution using semaphores and shared memory for Linux

# Producer-Consumer Problem
 The producer generates items and puts items onto the table. The consumer will pick up items. 
The table can only hold two items at the same time. When the table is complete, the producer 
will wait. When there are no items, the consumer will wait. We use semaphores to synchronize 
producer and consumer. Mutual exclusion should be considered. We use threads in the 
producer program and consumer program. Shared memory is used for the “table”.

# Solution Methodology
 Create a region of shared memory that holds a semaphore, 2 table locations, and completion flags for the producer and consumer. The producer creates the shared memory location using shm_open() and initializes the semaphore, the consumer opens the shared memory location. Both processes start new threads to run their respective processes using .join() and run until the buffer size is reached. The producer checks through the table and if either location contains a 0, changes the value to 1 for that location. If both locations hold a 0, the producer waits in a while loop. The consumer checks both locations and if either location contains a 1, changes it to 0. If both locations are empty, the consumer waits in a while loop. Once both processes have finished, the producer unlinks and closes the shared memory.

# Instruction and Use
 -Compile with -pthread and -lrt
 -Built to run the producer and consumer concurrently
