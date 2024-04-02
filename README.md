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
 Compile with g++, -pthread, -lrt and -std=c++11. Built to run the producer and consumer concurrently in linux using '&'

# Output Example
 [1] 659266                     --Thread 1 starting<br />
 [2] 659267                     --Thread 2 starting<br />
 A: 0 | B: 0                    --Table Content Initial vales <br />
 Produced A: 1 -- 0             --Producer producing value in table location A on iteration 0 <br />
 Produced B: 1 -- 0<br />
 Consumed A: 0 -- 0             --Consumer consuming value in table location A on iteration 0<br />
 Produced A: 1 -- 1<br />
 Consumed B: 0 -- 0<br />
 Produced B: 1 -- 2<br />
 Consumed A: 0 -- 1<br />
 Consumed B: 0 -- 1<br />
 Produced A: 1 -- 3<br />
 ...<br />
 ...<br />
 ...<br />
 Consumed B: 0 -- 294<br />
 Produced A: 1 -- 297<br />
 Produced B: 1 -- 297<br />
 Consumed A: 0 -- 295<br />
 Consumed B: 0 -- 295<br />
 Produced A: 1 -- 298<br />
 Produced B: 1 -- 298<br />
 Consumed A: 0 -- 296<br />
 Consumed B: 0 -- 296<br />
 Produced A: 1 -- 299<br />
 Produced B: 1 -- 299<br />
 WAITING FOR CONSUMER           --Producer met its iteration size and is waiting for consumer to finish<br />
 Consumed A: 0 -- 297<br />
 Consumed B: 0 -- 297<br />
 FINISHED                       --Consumer met its iteration size or can no longer consume because producer has finished<br />
 Shared Memory closed<br />
 Producer Process closing...    --Producer file closing<br />
 Consumer Process closing...    --Consumer file closing<br />

 [1]-  Done                    ./producer<br />
 [2]+  Done                    ./consumer<br />
