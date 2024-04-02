/*
-Isaac Hraga
-04/01/2024
-Operating Systems
-Project 1/Producer-Consumer Problem
*/
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#include <thread>

using namespace std;


const int ITERATIONS = 300;

/* Defines "structure" of shared memory */
struct region {        
    sem_t s;
    bool a;
    bool b;
    bool pDone;
    bool cDone;
};

/*Consumer waits for a and b to be set to true, then sets them to
false, then waits in a while loop until a or b is produced OR if the 
producer met its buffer limit*/
void consumer(region* r){
    /*offsets the consumer to give the producer time to produce values for
    the table*/
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    for(int i = 0; i < ITERATIONS; ++i){
        while(r->a != 0){
            if(sem_trywait(&(r->s)) == 0){
                r->a = 0;
                cout << "Consumed A: " << r->a <<" -- " << i <<  endl;
                sem_post(&(r->s));
            }
        }

        while(r->b != 0){
            if(sem_trywait(&(r->s)) == 0){
                r->b = 0;
                cout << "Consumed B: " << r->b <<" -- " << i <<  endl;
                sem_post(&(r->s));
            } 
        }

        while(r->a == 0 && r->b == 0 && r->pDone==0);
    } 

    /*Consumer Completion flag*/
    r->cDone = 1;
    
    
}



int main(){
    /*initializers*/
    struct region *rptr;
    int fd;


    /* Create shared memory object and set its size */
    fd = shm_open("/myregion", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    
    /* Handle error */
    if (fd == -1) cout << "Failed to open" << endl;

    /* Handle error */
    if (ftruncate(fd, sizeof(struct region)) == -1) cout << "Truncate failed" << endl;
        
        


    /* Map shared memory object */
    rptr = (region*)mmap(NULL, sizeof(struct region),
        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    /* Handle error */
    if (rptr == MAP_FAILED) cout << "Mapping failed" << endl;

        


   

    /*Initializes the consumer thread*/
    thread c(consumer, rptr);

    /*starts the consumer process*/
    c.join();

    

    cout << "Consumer Process closing..." <<endl;

    return 0;
    
}

