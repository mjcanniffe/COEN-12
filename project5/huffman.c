/* Michael Canniffe
   Dr. Atkinson 
   Project 5.   huffman.c

	Description




*/


#include "pack.h"
#include "pqueue.h"
#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define START_LENGTH 10
#define p(x) (((x)-1)/2)
#define l(x) ((x)*2+1)
#define r(x) ((x)*2+2)
typedef struct node NODE;


//comparison function that  returns 
int compare(NODE *i1, NODE *i2){
		return(i1->count< i2->count) ? -1 : (i1->count > i2->count );
	}


int main(int argc, char *argv[]){
	if(argc<1){
		printf("we dont have enough arguments.\n");
	}


//counting the characters	
	FILE *fp = fopen(argv[1], "r");
	assert(fp != NULL);
	int occurs[257] = {0};
	char Cbuff;
	while(fscanf(fp, "%c", &Cbuff) == 1){
		occurs[(int)Cbuff] +=1;
	}

//creating the priority queue	
	PQ *pq = NULL;
	pq  = createQueue(compare);
	
//assigning nodes to the priority queue	
	NODE *np;
	NODE *narray[257];
	int i;
	for(i=0; i<257; i++){
		if(occurs[i]==0){
			narray[i] = NULL;
		}
		else{
			np = malloc(sizeof(NODE));
			assert(np != NULL);
			np->parent = NULL;
			np->count  = occurs[i];
			narray[i] = np;
			addEntry(pq,np);
		}
	}
	np = malloc(sizeof(NODE));
	assert( np != NULL);
	np->count = 0;
	narray[256] = np;
	occurs[256] = 0;
	addEntry(pq,np);




//making the leaves 

	while((numEntries(pq)) > 1){
		NODE *left;
		left = removeEntry(pq);
		NODE *right;
		right = removeEntry(pq);
		
		NODE *nodeParent;
		nodeParent = malloc(sizeof(NODE));
		assert( nodeParent != NULL);
		nodeParent->count = (left->count +right->count);
		nodeParent->parent = NULL;
		left->parent= nodeParent;
		right->parent= nodeParent;
		addEntry(pq,nodeParent);
	}
	
//finds the height of the tree
	NODE *temp;
	temp = NULL;
	int j;
	for(j=0; j<257; j++){
	int count=0;
		if(narray[j] != NULL){
			temp = narray[j];

			while(temp->parent != NULL){
			
				temp = temp->parent;
				count++;
			}
			if(isprint(j)){
				printf("%c occurs %d times and uses %d bits.\n ",j,occurs[j], count );
			}
			else{
				printf("%03o occurs %d times and uses %d bits.\n ",j,occurs[j], count );
			}
			
		}
	}
	
	pack(argv[1], argv[2], narray);


	
	
	return 1;
}
