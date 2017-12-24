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

//	M A I N
int main(void){

	char filename[FILE_MAX];	//strings
	FILE *file_pointer;		//FILE POINTER

	do{
		fprintf(stdout,"Enter name of DATAFILE:\t");
		fscanf(stdin,"%s",filename);
		file_pointer = fopen(filename,"r");
		if (file_pointer == NULL){
			fprintf(stderr,"Error, file not open.\n");
			perror("Description:");
		}

	}while(file_pointer == NULL);

	

	puts("FILE OPENED!");
	fclose(file_pointer);
}

