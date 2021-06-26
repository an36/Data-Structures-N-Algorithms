/*
 *      ECE 362 | H.W.2 Part C | (tx)
 *      Author: Abdullah Almarzouq     (an36@pdx.edu)
 *
 *      Description: The program below creates two process (parent and child) by using fork().
 *                  The child process will execute the twist program and redirect the output (using pipes) to
 *                  the parent process which executes xor.  Xor takes its input from the redirected 
 *                  output by twist.
 *
 *
 *      @argument -i         the name of the input file (default: stdin)
 *      @argument -o         the name of the output file (default: stdout)
 *      @argument -b         the number of characters to be twisted (default: 10)
 *      @argument <string>   the mask which must be provided (must be less than 10 characters)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char *inp=NULL, *oup=NULL, *mask=NULL, *b;           //char inp is a variable that holds the name of the input file, and char oup hold the name of the output file.
                                                        //char mask will hold the character value of the mask for the xor program, while char b will hold the number of cahracters to twist within a block.
    int i=0;                                      // int i is a loop index.
    for(i=1;i<argc;i++){                        //this loop checks the command line entered by user.
        if((strcmp(argv[i],"-i")==0)&&i<(argc-1)){
            if((strcmp(argv[i+1],"-o")!=0)&&(strcmp(argv[i+1],"-b")!=0)){ //if the command has (-i) then this if statement checks if the preceding is a file name or just a parameter.
                inp=argv[i+1];
            }
        }
        if((strcmp(argv[i],"-o")==0)&&i<(argc-1)){
            if((strcmp(argv[i+1],"-i")!=0)&&(strcmp(argv[i+1],"-b")!=0)){   //if the command has (-o) then this statement checks if the preceding is a file name of not.
                oup=argv[i+1];
            }
        }
        if((strcmp(argv[i],"-b")==0)&&i<(argc-1)){
            if((strcmp(argv[i+1],"-o")!=0)&&(strcmp(argv[i+1],"-b")!=0)){   //if the command has (-b) then this statement check if the preceding is a number or not.
                b=(argv[i+1]);
            }
        }
        if((strcmp(argv[i],"-b")!=0)&&(strcmp(argv[i],"-i")!=0)&&(strcmp(argv[i],"-o")!=0)){        //while this if statement checks if the command line has a mask for the xor program.
          if((strcmp(argv[i-1],"-b")!=0)&&(strcmp(argv[i-1],"-i")!=0)&&(strcmp(argv[i-1],"-o")!=0)){
              mask=argv[i];
          }
        }
    }
    
    char *twArg[]={"./twist","-b",b,"-i",inp,(char*)0};            //twist program name and arguments
    char *xorArg[]={"./xor",mask,"-o",oup ,(char*)NULL};            //xor prgoram name and arguments
    int Pipe[2];                                                    //int Pipe[2] will be the pipe to redirect the output the chile process to the parent process as an input
    pipe(Pipe);                                                     //creating a pipe.

    int rc = fork();                                                //fork() creates two processes. Parent: xor and child: twist
    
    if(rc<0){                                                        //if fork fails then print error and exit
      fprintf(stderr,"Error: fork() failed: %s\n",strerror(errno));
      exit(-1);
    }
    
    if (rc==0){                                                  //if the value of rc=0 (child process) then this will execute twist
      close(1);                                                  //closing STDOUT
      dup(Pipe[1]);                                              //duplicating Pipe[1] to replace STDOUT
      close(Pipe[0]);                                            //closing pipes
      close(Pipe[1]);
      execvp(twArg[0],twArg);                                    //executes twist and redirect output to parent process (xor)
      }
    else{                                                        //else executes the xor program
      close(0);                                                  //closing STDIN
      dup(Pipe[0]);                                              //duplicating Pipe[0] to replace STDIN
      close(Pipe[0]);                                            //closing pipes
      close(Pipe[1]);
      wait(NULL);                                                //wait for the child process to execute and finish then begin the parent process
      execvp(xorArg[0],xorArg);                                  //executes xor where the input of xor is taken from the output of twist
    }
    
    close(Pipe[0]);                                              //closing pipes.
    close(Pipe[1]);
    
    
    return 0;
    }
