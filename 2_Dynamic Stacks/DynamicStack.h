struct Stack {
    int top;
    int capacity;
    int *array;
};

struct Stack *createStack(int capacity) {
    struct Stack *S = malloc(sizeof(struct Stack));
    if(!S) 
        return NULL;
    S->capacity = capacity;
    S->top = -1;
    S->array= malloc(S->capacity * sizeof(int));
    if(!S->array) 
        return NULL;
    return S;
}

int isEmpty(struct Stack *S) {
    return (S->top == -1);  	// if the condition is true then 1 is returned else 0 is returned
}

int size(struct Stack *S) {
    return (S->top + 1);  
}

int isFull(struct Stack *S){
    //if the condition is true then 1 is returned else 0 is returned
    return (S->top == S->capacity - 1); 
}

void doubleStack(struct Stack *S){
    S->capacity *= 2;
    S->array = realloc(S->array, S->capacity * sizeof(int));
}


void push(struct Stack *S, int data){
    if(isFull(S)) 
        doubleStack(S); 
    S->array[++S->top] = data;   
}

int pop(struct Stack *S){
    /* S->top == - 1 indicates empty stack*/
    if(isEmpty(S)){	
        printf("Stack is Empty\n");
        return INT_MIN;
    }
    else /* Removing element from  ?top? of the array and reducing ?top? by 1*/
        return (S->array[S->top--]); 
}

int peek(struct Stack *S){
    /* S->top == - 1 indicates empty stack*/
    if(isEmpty(S)){	
        printf("Stack is Empty");
        return INT_MIN;;
    }
    else 
        return (S->array[S->top]); 
}

void deleteStack(struct Stack *S){
    if(S) {     
        if(S->array)  
             free(S->array);
                  free(S);
      }
}
