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

const int BUFFER_SIZE = 300;

/* Defines "structure" of shared memory */
struct region {           
    sem_t s;        //semaphore
    bool a;         //table element 1
    bool b;         //table element 2
    bool pDone;     //producer completion flag
    bool cDone;     //consumer completion flag
};

/*Producer waits for a and b to be set to false, then sets them to
true, then waits in a while loop until a or b is consumed OR if the 
consumer met its buffer limit*/
void producer(region* r){
    cout << "A: " << r->a << " | B: " << r->b << endl;
    for(int i = 0; i < BUFFER_SIZE; ++i){
        while(r->a != 1){
            if(sem_trywait(&(r->s)) == 0){
                r->a = 1;
                cout << "Incremented A: " << r->a << " -- " << i << endl;
                sem_post(&(r->s));
            } 
        }

        while(r->b != 1){
            if(sem_trywait(&(r->s)) == 0){
                r->b = 1;
                cout << "Incremented B: " << r->b <<" -- " << i <<  endl;
                sem_post(&(r->s));
            }
            
        }

        while(r->a == 1 && r->b == 1 && r->cDone == 0);


    }
    /*Producer Completion flag*/
    r->pDone = 1;

    cout<<"WAITING FOR CONSUMER"<<endl;
    while(r->cDone == 0);
    cout <<"FINISHED"<<endl;
    
    
}




int main(){
    /*initializers*/
    struct region *rptr;
    int fd;

    /* Create shared memory object and set its size */
    fd = shm_open("/myregion", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) cout << "Failed to open" << endl;

    /* Handle error */
    if (ftruncate(fd, sizeof(struct region)) == -1) cout << "Truncate failed" << endl;


    /* Map shared memory object */
    rptr = (region*)mmap(NULL, sizeof(struct region),
        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    /* Handle error */
    if (rptr == MAP_FAILED) cout << "Mapping failed" << endl;
        


    /* initialization of the semaphore */
    int ret = sem_init(&(rptr->s), 1, 1);

    /* Handle error */
    if(ret != 0) cout << "Semaphore error" << endl;

    
    /*Initializes the producer thread*/
    thread p(producer, rptr);
  
    /*Starts initialization process*/
    p.join();

    /*Unlinks and closes shared memory*/
    shm_unlink("/myregion");
    close(fd);

    cout << "Shared Memory closed" << endl;
    cout << "Producer Process closing..."<<endl;

    return 0;
    
}

