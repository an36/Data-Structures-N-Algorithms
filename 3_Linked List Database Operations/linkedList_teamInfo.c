/*
 * LinkedList.c - Linked List ADT
 *
 * Originator: Roy Kravitz (roy.kravitz@pdx.edu)
 * Author:  Abdullah Almarzouq (an36@pdx.edu)
 * 
 * This is the source code file for a Linked List ADT that
 * implements a singly linked list.  
 *
 * @note Code is based on DynamicStack.c from Narasimha Karumanchi
 * @note Data Structures and Algorithms Made Easy, Career Monk Publishers, 2016
 *
 * @note Prints messages to stdio.  This is Karumanchi's doing
 */

#include <stdio.h>
#include <stdlib.h>
#include "starter_code/teamInfo_LinkedList.h"
#include "starter_code/teamInfo.h"

// API functions

/**
 * Creates a new instance of the Linked List
 *
 * @returns	Pointer to the new Linked List instance if it succeeds.  NULL if it fails
 */
LinkedListPtr_t createLList(void) {
	LinkedListPtr_t L = (LinkedListPtr_t) malloc(sizeof(LinkedList_t));
	if(!L)
		return NULL;
	L->head = NULL;
	L->count = 0;
	return L;
}


/**
 * Returns the number of items in the list
 *
 * @param L is a Pointer to a LinkedList instance
 *
 * @returns	Returns the number of nodes in the linked list
 */
int LListLength(LinkedListPtr_t L){
	return L->count;
}


/**
 * Inserts a new node into the linked list
 *
 * @param L is a Pointer to a LinkedList instance
 * @param data is the data item to put into the ndw node
 * @param pos is the position in the list to insert the item
 *
 * @returns	void
 */
void insertNodeInLList(LinkedListPtr_t L, TeamInfoPtr_t data, int pos){    //type of data changed to TeamInfoPtr_t so it could hold each element of info of a team
	ListNodePtr_t head = L->head;
	ListNodePtr_t q, p;
	ListNodePtr_t newNode = (ListNodePtr_t) malloc(sizeof(ListNode_t));

	int k = 1;

	if(!newNode){
		printf("LinkedList ADT: Memory Error\n");
		return;
	}
	newNode->data = data;
	p = head;
	if ((pos == 1) || (p == NULL)){
		newNode->next = head;
		L->head = newNode;
		L->count++;
	}
	else {
		while((p != NULL) && (k < pos)){
			k++;
			q = p;
			p = p->next;
		}
		newNode->next = q->next;
		q->next = newNode;
		L->count++;
	}
}


/**
 * Deletes a new node into the linked list
 *
 * @param L is a Pointer to a LinkedList instance
 * @param pos is the position in the list to insert the item
 *
 * @returns	void
 */
void deleteNodeFromLLinkedList(LinkedListPtr_t L, int pos) {
	ListNodePtr_t head = L->head;
	ListNodePtr_t q, p;

	int k = 1;

	p = head;
	if(head == NULL){
		printf("LinkedList ADT: List Empty\n");
		return;
	}
	else if( pos == 1){
		L->head = head->next;
		free(p);
		L->count--;
	}
	else {
		while((p!=NULL) && (k < pos)){
			k++;
			q = p;
			p = p->next;
		}
		if(p == NULL){
			printf("LinkedList ADT: Position does not exist\n");
		}
		else{
			q->next = p->next;
			free(p);
			L->count--;
		}

	}
}


/**
 * Prints all of the data items in the Linked List
 *
 * @param L is a Pointer to a LinkedList instance
 *
 * @returns	void
 */
void printLList(LinkedListPtr_t L) {        //There is no need for this function as the element of each node are going to be printed using another function

//	ListNodePtr_t head = L->head;
//	char name[MAX_TEAM_NAME]= head->data[0];
//	char nickname[MAX_TEAM_NICKNAME]= head->data->nickname;
//	int league= head->data->league;
//	int conf= head->data->conf;
//	int wins= head->data->wins;
//	int losses= head->data->losses;
//	int draws= head->data->draws;
//
//	while(head != NULL){
//		printf("name: %s\n", name);
//		printf("nickname: %s\n", nickname);
//		printf("league: %d\n", league);
//		printf("conf: %d\n", conf);
//		printf("wins: %d\n", wins);
//		printf("losses: %d\n", losses);
//		printf("draws: %d\n", draws);
//		head = head->next;
//	}
//	printf("\n");
}
