/*
   Michael Canniffe
   Dr. Atkinson
   Project 3 
   generic


Description:
	This file creates a set which points to an arrau of void* elements.  The elemensts are oragnized     by a hashing function which allows each array to be compressed into a numerical location.  If 
	that location is already taken, then the function uses linear probing to find an opening.
	It also includes funcions for adding removing, and counting elements in the set.
*/

//#define strhash
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
//# ifndef SET_H
//# define SET_H
#include "set.h"
#define EMPTY 0
#define FILLED 1
#define DELETED 2


//declares a struct with these variables 
typedef struct set{
	int count;
	int length;
	void **data;
	char *flags;
	int (*compare)();
	unsigned (*hash)();

}SET;

//O(n)
//creates a set with the variables from struct and allocates memory for them
SET *createSet(int maxElts,int(*compare)(),unsigned (*hash)()){
	SET *sp;
	int i;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp -> count=0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(void *)*maxElts);
	assert(sp->data !=NULL);
	sp->flags = malloc(sizeof(char )*maxElts);
	sp->compare = compare;
	sp->hash = hash;
	assert(sp->flags !=NULL);
	for (i=0; i<maxElts; i++){
		sp->flags[i] = EMPTY;
	}
	
	return sp;
}


//O(n)
//this function search an element in the array and returns 0 if it is empty, 1 if it is filled, or 2 if it was previously filled, but is now deleted.  It will hash to the initial location where the 
//element should be and continue linear probing until it is either found or a 0 is found
static int search(SET *sp, void *elt, bool *found ){
	assert(sp != NULL && elt != NULL);
	int i;
	int deleteLocn = -1;
	
	
	int start = (*sp->hash)(elt) % sp->length;
	for(i=0;i<sp->length;i++){
		int locn = (start + i) % sp->length;
		if(sp->flags[locn] == EMPTY){
			*found = false;
			if(deleteLocn == -1){
				return locn;
			}
		}
		else if(sp->flags[locn]==FILLED){
			if(((*sp->compare)(sp->data[locn],elt))==0){
				*found = true;
				return locn;
			}
		}
		else{
			if(deleteLocn == -1){
				deleteLocn = locn;
			}
		}
	}
	*found = false;
	return deleteLocn ;
}

//O(1)
//this function destroys the set and frees all of the pointers that had  being allocated
void destroySet(SET *sp){
	free(sp->data);
	free(sp->flags);
	free(sp);
}

//O(1)
//this function returns the number of elements in the set
int numElements(SET *sp){
	assert(sp !=NULL);
	if(sp !=NULL){
		return sp->count;
	}
	else{
		return -1;
	}
}


//O(1)
//this funciton takes an element, hashes it, and then inserts it in the correct location once the probing has been completed.  Then it sets the flag to filled and increments the count
void addElement(SET *sp, void *elt){
	
	assert(sp != NULL || elt != NULL);
	bool found;
	int a;
	a = search(sp, elt, &found);
	if(!found){
		sp->data[a]=elt;
		sp->flags[a]=FILLED;
		sp->count++;
	}
}



//O(1)
//this function hashes an element and then probes until it finds it.  Once it has been found, the 
//flag is set to 2 and the count is decremented
void removeElement(SET *sp, void *elt){
	assert(sp != NULL || elt != NULL);
	bool found;
	int a;
	a = search(sp, elt, &found);
	if(found){
		sp->flags[a]=DELETED;
		sp->count--;
	}
}

//O(1)
//this function finds an element in the set
void *findElement(SET *sp, void *elt){
	assert(sp != NULL || elt != NULL);
	bool found;
	int i  = search(sp, elt,&found);
	if(found){
		return sp->data[i];
	}
	else{
		return NULL;
	}
}


//O(n)
//creates a copy of the current array 
void *getElements(SET *sp){
	assert(sp != NULL);
	int i;
	int j=0;
	void **temp = malloc(sizeof(void *)*sp->count);
	assert(temp !=NULL );
	for(i=0;i<sp->length;i++){
		if(sp->flags[i]==FILLED){
			temp[j]=sp->data[i];
			j++;
		}
	}
	return temp;
}
















