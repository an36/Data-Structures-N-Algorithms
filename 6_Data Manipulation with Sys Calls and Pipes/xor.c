/*
 *      ECE 362 | H.W.2 Part B | (XOR)
 *      Author: Abdullah Almarzouq     (an36@pdx.edu)
 *
 *      Description: The program below takes an input from an input file (or stdin)
 *                   then it performs and XOR operation the string/content of that
 *                   file (or stdin) with a mask value that is specified by the user.
 *                   Finally the program writes the XORed output back to an output
 *                   file (or stdout).
 *
 *
 *      @argument -i           the name of the input file (default: stdin)
 *      @argument -o           the name of the output file (default: stdout)
 *      @argument <string>     the mask which must be provided (must be less than 10 characters)
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
    char *inp, *oup, *mask;          //char inp is a variable that holds the name of the input file, char oup hold the name of the output file and char mask is the mask variable.
    int i=0, j=0, fndi=0, fndo=0, fndm=0;            //int i & int j are loop indices.
                                                         // int fndi turns to one to indicate that an input file has been found and int fndo turns to one to indicate that an output file has been found.
                                                         // int fndm turns to one to indicate that a mask has been found.

    for(i=1;i<argc;i++){                        //this loop checks the command line entered by user.
        if((strcmp(argv[i],"-i")==0)&&i<(argc-1)){
            if((strcmp(argv[i+1],"-o")!=0)){ //if the command has (-i) then this if statement checks if the preceding is a file name or just a parameter.
                inp=argv[i+1];
                fndi=1;                         //fndi turn to one to indicate that an input file has been found.
            }
        }
        if((strcmp(argv[i],"-o")==0)&&i<(argc-1)){
            if((strcmp(argv[i+1],"-i")!=0)){   //if the command has (-o) then this statement checks if the preceding is a file name of not.
                oup=argv[i+1];
                fndo=1;                         //fndo turns to one to indicate that an output file has been found.
            }
        }
        if((strcmp(argv[i],"-i")!=0)&&(strcmp(argv[i],"-o")!=0)){   //if the command has a mask then this statement checks to find it and assign to char m.
            if((strcmp(argv[i-1],"-o")!=0)&&(strcmp(argv[i-1],"-i")!=0)){
                if(fndm==0){
                    mask=argv[i];
                    fndm=1;                         //fndm turns to one to indicate that a mask has been found.
                }
            }
        }

    }
        if(fndm==0){
            fprintf(stderr,"\nError: No mask <string> has been found.\n\n");  //prints error if there's no mask string
            exit(-1);
        }
        else if(fndm==1&&strlen(mask)>=10){
            fprintf(stderr,"\nError: The mask <string> length must be less than 10 characters\n\n");    //print error if mask string length is more than 10 characters
            exit(-1);
        }

    char buff[buflen];          //this buffer array is the array the would hold the content of a file (or user input).
    int ifile, ofile, isz;      // ifile is the relative path to the input file, ofile is the relative path to the output file.
                                // isz will hold the size of the input file.

    if(fndi==0){                //if no input file name has been entered then take input from stdin.
        isz=read(STDIN_FILENO,buff,buflen);
        buff[isz]='\0';
        if(buff[strlen(buff)-1]=='\n'){
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
        buff[isz-1]='\0';
        if(buff[strlen(buff)-1]=='\n'){
            buff[strlen(buff)-1]='\0';
        }
    }
    if(fndo==1){                //if there's an output file then open, if cannot be opened then print error.
        ofile=open(oup,O_WRONLY | O_TRUNC);       //opens output file, if cannot be opened then print error.

        if(ofile<0){
            fprintf(stderr,"\nCannot find output file (%s): %s\n\n",oup,strerror(errno));
            exit(-1);
        }
    }

    char opbuff[buflen];            //opbuff is a string array that would hold the XORed output.
    for(i=0;i<strlen(buff);i++){    //This for loop goes through each element of the input string, XORs that element with the mask element.
        opbuff[i]=buff[i]^mask[j];     //XORs input with mask then assign that element to opbuff.
        j+=1;                       //increment index of mask[j]
        if(j>=strlen(mask)){        //if the mask index j is bigger or equal to the length of the mask string then let the index j=0.
            j=0;
        }
    }
    opbuff[strlen(buff)]='\0';
    opbuff[strlen(buff)]='\n';

    int osz;                                    //osz will hold the output file size when it's being written to.
    if(fndo==0){                                // this if statement prints the output to stdout if there's no output file, otherwise, the output gets written to the output file
        osz=write(STDOUT_FILENO,opbuff,strlen(buff)+1);
    }
    else{
        osz=write(ofile,opbuff,strlen(buff)+1);     //writes XORed output from opbuff to output file.
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


