/*
 *      twist.c 
 *
 *      Author: Abdullah Almarzouq     (an36@pdx.edu)
 *
 *      Description: The program below takes an input from an input file (or stdin)
 *                   then it twists the content of that file (or stdin) according to
 *                   the number of characters to twist (b).  Finally the program
 *                   writes the twisted output back to an output file (or stdout).
 *
 *
 *      @argument -i   the name of the input file (default: stdin)
 *      @argument -o   the name of the output file (default: stdout)
 *      @argument -b   the number of characters to be twisted (default: 10)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define buflen 1024         //define the size of the buffer that would hold the content of a file (or user input)

int main(int argc, char *argv[])
{
    char *inp, *oup;           //char inp is a variable that holds the name of the input file, and char oup hold the name of the output file.
    int b=10, i=0, j=0, fndi=0, fndo=0;         // int b hold the number of characters to be twisted and int i & int j are loop indices.
                                                // int fndi turns to one to indicate that an input file has been found and int fndo turns to one to indicate that an output file has been found.

    for(i=0;i<argc;i++){                        //this loop checks the command line entered by user.
        if((strcmp(argv[i],"-i")==0)&&i<(argc-1)){
            if((strcmp(argv[i+1],"-o")!=0)&&(strcmp(argv[i+1],"-b")!=0)){ //if the command has (-i) then this if statement checks if the preceding is a file name or just a parameter.
                inp=argv[i+1];
                fndi=1;                         //fndi turn to one to indicate that an input file has been found.
            }
        }
        if((strcmp(argv[i],"-o")==0)&&i<(argc-1)){
            if((strcmp(argv[i+1],"-i")!=0)&&(strcmp(argv[i+1],"-b")!=0)){   //if the command has (-o) then this statement checks if the preceding is a file name of not.
                oup=argv[i+1];
                fndo=1;                         //fndo turns to one to indicate that an output file has been found.
            }
        }
        if((strcmp(argv[i],"-b")==0)&&i<(argc-1)){
            if((strcmp(argv[i+1],"-o")!=0)&&(strcmp(argv[i+1],"-b")!=0)){   //if the command has (-b) then this statement check if the preceding is a number or not.
                b=atoi(argv[i+1]);
            }
        }
    }

    if (b>=1000){       //if b (number of character in a twist block) is 1000 or more then print error and exit
        fprintf(stderr,"\nError: The number of characters (b) should be less than 1000\n\n");
        exit(-1);
    }

    char buff[buflen];          //this buffer array is the array the would hold the content of a file (or user input).
    int ifile, ofile, isz;      // ifile is the relative path to the input file, ofile is the relative path to the output file.
                                // isz will hold the size of the input file.

    if(fndi==0){                //if no input file name has been entered then take input from stdin.
        isz=read(STDIN_FILENO,buff,buflen);
        buff[isz]='\0';
        if (buff[strlen(buff)-1]=='\n'){
            buff[strlen(buff)-1]='\0';
        }
    }
    else{                       //else if there's a file name, then try to open that file, if the file cannot be opened then print error.
        ifile=open(inp, O_RDONLY);      //open file and assign file path to ifile.

        if (ifile<0){
            fprintf(stderr,"\nCannot open the input file (%s): %s\n\n",inp,strerror(errno));
            exit(-1);
        }
        isz=read(ifile,buff,buflen);    //read file and assign the size to isz.
        if (isz<=1){
            fprintf(stderr,"\nError: Input file is empty\n\n");
            exit(-1);
        }
        buff[isz]='\0';
        if(buff[isz-1]=='\n'){
            buff[isz-1]='\0';
        }
    }
    if(fndo==1){                //if there's an output file then open, if cannot be opened then print error.
        ofile=open(oup,O_WRONLY | O_TRUNC);       //opens output file, if cannot be opened then print error.

        if(ofile<0){
            fprintf(stderr,"\nCannot find output file (%s): %s\n\n",oup,strerror(errno));
            exit(-1);
        }
    }

    char temp1[b], temp2[b], opbuff[buflen];    //temp1 and temp2 are temporary arrays that will be used in the for loops below to copy and twist characters
                                                //after twisting characters then the twisted characters are going to be copied to opbuff.

    if(b>isz){                                  //if number of characters to twist is larger then the content then make the number of character to twist (b) equal to the size of the input
        b=isz;
    }

    for(j=0;j<isz;j+=b){                        //this for loop is used to copy characters from the input file (or user input).
        for(i=0;i<b;i++){                     //this for loop copies the content of the input to temp1 is chunks of b (number of characters to twist).
            temp1[i]=buff[i+j];
        }
        temp1[b+j]='\0';
        int temp1len=strlen(temp1);
        for(i=0;i<b;i++){                       //this for loop copies the characters from temp1 to temp2 in reverse. Which means the last element in temp1 will the first element in temp2.
            temp2[i]=temp1[((temp1len)-(i+1))];
        }
        temp2[b+j]='\0';
        int temp2len= strlen(temp2);
        for(i=0;i<b;i++){                     //this for loop copies the twisted element from temp2 to opbuff.
            if(i>temp2len){
                opbuff[strlen(opbuff)]='\0';
                break;
            }
            opbuff[j+i]=temp2[i];
        }
        opbuff[b+j]='\0';
    }

    //opbuff[strlen(buff)]='\0';
    opbuff[strlen(buff)]='\n';

    int osz;                                    //osz will hold the output file size when it's being written to.
    if(fndo==0){                                // this if statement prints the output to stdout if there's no output file, otherwise, the output gets written to the output file
        osz=write(STDOUT_FILENO,opbuff,strlen(opbuff));
    }
    else{
        osz=write(ofile,opbuff,strlen(opbuff));     //writes twisted output from opbuff to output file.
        osz=close(ofile);                           //close output file
        if(osz<0){
            fprintf(stderr,"\nError closing file (%s): %s\n\n",oup,strerror(errno));
            exit(-1);
        }
    }

    if(fndi==1){
        isz=close(ifile);                           //close input file if there's one
        if(isz<0){
            fprintf(stderr,"\nError closing file (%s): %s\n\n",inp,strerror(errno));
            exit(-1);
        }
    }

    return 0;
}

