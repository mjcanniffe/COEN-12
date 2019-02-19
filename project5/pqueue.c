/* Michael Canniffe
   Dr. Atkinson 
   Project 5.   pqueue.c

	Description
			This is my pqueue.c file. It implements a priority queue that stores the smallest integer value as the root of the
			tree.  I have functions that create and destroy the priority queue.  A function to return the number of entries.
			I also have functions to add and remove numbers from the priority queue.	My add function uses a helper function
			that uses recursion to "bubble up" the inserted number until it reaches its correct position.  The last function,
			removeEntry will remove the first element and the reorder the priority queue.

*/
#include "pack.h"
#include "pqueue.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define START_LENGTH 10
#define p(x) (((x)-1)/2)
#define l(x) ((x)*2+1)
#define r(x) ((x)*2+2)

struct pqueue{
	int count;
	int length;
	void **data;
	int (*compare)();
};

//O(1)
//creates the priority queue, intializies all of the variables and allocates the appropriate memory
PQ *createQueue(int (*compare)()){
	PQ *pq;
	pq = NULL;
	pq = malloc(sizeof(PQ));
	assert( pq !=NULL);
	pq->length = START_LENGTH;
	pq->data = malloc(sizeof(void*) * pq->length);
	assert(pq->data != NULL);
	pq->count = 0;
	pq->compare = compare;
	return pq;	
}

//O(1)
//frees all of the memory for the priority queue
void destroyQueue(PQ *pq){
	assert(pq != NULL);
	free(pq->data);
	free(pq);
}


//O(1)
//returns the count of the priority queue
int numEntries(PQ *pq){
	assert(pq != NULL);
	return pq->count;

}

//O(1)
//My add function uses a helper function that uses recursion to "bubble up" the inserted number until it reaches
//its correct position. 
void addHeapify(PQ *pq, int i){
	assert(pq !=  NULL);
	void *temp;
	if(i==0){
		return;
	}
	if((*pq->compare)(pq->data[i],pq->data[p(i)])<0) {
		temp = pq->data[i];
		pq->data[i] = pq->data[p(i)];
		pq->data[p(i)] = temp;
	}
	addHeapify(pq, p(i));
}

//O(1)
//My add function checks if there is space to add another item and if not, reallocates twice the smount of memory to make room 
//for the next entry. It adds the new element to the last position and then uses the helper function to  get it to the right place

void addEntry(PQ *pq, void *entry){
	assert(pq != NULL || entry != NULL);
	if(pq->count == pq->length){
		pq->data = realloc(pq->data, sizeof(void*)*pq->length*2);
		pq->length *= 2;
	}
	pq->data[pq->count] = entry;
	addHeapify(pq, pq->count);
	pq->count++;

}

//O(n)
//removes the first item and puts the last item in the first poistion.  then it uses a while loop to correctly sort the priority
//queue.  It finds the smallest child and then compares it to the parent, swapping them if the child is smaller.
void *removeEntry(PQ *pq){
	int i=0;
	int small; 
	void *removedItem;
	void *temp;
	assert(pq != NULL);
	if(pq->count ==1){
		pq->count--;
		return pq->data[0];
	}

	removedItem = pq->data[0];
	pq->data[0] = pq->data[pq->count-1];
	pq->count--;

	while(l(i) < pq->count){
		if(r(i)<pq->count){
			if((*pq->compare)(pq->data[l(i)],pq->data[r(i)])>0 ){
				small = r(i);
			}
			else{
				small = l(i);
			}
		}
		else{
			small = l(i);
		}

		if((*pq->compare)(pq->data[i],pq->data[small])>0){
			temp = pq->data[i];
			pq->data[i] = pq->data[small];
			pq->data[small] = temp;
			i = small;
		}
		else{
			break;
		}
}
	return removedItem;

}

