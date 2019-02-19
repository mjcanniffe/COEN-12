#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"




struct set{
	int count;
	int length;
	char **data;
};

typedef struct set SET;

//this function creates an empty set for data to be stored in
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
//this function frees the set and goes through the array of data and frees them one by one 
//O(n)
void destroySet(SET *sp){
	int i;
	for(i=0; i < sp->count; i++){
		free(sp->data[i]);
	}
	free(sp->data);
	free(sp);
}

//this is a binaray search function that returns wether or not the character is in the array and if it isn't, then it returns the position where it should be placed
//O(logn)
static int search(SET *sp, char *elt, bool *found){
	assert(sp != NULL || elt != NULL);
	int lo,hi,mid,diff;
	lo = 0;
	hi = sp->count-1;
	while(lo<=hi){
		mid = (lo+hi)/2;
		diff= strcmp(elt,sp->data[mid]);
		if(diff<0){
			hi = mid-1;
		}
		else if(diff>0){
			lo = mid+1;
		}
		else{
			*found = true;
			return mid;
		}
	}
	*found = false;
	return lo;
}


//reutrns the number of elements
//O(1)
int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;
}



//adds element in the correct position
//O(n)
void addElement(SET *sp, char *elt){	
	assert(sp != NULL || elt != NULL);
	int i;
	bool found;
	int a;
	printf("%s",elt);
	fflush(stdout);
	a = search(sp, elt, &found);
	printf("%d\n",a);
	fflush(stdout);
	if(!found){
		for(i=sp->count;i>a;i--){
			sp->data[i]=sp->data[i-1];
		}
	elt= strdup(elt);
	assert(elt!=NULL);
	sp->data[a]=elt;
	sp->count++;
	
	
	}
}

//removes and element and shifts every other element up
//O(n)
void removeElement(SET *sp, char *elt){
	assert(sp != NULL || elt != NULL);
	int i;
	bool found;	
	int a = search(sp,elt,&found);
	if(found){
		free(sp->data[a]);
		for(i=a+1; i<sp->count;i++){
			sp->data[i-1]=sp->data[i];
		}
	}
	sp->count--;
}

//finds and element and returns the position
//O(1)
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


//makes a shallow copy of the array
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
























