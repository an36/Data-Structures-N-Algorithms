/*
*   ECE362 | H.W.5 | Problem.2) Multi-threading.
*   Author: Abdullah Almarzouq      (an36@pdx.edu)
*
*   Description:  The program below creates a number of threads, specified by user,
*                 and each threads created uses the function 'thread_id' to print its own id
*                 and the subtotal of the summation process that the thread has computed.
*                 The array of values 'ary[64000]' has randomly generated values with a seed
*                 that should be specified by the user.  This array's values are used to for the summation
*                 process while each. The values inside that array are divided upon the created threads
*                 so that each thread can compute the subtotal of those values, then the Total is 
*                 computed by adding those subtotals.
*
*  @param -t      the number of threads (1, 2, 4 or 8)
*  @param -s      the value of the seed to be used in srand
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//Global variables
int ary[64000];    //the array of randomly generated values to be used in the summation process.
int strt=0;        //Array index to be used in summation loop function when calling pthread_create().
int end;           //this integer will be used to determine when to stop the summation process for each thread.
long long int Total=0;       //This integer holds the total sum of subtotals computed by each thread.

void* thread_id( void* tid ){                   //This function is used by each thread in 'pthread_create' to print their own thread id.
    long long int sum=0;                        //this variable will hold the subtotal of the sum computed by each thread.
   printf("Thread ID: %ld\n", (long int) tid);  // Prints the thread id.
   
   for(strt=strt;strt<end;strt++){              //for loop that computes the subtotal.
     sum=ary[strt]+sum;
   }
   printf("Thread subtotal: %lld\n\n",sum);     //prints subtotal.
   Total=Total+sum;                             //add subtotal to the total sum.
   pthread_exit(0);                              //terminates thread.
}

int main(int argc, char *argv[])
{
    int tnum,seed;          //tnum is the number of threads and seed is the seed value to be used in srand()
    int *t=NULL, *s=NULL;    // pointers *s & *t points to the number of threads and the value of the seed respectively.
    int i;                       // i is a loop index.
    
    if(argc<=2){
      fprintf(stderr,"\nError: No parameters/values have been found\n");    //if there are no parameters then print error and exit.
      exit(0);
    }
    
    for(i=1;i<argc;i++){
      if((strcmp(argv[i],"-t")==0)&&(i<(argc-1))){      //if there's parameter -t then take the value next to it as the number of threads to be created.
        tnum=atoi(argv[i+1]);
        t=malloc(sizeof(int));
        *t=tnum;
      }
      if((strcmp(argv[i],"-s")==0)&&(i<(argc-1))){      //if there's parameter -s then take the value next to it as the value of the seed.
        seed=atoi(argv[i+1]);
        s=malloc(sizeof(int));
        *s=seed;
      }
    }
    
    if(t==NULL){
      fprintf(stderr,"\nError: Couldn't find the desired number of thread\n");    //if the number of threads wasn't found then print error and exit.
      free(s); free(t);
      exit(0);
    }
    else if(s==NULL){
      fprintf(stderr,"\nError: Couldn't find the desired seed value\n");    //if the seed value wasn't found then print error and exit.
      free(s); free(t);
      exit(0);
    }
    else if(((tnum%2!=0)&&tnum>1)||tnum>8||tnum==6||tnum<1){        //if the number of threads is not 1,2,4 or 8 then print error and exit.
      fprintf(stderr,"\nError: Number of thread should either 1, 2, 4 or 8\n");
      free(s); free(t);
      exit(0);
    }
    
    srand(seed);        //generate srand() with the seed value.
    
    long long int sum=0;    //This integer holds the expected total sum.
    
    for(i=0;i<64000;i++){    //for loop that populates the array ary[] with random values.
      ary[i]=rand();
    }
    for(i=0;i<64000;i++){    //for loop that computes the expected sum.
      sum=sum+ary[i];
    }
    
    printf("\nExpected results: %lld\n\n",sum);    //prints expected total sum.
    
    pthread_t tid[tnum];           //variable tid[4] is an array, of type pthread_t, that holds the thread IDs.
    
    end=64000/tnum;              //divides the number of values by the number of threads and assign it to 'end' to be used by the first thread to compute the first subtotal.

    for (i=0; i<tnum; i++){    // a for loop that creates four threads.
    tid[i]= pthread_self();     // assigns thread id to tid.
    pthread_create(&tid[i], NULL, &thread_id, &tid[i]); //this instruction creates a thread using the thread id array tid and the function thread_id.
    pthread_join(tid[i],NULL);  //Waits for the earlier thread to finish executing.
    end=end+(64000/tnum);      //increments 'end' to compute the sum of the next x values assigned to the next thread.
    }
    printf("\nThreads Total: %lld\n",Total);    //prints the threads total sum.
    
    if(sum==Total){        //if the Total=expected sum then print success.
      printf("\nSuccess\n");
    }
    else{                  //else print error and exit.
      fprintf(stderr,"\nError: Thread summation failed\n");
    }
    
    free(s);            //frees pointer
    free(t);            //frees pointer
    
    exit(0);            //terminates the threads.
    
    return 0;
}
