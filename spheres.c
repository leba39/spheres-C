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
#define PI 3.14
#define VOL_LIM 215.0

//	STRUCTS
struct sphere{
	double radio;
	char  color; //why pointer?
};

//	FUNCTION DECLARATION
FILE* openFile(void);
int readFile(FILE* fp,struct sphere *arr_sphere);
//void change_rad(struct sphere *esfera,double new_rad);
//void change_clr(struct sphere *esfera,char *new_clr);
void print_report(struct sphere *arr_sphere,int num_spheres);
double calculate_area(struct sphere esfera);
double calculate_volume(struct sphere *esfera); //just to see the diff


//	M A I N
int main(void){

		//VARS
	int num_spheres;
	FILE *file_pointer;					//FILE POINTER
	struct sphere sphere_data[MAX];				//array of spheres


	file_pointer = openFile();				//OPENING FILE
	num_spheres  = readFile(file_pointer,sphere_data);	//READING FILE
	print_report(sphere_data,num_spheres);
	
	exit(EXIT_SUCCESS);
	
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
	puts("FILE OPENED!");
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
		double rad;
		
		end = fscanf(fp,"%lf %s",&rad,clr);
		//lf, longfloat igual a double.
		if (end != EOF){
			arr_sphere[i].radio = rad;
			arr_sphere[i].color = clr[0];  			
			i++;
		}

	}while(end != EOF);

	fclose(fp);	//CLOSING FILE

	return i;
}


double calculate_area(struct sphere esfera){
	//if I include math (link) I could use a better aproximation of PI.
		
	//vars	
	double area,radio;

	radio = esfera.radio;
	area  = 4*PI*radio*radio;

	return area;

}

double calculate_volume(struct sphere *esfera){
	//same process as before but I used pointer instead

	//vars
	double volume,radio;
	
	radio  = (esfera->radio);
	volume = (4.0/3)*PI*radio*radio*radio;	//homemade cast to get 4/3 right	
	//Could I use pow from math.h?

	return volume;
}

void print_report(struct sphere *arr_sphere,int num_spheres){
	//generates updated report of the sphere data as ruled in rules.txt
	
	//VARs
	int num_color;
	int num_red = 0;
	int num_vol = 0;
	double rad,area,vol;
	double total_area = 0.0;
	char color;
	char *colores[] = {"Blue","Yellow","Red","Pink","NoColor"};

	fprintf(stdout,"\n\tNumber\t\tRadius\t\tColor\t\tArea\t\tVolume\n");
	for(int i = 0;i < num_spheres;i++){
		
		//getters
		color  = arr_sphere[i].color;	//WHY ISNT '->' VALID HERE  ?????
		rad    = arr_sphere[i].radio;			//SEE FUNCTION DECLARATION
		area   = calculate_area(arr_sphere[i]);		//content of sphere[i]
		vol = calculate_volume(&arr_sphere[i]);		//address of sphere[i]  
		//info
		total_area += area;
		if (vol > VOL_LIM) num_vol++;
	
		switch (color){
			case 'b':
				num_color = 0;
				break;
			case 'y':
				num_color = 1;
				break;
			case 'r':
				num_color = 2;
				num_red++;
				break;
			case 'p':
				num_color = 3;
				break;
			default:
				num_color = 4;
		}
		
		fprintf(stdout,"\t%d\t\t%.2lf\t\t%s\t\t%.2lf\t\t%.2lf\n"
		,(i+1),rad,colores[num_color],area,vol);
	}
	
	//Extra data: num of spheres, %red, num Vol>215 and average area.

	fprintf(stdout,"Total number of spheres:\t%d\n",num_spheres);
	fprintf(stdout,"%.2lf %% of spheres are red.\n",(double) num_red/num_spheres*100);
	fprintf(stdout,"%d spheres have a volume over the %.2lf limit.\n",num_vol,VOL_LIM);
	fprintf(stdout,"Average area:\t%.2lf\n",total_area/num_spheres);

}



/*	PROBLEMS:
 *WHY DO IT READS ONE/TWO UNEXISTANT SPHERES AT THE END?
 *In the last iteration of the do_while in readFile
 *i = 17, end = -1 already but it puts data on the struct.
 *
 *EASY FIX -> ANOTHER IF IN THE LOOP. we only write data in the struct
 *if previously end isnt equal to -1 eof.
 *
 *Why isnt arr_sphere[i]->radio valid on print_report? aren't we accessing
 *trough pointers?? arr_sphere[i].radio works tho...
 */
