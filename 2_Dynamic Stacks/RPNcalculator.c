#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "DynamicStack.h"

/*  Abdullah Almarzouq
    
    The DynamicStack.h header file includes the stack struct and functions that would create a stack, push to a stack, pop from stack and so on.
    The program below, within main(), lets the user to evaluate expression using RPN calculations.
    It asks the user to enter the expression (numbers followed by operators) then evaluate that expression accordingly.
*/

int main()
{
    int expLen=0,i=0,capacity=0,res=0;           //expLen is the length of the expression, i is a loop index, capacity is the capacity of the stack
                                                 // res holds the result of an operation
    char exp[10]; exp[0]='1';                    // exp is a char array that holds the full expression entered by the user, the exp[0]='1' line lets the while loop works, if exp[0] is not a number then the program stops

    while(isdigit(exp[0])){                      //This while loop checks if the entered expression is a number
        printf("Enter an RPN expression: ");
        scanf(" %s",&exp);                       //lets the user enter the expression
        expLen=strlen(exp);                      //finds the length of the expression

        for(i=0;i<expLen;++i){                   //this for loop finds how many operands within the expression and increments 'capacity' by one
            if(isdigit(exp[i])){
                capacity++;
            }
        }
        struct Stack *nums=createStack(capacity);   //this line creates a stack (nums) with amount of 'capacity'

        for(i=0;i<expLen;++i){                   //this loop checks if the element within the expression is an operand then it pushes it to the stack, otherwise, if the element if an operator then perform that operation
            if(isdigit(exp[i])){
                push(nums,exp[i]-48);

            }
            else {                              //here the else statements checks if the element is an operator then performs the operation
                if(i>1){
                    if(exp[i]=='+'){
                        res=pop(nums)+pop(nums);   //if addition then pop a number and added to another popped number from the stack
                        push(nums,res);
                    }

                    if(exp[i]=='-'){           //if subtraction then pop a number then pop another one and subtracted the firstly popped number from the lastly popped number
                        res=pop(nums);
                        res=pop(nums)-res;
                        push(nums,res);
                    }
                    if(exp[i]=='*'){           // if multiplication then pop two numbers and multiply them
                        res=pop(nums)*pop(nums);
                        push(nums,res);
                    }
                    if(exp[i]=='/'){          //if division then the operation goes just like how the subtraction does
                        res=pop(nums);
                        res=pop(nums)/res;
                        push(nums,res);
                    }
                    if(exp[i]=='='){          // the '=' operator prints the top element of the stack
                        printf("Value of expression= %d\n",peek(nums));
                    }
                }
            }
        }
        deleteStack(nums);               //this line deletes the stack in case the user want to perform another calculation
    }

    return 0;
}
