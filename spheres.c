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
#define MAX 100			//max 100 spheres

//	STRUCTS
struct sphere{
	double radio;
	char  color; //why pointer?
};

//	FUNCTION DECLARATION
FILE* openFile(void);
int readFile(FILE* fp,struct sphere *arr_sphere);


//	M A I N
int main(void){

		//VARS
	int num_spheres;
	FILE *file_pointer;					//FILE POINTER
	struct sphere sphere_data[MAX];				//array of spheres


	file_pointer = openFile();				//OPENING FILE
	num_spheres  = readFile(file_pointer,sphere_data);	//READING FILE
	
	
	puts("FILE OPENED!");

	for(int i = 0;i < num_spheres;i++){	//verificacion

		double data;
		char color;
	
		color = sphere_data[i].color;
		data = sphere_data[i].radio;
		printf("Esfera n%d:\t%lf\t%c\n",i,data,color);
	}
	
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

int readFile(FILE* fp,struct sphere *arr_sphere){

	//we read the file, skipping the two first lines
	//should I use fgetc or fgets
	
	//Vars
	char newline;
	int end;
	int i = 0;
	bool stop = false;
	
	while(stop != true){
		newline = fgetc(fp);
		if(newline == '\n'){	//when we encounter newline, add 1
			i++;		
		}
		if(i == 2){	//if we encountered 2 newlines already, change stop.
			stop = true;
		}

	}	//we should be ready to scanf the data into the spheres array.

	i = 0;
	do{
		char clr[FILE_MAX];
		end = fscanf(fp,"%lf %s",&arr_sphere[i].radio,clr); 	// -> o . ?
		arr_sphere[i].color = clr[0];  				//== &clr[0]
		i++;
		//lf, longfloat igual a double.
	}while(end != EOF);

	fclose(fp);	//CLOSING FILE

	return (i+1);
	//CERRAR EL ARCHIVO DESDE ESTA FUNCION DESPUES DE LECTURA.
	//VERIFICAR QUE SE HA LEIDO LA DATA CORRECTAMENTE.
	
}
