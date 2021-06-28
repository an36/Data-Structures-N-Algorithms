/*
 *      MultiQueue Generator (mqg)
 *      Author: Abdullah Almarzouq      (an36@pdx.edu)
 *
 *      Description: The program below generates a specified number of queues and
 *                   populates randomly according to the number of requests.  The user can
 *                   specify the number of queues, the amount of requests and the Min & Max
 *                   values of the requests.
 *
 *      @param -q       The number of queues (default:1)
 *      @param -r       The number of requests (default:5)
 *      @param -min     The minimum value of the requests (default:0)
 *      @param -max     The maximum value of the requests (default:20)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int i, q=1, r=5, mn=0, mx=20;       // i is a loop index, q is the number of queues,
                                        //r is the number of requests, mn is the minimum value and mx is the maximum value.
    srand(time(0));                     //initialize random number to be absolutely random.

    //The for loop below checks if the user entered a number for each parameter,
    //if the user didn't then the parameter is going to be the default value.
    for( i= 0; i< argc; i++ ){
        if ((strcmp(argv[i],"-q")==0)&&i<argc-1){
            if(strspn(argv[i+1],"0123456789")>0){       //this if statements checks if theres a number after a parameter using the strspn function.
                q=atoi(argv[i+1]);                      //this line converts the number in the string to an integer.
            }
        }
        if ((strcmp(argv[i],"-r")==0)&&i<argc-1){
            if(strspn(argv[i+1],"0123456789")>0){
                r=atoi(argv[i+1]);
            }
        }
        if ((strcmp(argv[i],"-min")==0)&&i<argc-1){
            if(strspn(argv[i+1],"0123456789")>0){
                mn=atoi(argv[i+1]);
            }
        }
        if ((strcmp(argv[i],"-max")==0)&&i<argc-1){
            if(strspn(argv[i+1],"0123456789")>0){
                mx=atoi(argv[i+1]);
            }
        }
    }

    printf("Queues:%d | Requests:%d | Min. Value:%d | Max. Value:%d\n\n",q,r,mn,mx);        //prints the values of each parameter.

    if (mn>mx){
        mx=mn+1;
        printf("Error: Min is bigger than Max\nFixed: Min=%d & Max=%d\n\n",mn,mx);          //this if statement checks if the minimum value is larger the the maximum value and fixes it by making max=min+1.
    }

    int ques[q][r];         //A multi-dimensional array the holds each queue and its randomly assigned values.
    int j=0, temp=0;        //j is a loop index and temp is a temporary integer variable to be sued in loops and such.
    int Qsize[q];           //Qsize is an array that holds the size of each generated queue.

    if(q==1){               //if there's only one generated queue, then make the size of that queue = the number of requests.
        Qsize[0]=r;
    }
    else if (q>1){          //else if there are more than one queue, then assign random sizes for each queue.
        j=r;
        temp=r;
        for (i=0; i<q; i++){        //this for loop assigns random sizes to each queue.  The sum of all sizes is equal to the number of requests.
            if (i==q-1){
                Qsize[i]=temp;
            }
            j=rand()%j;
            temp=temp-j;
            if(j>=0&&i<q-1){
                Qsize[i]=j;
                j=temp;
            }
        }
    }

    for (i=0; i<q; i++){            //this for loop assigns random values, between min and max, to each queue according to the queue size that was generated randomly.
        for(j=0;j<Qsize[i];j++){
            ques[i][j]=mn+(rand()%(mx+1-mn));
        }
    }

    int sums[q];                    //This array holds the sum of all values within each queue.
    for (i=0;i<q;i++){
        sums[i]=0;
        printf("Queue[%d]: %s",i+1,(Qsize[i]>0)? "[":"Empty");      //prints the queue number, if queue is empty then print Empty.
        for (j=0; j<Qsize[i]; j++){
            printf("%d%s",ques[i][j],(j<Qsize[i]-1)? ",":"]");      //prints the values inside each queue.
            sums[i]=sums[i]+ques[i][j];                             //sums the values within each queue and stores in sums[i] accordingly.
        }
        printf("%-5s => sum: %d\n"," ",sums[i]);                    //prints the sum of each queue.
    }

    int smallest=sums[0];       //smallest is an integer to be used in the for loop below to find the smallest sum out of all the queues.
    temp=0;
    for (i=0;i<q;i++){          //this for loop finds the smallest sum value by looking up the sums of each queue.
        if (smallest>sums[i]){
            smallest=sums[i];
            temp=i;
        }
    }
    printf("\nValues in lowest sum queue:\n");
    printf("Queue[%d]: [",temp+1);              //prints the queue number that has the smallest sum value.

    if (Qsize[temp]==0){                        //if the smallest sum queue is empty then print Empty.
        printf("Empty]");
    }
    else {
        for (i=0; i<Qsize[temp]; i++){          //else, print the values within the queue that has the smallest sum.
        printf("%d%s",ques[temp][i],(i<Qsize[temp]-1)?", ":"]");
        }
    }

    return 0;
}
