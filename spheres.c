/*
	SPHERES PROGRAM
*/
//	PREPROCESSOR
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

//	CONSTANTs
#define FILE_MAX 255

//	FUNCTION DECLARATION
FILE* openFile(void);

//	M A I N
int main(void){

		//VARS
	FILE *file_pointer;	//FILE POINTER

	file_pointer = openFile();
	puts("FILE OPENED!");
	fclose(file_pointer);

}

FILE* openFile(void){

	char filename[FILE_MAX];	//string
	FILE *fp;
	
	do{
		fprintf(stdout,"Enter name of DATAFILE:\t");
		fscanf(stdin,"%s",filename);
		fp = fopen(filename,"r");
		if (fp == NULL){
			fprintf(stderr,"Error, couldnt open file. Error Num: %d\n",errno);
			perror("Description:");
		}
	}while(fp == NULL);

	return fp;

}
