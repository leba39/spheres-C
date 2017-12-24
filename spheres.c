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
void openFile(FILE *fp);

//	M A I N
int main(void){

		//VARS
	FILE *file_pointer = NULL;	//FILE POINTER
	

	openFile(file_pointer);
	puts("FILE OPENED!");
	fclose(file_pointer);
}

void openFile(FILE *fp){

	char filename[FILE_MAX];	//string	
	do{
		fprintf(stdout,"Enter name of DATAFILE:\t");
		fscanf(stdin,"%s",filename);
		fp = fopen(filename,"r");
		if (fp == NULL){
			fprintf(stderr,"Error, file not open.\n");
			perror("Description:");
		}
	}while(fp == NULL);
}
