#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"




typedef struct set{
	int count;
	int length;
	char **data;
}SET;
//creates a set and allocates memory for it
//O(1)
SET *createSet(int maxElts){
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp -> count=0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(char *)*maxElts);
	assert(sp->data !=NULL);
	return sp;
}
//frees all of the elements in the sets
//O(n)
void destroySet(SET *sp){
	int i;
	for(i=0; i < sp->count; i++){
        if (sp->flags[i] !=NULL) {
            free(sp->data[i]);
            free(sp->flags[i]);
	}
	free(sp->data);
    free(sp->flags);
	free(sp);
}

// search for an element and return its position, if it isnt there, return -1
//O(n)
static int search(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);
	int i;
	for(i=0;i<sp->count;i++){
		if(strcmp(sp->data[i],elt )==0){
			return i;
		}
	}
	return -1;
}


//returns the number of elements
//O(1)
int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;
}



//adds an element in the end of the list
//O(1)
void addElement(SET *sp, char *elt){	
	assert(sp != NULL && elt != NULL);
		
	if( search(sp, elt)==-1){
		assert(sp->count < sp->length);
		sp->data[sp->count] = strdup(elt);
		sp->count++;
	}
}

//removes the element from the array and swaps the empty spot with the last element in the array
//O(1)
void removeElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);
	int i;
	int a = search(sp,elt);
	
	if(a != -1){
		free(sp->data[a]);
		sp->data[a]=sp->data[--sp->count];
	}
	
}

//finds an element and returns there position, if it isnt there, return -1
//O(1)
char *findElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);
	int i  = search(sp, elt);
	if(i== -1){
		return NULL;
	}
	else{
		return sp->data[i];
	}
}


//makes a copy of the the array
//O(n)
char **getElements(SET *sp){
	assert(sp != NULL);
	int i;
	char **temp = malloc(sizeof(char *)*sp->count);
	assert(temp !=NULL );
	for(i=0;i<sp->count;i++){
		temp[i]=sp->data[i];
	}
	return temp;
}
























