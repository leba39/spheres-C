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
int pMenu(char *opt,int total);
void change_rad(struct sphere *esfera,double new_rad);
void change_clr(struct sphere *esfera,char new_clr);
void print_report(struct sphere *arr_sphere,int num_spheres);
double calculate_area(struct sphere esfera);
double calculate_volume(struct sphere *esfera); //just to see the diff


//	M A I N
int main(void){

		//VARS
	char opt,clean;
	int scanned;
	int num_spheres;
	int sphere_mod;
	FILE *file_pointer;					//FILE POINTER
	struct sphere sphere_data[MAX];				//array of spheres

		//INTRO
	file_pointer = openFile();				//OPENING FILE
	num_spheres  = readFile(file_pointer,sphere_data);	//READING FILE
		//MENU
	do{
		//vars
		double rad;
		char newcolor;

		sphere_mod = pMenu(&opt,num_spheres);
		switch (opt){
			case '1':
				//CHANGE RADIUS
				do{
					fprintf(stdout,"\nEnter new radius:\t");
					scanned = fscanf(stdin,"%lf",&rad);
					
					if (scanned != 1){ //if there is a matching failure
						fprintf(stderr,"Wrong sphere radius!\n");
						while((clean = fgetc(stdin)) != '\n'); //clean buffer
						//so fscanf can try again with a new clean start
					}

				}while(rad <= 0 || scanned != 1); 
				//negative-void radius non-valid.only positive.
				//rad had a previous value of a large number(E^14) so (rad <= 0)
				//alone didn't work. Two solutions. define rad before this main loop
				//to 0 or add the OR scanned != 1 condition.. 
				
				change_rad(&sphere_data[sphere_mod-1],rad);//index 0 taking care of
				break;
			case '2':
				//CHANGE COLOR
				fprintf(stdout,"\nEnter new color:\t");
				
				newcolor = fgetc(stdin);//prevents newline remainder in buffer
				if (newcolor == '\n'){ 
					newcolor = fgetc(stdin);		//reads char
					while((clean = fgetc(stdin)) != '\n'); 	//clean buffer
				}
				
				change_clr(&sphere_data[sphere_mod-1],newcolor);
				break;
			case '3':
				//PRINT REPORT
				print_report(sphere_data,num_spheres);
				break;
			case '4':
				//NORMAL EXIT
				exit(EXIT_SUCCESS);
			default:
				//FAILURE
				fprintf(stdout,"Menu Error!\n");
		}
	}while(sphere_mod != -1);
	
	//WRONG MENU. WE EXIT PROGRAM.
	fprintf(stderr,"Wrong Option!\n\a");
	exit(EXIT_FAILURE);
	
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

	fprintf(stdout,"\n\tNumber\t\t\tRadius\t\t\tColor\t\t\tArea\t\t\tVolume\n");
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
		
		fprintf(stdout,"\t%d\t\t\t%.2lf\t\t\t%s\t\t\t%.2lf\t\t\t%.2lf\n"
		,(i+1),rad,colores[num_color],area,vol);
	}
	
	//Extra data: num of spheres, %red, num Vol>215 and average area.

	fprintf(stdout,"Total number of spheres:\t%d\n",num_spheres);
	fprintf(stdout,"%.2lf %% of spheres are red.\n",(double) num_red/num_spheres*100);
	fprintf(stdout,"%d spheres have a volume over the %.2lf limit.\n",num_vol,VOL_LIM);
	fprintf(stdout,"Average area:\t%.2lf\n",total_area/num_spheres);

}

int pMenu(char *opt,int total){

	//VARs
	char str_user[FILE_MAX],clean;
	int resp,scanned;
	int i = 0;
	bool stop = false;	

	fprintf(stdout,"MENU:\n");
	fprintf(stdout,"\t1.Change sphere radius.\n");
	fprintf(stdout,"\t2.Change sphere color.\n");
	fprintf(stdout,"\t3.Print report.\n");
	fprintf(stdout,"\t4.Exit.\n");

	while (stop != true){
		//reads entire user input string until newline. we only use first char.
		str_user[i] = fgetc(stdin);	
		if (str_user[i] == '\n' || i == (FILE_MAX-1)){
			stop = true;
		}else{
			i++;
		}
		if (str_user[0] == '\n') stop = false; 
		//unless there was a remainder lonely newline in the buffer. we would ask again.
	}

	resp = 0;	//reset sphere response (somehow in the main loop, call after call it kept
			//its previous value). Ex: changeradius->1->12.5->change color->'1' already there
 
	switch (str_user[0]){
		case '1':
			*opt = '1';
			fprintf(stdout,"Which one? (Max:\t%d)\n",total);
			do{
				scanned = fscanf(stdin,"%d",&resp); //what happens if user puts char?
				if (scanned != 1){ //if there is a matching failure
					fprintf(stderr,"Wrong sphere input!\n");
					while((clean = fgetc(stdin)) != '\n'); //clean buffer
					//so fscanf can try again with a new clean start
				}
			}while(resp <= 0 || resp > total || scanned != 1);
			//scanned != 1 wasn't strictly required above because the definition resp = 0
			//made sure the while kept looping until something could be properly read into it
			//anyways it shouldn't do harm this logic condition addition.

			return resp;
		case '2':
			*opt = '2';
			fprintf(stdout,"Which one? (Max:\t%d)\n",total);
			do{
				scanned = fscanf(stdin,"%d",&resp); //I need more error control!
				if (scanned != 1){ //if there is a matching failure 
					fprintf(stderr,"Wrong sphere input!\n");
					while((clean = fgetc(stdin)) != '\n'); //clean buffer
					//so fscanf can try again
				}

			}while(resp <= 0 || resp > total || scanned != 1);

			return resp;	//we don't need breaks if we return.
		case '3':
			*opt = '3';	//no sphere needed
			return -3;	
			//random negative return int so we have no warning: control reaches
			//end of non void function 
		case '4':
			*opt = '4';	//NOMRAL EXIT
			return -4;	//same as above
		default:
			*opt = 'd';	//default
			return -1;	//wrong menu selection.Special return.

	}

}

void change_rad(struct sphere *esfera,double new_rad){
	//changes radius
	esfera->radio = new_rad;
}

void change_clr(struct sphere *esfera,char new_clr){
	//changes color
	esfera->color = new_clr;
}


/*	PROBLEMS:
 *WHY DO IT READS ONE/TWO UNEXISTANT SPHERES AT THE END?
 *In the last iteration of the do_while in readFile
 *i = 17, end = -1 already but it puts data on the struct.
 *
 *EASY FIX -> ANOTHER IF IN THE LOOP. we only write data in the struct
 *if previous 'end' isnt equal to -1 eof.
 *
 *Why isnt arr_sphere[i]->radio valid on print_report? aren't we accessing
 *trough pointers?? arr_sphere[i].radio works tho...
 *
 *How can I force the user to introduce the desired input using fscanf??
 *I made a quick fix just quitting the program if they don't put an int
 *in the pMenu and Main parts where I ask them to choose the sphere and/or
 *enter new radius.
 *
 *It seems as if the scanf won't work in a loop once called and having a 
 *matching failure. It jams the scanf on infinite loops.
 *
 *scanf leaves the non matching characters in the buffer ready for the next read!
 *Does the C language provides error checking/recovery for user input in fscanf??
 */
