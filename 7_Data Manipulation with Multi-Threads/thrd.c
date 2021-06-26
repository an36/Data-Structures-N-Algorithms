/*
*   ECE362 | H.W.5 | Problem.1) Creating 4 threads.
*   Author: Abdullah Almarzouq      (an36@pdx.edu)
*
*   Description:  The program below creates four threads and each threads created
*                 uses the function 'thread_id' to print its own id.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_id( void* tid ){                   //This function is used by each thread in 'pthread_create' to print their own thread id.
   printf("Thread ID: %ld\n", (long int) tid);  // Prints the thread id.
   return tid;                                  // "unused" return statement to avoid errors.
}

int main()
{
    pthread_t tid[4];           //variable tid[4] is an array, of type pthread_t, that holds the thread IDs.

    for (int i=0; i<4; i++){    // a for loop that creates four threads.
    tid[i]= pthread_self();     // assigns thread id to tid.
    pthread_create(&tid[i], NULL, &thread_id, &tid[i]); //this instruction creates a thread using the thread id array tid and the function thread_id.
    pthread_join(tid[i],NULL);  //Waits for the earlier thread to finish executing.
    }

    exit(0);            //terminates the threads.

    return 0;
}
