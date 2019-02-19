/*  
	Project 4
	Michael Canniffe

	Description
		This is my list.c file. It creates a circular deque with a dummy node to remove the need for  
		special cases.  This file includes functions to create and destroy the list.  It also includes
		functions that add and remove nodes from the begninning and end of the linked list.  It also includes
		three functions that will be referenced in my set.c
	 

*/

#include "set.h"
#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


struct node{
	void *data;
	struct node *prev;
	struct node *next;
};


typedef struct node NODE;


struct list {
	int count;
	struct node *head;
	int (*compare)();
};

typedef struct list LIST;


//O(1)
//return a pointer to a new list using compare as its comparison function, which may be NULL
LIST *createList(int (*compare)()){
	LIST *lp;
	lp = malloc(sizeof(LIST));
	assert(lp!=NULL);
	lp->count = 0;
	NODE *dummy;	
	dummy= malloc(sizeof(NODE));
	dummy ->next = dummy;
	dummy ->prev = dummy;
	lp->head = dummy;
	lp->compare=compare;
	return lp;
}

//O(n)
//deallocate memory associated with the list pointed to by lp
void destroyList(LIST *lp){
	assert(lp != NULL);
	struct node *i;
	for(i=lp->head->next; i !=lp->head; i= i->next){
		free(i);
	}
	
	free(lp->head);
	free(lp);
}

//O(1)
//return the number of items in the list pointed to by lp
int numItems(LIST *lp){
	assert(lp != NULL);
	return lp->count;
}


//O(1)
//add item as the first item in the list pointed to by lp
void addFirst(LIST *lp, void *item){
	NODE *dummy;
	dummy = lp->head;
	NODE *new;
	new = malloc(sizeof(NODE));
	new->data = item;

	new->prev = dummy;
	new->next = dummy->next;
	dummy->next->prev = new;
	dummy->next = new;
	lp->count++;
}


//O(1)
//add item as the last item in the list pointed to by lp
void addLast(LIST *lp, void *item){
	NODE *dummy;
	dummy = lp->head;
	NODE *new;
	new = malloc(sizeof(NODE));
	new->data = item;

	new->next = dummy;
	new->prev = dummy->prev;
	dummy->prev->next = new;
	dummy->prev = new;
	lp->count++;
}


//O(1)
//remove and return the first item in the list pointed to by lp ; the list must not be empty
void *removeFirst(LIST *lp){

	NODE *dummy;
	dummy = lp->head;
	NODE *temp = dummy->next;
	dummy->next->next->prev = dummy;
	dummy->next=temp->next;
	void *tempdata;
	tempdata= temp->data;
	free(temp);
	lp->count--;
	return tempdata;


}




//O(1)
//remove and return the last item in the list pointed to by lp ; the list must not be empty
void *removeLast(LIST *lp){

	NODE *dummy;
	dummy = lp->head;
	NODE *temp = dummy->prev;
	dummy->prev->prev->next = dummy;
	dummy->prev=temp->prev;
	void *tempdata; 
	tempdata= temp->data;
	free(temp);
	lp->count--;
	return tempdata;
}

//O(1)
//return, but do not remove, the first item in the list pointed to by lp ; the list must not be empty
void *getFirst(LIST *lp){

	NODE *dummy;
	dummy = lp->head;
	return dummy->next->data;

}

//O(1)
//return, but do not remove, the last item in the list pointed to by lp ; the list must not be empty
void *getLast(LIST *lp){
	
	
	NODE *dummy;
	dummy = lp->head;
	return dummy->prev->data;

}

//O(n)
//if item is present in the list pointed to by lp then remove it; the comparison function must not be NULL
void removeItem(LIST *lp, void *item){
	assert(lp != NULL || item != NULL || lp->compare != NULL);
	NODE *i;
	for(i=lp->head->next ;i != lp->head;i = i->next){
		if((*lp->compare)(i->data,item)==0){
			NODE *temp = i;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			lp->count--;
			free(temp);
			break;
		}
	}
}


//O(n)
//if item is present in the list pointed to by lp then return the matching item, otherwise return NULL; the comparison function must not be NULL
void *findItem(LIST *lp, void *item){
	assert(lp != NULL || item != NULL || lp->compare != NULL);
	NODE *i;
	for(i=lp->head->next ;i != lp->head;i = i->next){
		if((*lp->compare)(i->data,item)==0){
			return i->data;
		}
	}
	return NULL;	
}

//O(n)
//allocate and return an array of items in the list pointed to by lp
void *getItems(LIST *lp){
	assert(lp != NULL || lp->compare != NULL);
	void **temp;
	temp = malloc(sizeof(void*)* lp->count);
	assert(temp != NULL);
	NODE *i;
	int j = 0;
	for(i= lp->head->next; i !=lp->head; i = i->next){
		temp[j] = i->data;
		j++;
	}

	return temp;

}



