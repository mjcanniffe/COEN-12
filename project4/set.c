/*  
	Project 4
	Michael Canniffe

	Description
		This is my set.c file. It implements a set using a hash table and resolving the collisions  

*/

#include "set.h"
#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define AVG_LENGTH 20
struct set{
	int count;
	int length;
	LIST **data;
	int(*compare)();
	unsigned(*hash)();
};
typedef struct set SET;



//this function creates a set pointer and mallocs space for that set.  It then assigns a value to each of 
//corresponding variables
//O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->data = malloc(sizeof(LIST*)*(maxElts/AVG_LENGTH));
	sp->length=maxElts/AVG_LENGTH;
	sp->count = 0;
	sp->compare=compare;
	sp->hash=hash;
	int i;
	for(i=0;i<sp->length;i++){
		sp->data[i]=createList(compare);
	}
	return sp;
}

//O(n)
//destroys each list and then frees the set
void destroySet(SET *sp){
	assert(sp != NULL);
	int i;
	for(i=0; i<sp->length; i++){
		destroyList(sp->data[i]);
	}
	free(sp->data);
	free(sp);
}

//O(1)
//return the number of items in the set pointed to by sp
int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;
}


//O(1)
//hashes an element to a location in a hash table and then uses chaining to to resolve collisions
void addElement(SET *sp, void *elt){
	assert(sp!=NULL || elt !=  NULL);
	int loc;
	loc = ((*sp->hash)(elt)%sp->length);
	if(findItem(sp->data[loc], elt) == NULL){
		addFirst(sp->data[loc], elt);
		sp->count++;
	}

}



//O(1)
//hashes an element and removes it from the correspoding linked list 
void removeElement(SET *sp, void *elt){
	assert(sp!=NULL || elt !=  NULL);
	int loc, count;
	loc = ((*sp->hash)(elt)%sp->length);
	count = numItems(sp->data[loc]);
	removeItem(sp->data[loc], elt);
	if(count>numItems(sp->data[loc])){
		sp->count--;
	}
}


//O(1)
//hashes an element to a location and then traverses to a corresponding linked list to find the 
//right item
void *findElement(SET *sp, void *elt){
	assert(sp!=NULL|| elt !=NULL);
	int loc;
	loc= ((*sp->hash)(elt))%sp->length;
	return findItem(sp->data[loc],elt);
}


//O(n^2)
//allocate and return an array of items in the list pointed to by sp
void *getElements(SET *sp){
	assert(sp != NULL);
	void **temp1 = NULL;
	void **temp2 = NULL;
	temp1 = malloc(sizeof(void*)* sp->count);
	assert(temp1 != NULL);
	int i,j,k,l;
	k=0;
	for(i=0;i<sp->length;i++){
		temp2 = getItems(sp->data[i]);
		l = numItems(sp->data[i]);
		for(j=0;j<l;j++){
			temp1[k]=temp2[j];
			k++;
		}
		free(temp2);
	}
	return temp1;
}













