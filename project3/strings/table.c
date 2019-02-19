/*
   Michael Canniffe
   Dr. Atkinson
   Project 3 
   strings

Description:
	This file creates a set which points to an array of char* elements.  The elemensts are oragnized     by a hashing function which allows each array to be compressed into a numerical location.  If 
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

//O(n)
//this function takes an array of characters and hashes each one to a location in the array.  If that location is already taken in the array, then the function uses linear probing to find an opening
unsigned strhash(char *s){
	unsigned hash = 0;

	while(*s != '\0'){
		hash = 31 * hash + *s ++;
	}
	return hash;
}

//this defines the types of data in the set
typedef struct set{
	int count;
	int length;
	char **data;
	char *flags;
}SET;



//O(n)
//creates a set with the variables from struct and allocates memory for them
SET *createSet(int maxElts){
	SET *sp;
	int i;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp -> count=0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(char *)*maxElts);
	assert(sp->data !=NULL);
	sp->flags = malloc(sizeof(char )*maxElts);
	assert(sp->flags !=NULL);
	for (i=0; i<maxElts; i++){
		sp->flags[i] = EMPTY;
	}
	
	return sp;
}


//O(n)
//this function search an element in the array and returns 0 if it is empty, 1 if it is filled, or 2 if it was previously filled, but is now deleted.  It will hash to the initial location where the 
//element should be and continue linear probing until it is either found or a 0 is found
static int search(SET *sp, char *elt, bool *found ){
	assert(sp != NULL && elt != NULL);
	int i;
	int deleteLocn = -1;
	
	
	int start = strhash(elt) % sp->length;
	for(i=0;i<sp->length;i++){
		int locn = (start + i) % sp->length;
		if(sp->flags[locn] == EMPTY){
			*found = false;
			if(deleteLocn == -1){
				return locn;
			}
			else{
				return deleteLocn;
			}
		}
		else if(sp->flags[locn]==FILLED){
			if(strcmp(sp->data[locn],elt )==0){
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

//O(n)
//this function frees all of the filled flags and then frees all of the data in the set
void destroySet(SET *sp){
	int i;
	for(i=0; i < sp->count; i++){
		if (sp->flags[i] ==FILLED) {
			free(sp->data[i]);
		}
	}
	free(sp->data);
	free(sp->flags);
	free(sp);
}

//O(1)
//this funtion returns the number of elements
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
void addElement(SET *sp, char *elt){
	
	assert(sp != NULL || elt != NULL);
	bool found;
	int a;
	a = search(sp, elt, &found);
	if(!found){
		sp->data[a]=strdup(elt);
		sp->flags[a]=FILLED;
		sp->count++;
	}
}



//O(1)
//this function hashes an element and then probes until it finds it.  Once it has been found, the 
//flag is set to 2 and the count is decremented
void removeElement(SET *sp, char *elt){
	assert(sp != NULL || elt != NULL);
	bool found;
	int a;
	a = search(sp, elt, &found);
	if(found){
		free(sp->data[a]);
		sp->flags[a]=DELETED;
		sp->count--;
	}
}


//O(1)
//this function find the location of an element and returns the data inside that element
char *findElement(SET *sp, char *elt){
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
//this function creates a copy of the array
char **getElements(SET *sp){
	assert(sp != NULL);
	int i;
	char **temp = malloc(sizeof(char *)*sp->count);
	assert(temp !=NULL );
	for(i=0;i<sp->count;i++){
		if(sp->flags[i]==FILLED){
			temp[i]=sp->data[i];
		}
	}
	return temp;
}
















