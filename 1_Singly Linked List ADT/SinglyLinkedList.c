#include<stdio.h>
#include<stdlib.h>

#define MAX_LEN 10

/*  Abdullah Almarzouq
    
    The functions below can create up to 10 singly linked lists and the main() functionality allows the user
    to manipulate each linked list by choice.  The user can fill/refill each list with the desired number of nodes.
    The user can also insert a node, delete a node, print the data within a list and print the size of a list.
*/

struct listNode{
	int data;
	struct listNode *next;
};

struct listNumbers{                         //This struct holds an array of singly linked lists
    struct listNumbers *array[MAX_LEN];
};

struct listNode *createList(){             //This function can create a head list and assign in to NULL
    struct listNode *head;
    head = malloc(sizeof(struct listNode));
    head = NULL;
    return head;
};

int singlyListLength(struct listNode *head){
	int count=0;
	struct listNode *current=head;
	while(current!=NULL){
		count++;
		current=current->next;
	}
	return count;
}
void insertInSinglyLinkedList(struct listNode **head, int data, int pos){
	int k=1;
	struct listNode *q,*p;
	struct listNode *newNode=(struct listNode*)malloc(sizeof(struct listNode));
	if(!newNode){
		printf("Memory Error\n");
		return;
	}
	newNode->data=data;
	p=*head;
	if(pos==1 || p==NULL){
		newNode->next=*head;
		*head=newNode;
	}
	else{
		while(p!=NULL && (k<pos)){
			k++;
			q=p;
			p=p->next;
		}
		newNode->next=q->next;
		q->next=newNode;
	}
}
void deleteNodeFromLinkedList(struct listNode **head, int pos){
	int k=1;
	struct listNode *p,*q;
	p=*head;
	if(*head==NULL){
		printf("List Empty\n");
		return;
	}
	else if(pos==1){
		*head=(*head)->next;
		free(p);
	}
	else{
		while(p!=NULL && k<pos){
			k++;
			q=p;
			p=p->next;
		}
		if(p==NULL){
			printf("Position does not exist\n");
		}
		else{
			q->next=p->next;
			free(p);
		}
	}
}
void printSLList(struct listNode *head){
	while(head!=NULL){
		printf("%d ",head->data);
		head=head->next;
	}
	printf("\n");
}

int main()
{
    int i=0,nodeNum,data,listNum=0,listIndex=1, choice=1;   //i is a loop index, nodeNum is the number of nodes, data is the data within a node, listNum is the number of lists,
                                                            //listIndex is the index of a chosen list and choice is the user choice from the menu
    int size=0,position=0;                                  // size if the size of a list, position is the user's choice of what node to delete or where to insert a node
    char quit='Y';                                          //quit is a while loop condition for the creation of lists

    struct listNumbers *array[MAX_LEN];                     // this line defines the struct array that would hold the linked lists

    while(choice>0){                                           //The user can choose what they want to do from the menu below
        printf("\nNumber of lists created is: %d\n",listNum);
        printf("Enter [1] to create new Singly Linked Lists\n");
        printf("Enter [2] to fill/refill a Singly Linked List\n");
        printf("Enter [3] to check the size of a Singly Linked List\n");
        printf("Enter [4] to insert data in a node within a Singly Linked List\n");
        printf("Enter [5] to delete a node within a Singly Linked List\n");
        printf("Enter [6] to print the data within a Singly Linked List\n");
        printf("Enter [0] to quit\n");
        printf("Enter here: ");
        scanf("%d",&choice);

        if (choice==1){                            //This if statement lets the user to choose how many lists they want to create
            quit='Y';
            printf("\nHow many Singly Linked Lists do you want to create [1 to 10]? ");
            scanf("%d",&listNum);

            while (listNum<=0 || listNum>10){      //if the number of lists is less than 1 or higher then 10, then let the user choose again
                printf("\nNumber of lists should between 1 and 10 inclusively\n");
                printf("\nHow many Singly Linked Lists do you want to create [1 to 10]? ");
                scanf("%d",&listNum);
            }

            for (i=0;i<listNum;i++){               //this for loop creates listNum amount of lists
                array[i]= createList();
            }

            printf("\nYou have created %d linked lists\n",i);


            while(quit=='Y'||quit=='y'){         //while loop that asks the user if they want to fill/refill a list while the user creates the lists
                if(listNum>1){
                    printf("\nWhich list do you want to fill with data? ");
                    scanf("%d",&listIndex);
                    while (listIndex>listNum){     //if the list doesn't exist then let the user choose again
                        printf("\nThere are only %d lists",listNum);
                        printf("\nWhich list do you want to fill with data? ");
                        scanf("%d",&listIndex);
                    }
                    array[listIndex-1]=createList();   //this line would empty the chosen list so the user can refill it
                }
                printf("\nHow many nodes do you want within the list? ");   //asks the user how many nodes they want within a list
                scanf("%d",&nodeNum);
                printf("\n");

                for(i=1; i<=nodeNum; i++){            //This loop lets the user fill a list with the desired data
                    printf("Enter the data for node #%d: ",i);
                    scanf("%d",&data);
                    insertInSinglyLinkedList(&array[listIndex-1],data,i);
                }

                printf("\nData: ");
                printSLList(array[listIndex-1]);

                printf("\nDo you want to fill/refill a list again (y or n)?");  //asks the user if they want to fill/refill a list, this line could activate the while loop with the quit variable
                scanf(" %c",&quit);
                printf("\n");

                if((quit=='Y' ||quit=='y')&&listIndex==1){
                    array[listIndex-1]=createList();
                }
            }
        }

        if (choice==2){        //this if statement lets the user fill/refill a list from the main menu
            if(listNum>1){
                printf("\nWhich list do you want to fill with data? ");
                scanf("%d",&listIndex);
                while (listIndex>listNum){          //This while loop checks if the list exists, if not then asks the user again
                    printf("There are only %d lists\n",listNum);
                    printf("\nWhich list do you want to fill with data? ");
                    scanf("%d",&listIndex);
                }
                    array[listIndex-1]=createList();
            }
            else if (listNum==1){
                array[listIndex-1]=createList();
            }
                printf("\nHow many nodes do you want within the list? ");
                scanf("%d",&nodeNum);
                printf("\n");

                for(i=1; i<=nodeNum; i++){
                    printf("Enter the data for node #%d: ",i);
                    scanf("%d",&data);
                    insertInSinglyLinkedList(&array[listIndex-1],data,i);
                }

                printf("\nData: ");
                printSLList(array[listIndex-1]);
        }

        if (choice==3){                       //This if statement prints the size of a list
            if(listNum==1){
                size=singlyListLength(array[listIndex-1]);
                printf("\nThe size of the list is %d node/s",size);
                printf("\n");
            }
            else{                            //This statement lets the user choose which list they want to print the size of, if it doesn't exist then ask the user again
                printf("\nWhich list do you want find the size of? ");
                scanf("%d",&listIndex);
                while(listIndex>listNum){
                    printf("There only %d lists created\n",listNum);
                    printf("\nWhich list do you want find the size of? ");
                    scanf("%d",&listIndex);
                }
                size=singlyListLength(array[listIndex-1]);
                printf("\nThe size of the list is %d node/s",size);
                printf("\n");
            }
        }

        if (choice==4){            //This if statement lets the user insert a node within a list, if the list or node doesn't exist then asks the user again
            if (listNum>1){
                printf("\nWhich list do you want to insert a node to? ");
                scanf("%d",&listIndex);
                while (listIndex>listNum){
                    printf("There are only %d lists\n",listNum);
                    printf("\nWhich list do you want to insert a node to? ");
                    scanf("%d",&listIndex);
                }
            }
            printf("\nAt what position do you want to insert the node? ");
            scanf("%d",&position);
            size=singlyListLength(array[listIndex-1]);
            while(position>size){
                printf("This list has %d node/s only\n",size);
                printf("\nAt what position do you want to insert the node? ");
                scanf("%d",&position);
            }
            printf("\nWhat's the data that you want to insert? ");
            scanf("%d",&data);
            insertInSinglyLinkedList(&array[listIndex-1],data,position);
            printf("\nData: ");
            printSLList(array[listIndex-1]);
        }

        if (choice==5){             //This if statement lets the user delete a node within a list, if the list or node doesn't exist then asks the user again
            if (listNum>1){
                printf("\nWhich list do you to delete a node from? ");
                scanf("%d",&listIndex);
                while(listIndex>listNum){
                    printf("There only %d lists created\n",listNum);
                    printf("\nWhich list do you to delete a node from? ");
                    scanf("%d",&listIndex);
                }
            }
            size=singlyListLength(array[listIndex-1]);
            printf("\nWhich node do you want to delete? ");
            scanf("%d",&position);
            while(position>size){
                printf("This list has %d node/s only\n",size);
                printf("\nWhich node do you want to delete? ");
                scanf("%d",&position);
            }
            deleteNodeFromLinkedList(&array[listIndex-1],position);
            printf("\nData: ");
            printSLList(array[listIndex-1]);
        }
        if (choice==6){             //This statement lets the user print the content within a list, if the list doesn't exist then asks the user again
            if (listNum>1){
                printf("\nWhich list do you want to print the content of? ");
                scanf("%d",&listIndex);
                while(listIndex>listNum){
                    printf("There only %d lists created\n",listNum);
                    printf("\nWhich list do you want to print the content of? ");
                    scanf("%d",&listIndex);
                }
            }
            printf("\nData: ");
            printSLList(array[listIndex-1]);
        }
    }
    return 0;
}
