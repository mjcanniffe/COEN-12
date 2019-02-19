#define MAX_WORD_LENGTH 31
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	char wordbuff[MAX_WORD_LENGTH];
	FILE *fp = fopen(argv[1],"r");
	int wordcount = 0;

	if(fp == NULL){
		return 0;
	}
	if(argc!=2){
		return 0;
	}
	while(fscanf(fp,"%s",wordbuff)==1){
			wordcount++;
	}

	printf("%d total words\n",wordcount);
}






















