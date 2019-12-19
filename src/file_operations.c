#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "../include/fusion_algorithm_support_degree.h"
/** 
	*line size
	*number of lines
*/
#define LSIZ 500													
#define RSIZ 1000													
#define LINESTRUCT 500

/** 
	* includes all the file operations for reading and writting the file
*/

char *filenameglobal =(char *) malloc(100);
/**
	* read file functions 
*/


void read_from_file(char *filename){   							
    char line[RSIZ][LSIZ];
	char line_temp[RSIZ][LSIZ];
	char fname[20] ;
	sensor *sen_val ;
	sen_val = (sensor *) malloc(LINESTRUCT * sizeof(sensor));
	strcpy(filenameglobal,filename);		
	FILE *fptr = NULL;
	int i = 0,j=0,k=0,k1=0;
	int total = 0,count=0;
	int begin, end, count_file = 0;
	/**
		* Open the output file in read mode
	*/	
	
	if((fptr = fopen(filename, "r"))==NULL){					
			printf("Cannot open file.\n");
  		}							
	while(fgets(line[i], LSIZ, fptr)){
		line[i][strlen(line[i]) - 1] = '\0';
		i++;
	}
	char timezone[50];
	strcpy(timezone,line[0]);
	strtok(timezone, ",");
	total = i;		
	int len = strlen(filenameglobal);
   	filenameglobal[len-4] = '\0';
	/**
		* name the output file as inputfilename_output.csv 
	*/
	
	strcat(filenameglobal,"_output.csv");		
	
	while(j<total){		
		char temp2[50] ;
		strcpy(temp2,line[j]);
		strtok(temp2, ",");
 		if (strcmp (timezone,temp2)==0){
			k=0;
			for(i = count; i < total; i++){
				char temp[50] ;
				strcpy(temp,line[i]);
				strtok(temp, ",");
				if (strcmp (timezone,temp)==0){
					/**
						* reading the files and store data in sensor structure for 1 group of sensor at a time
					*/
					char* token = strtok(line[i], ",");     
					strcpy(sen_val[k].time, token) ;
					token = strtok(NULL, ",") ;
					strcpy(sen_val[k].sensor_name, token) ;
					token = strtok(NULL, "\n") ;
					sen_val[k].value = atof(token) ;
					k++;
					count++;
				}
				else{
					strcpy(timezone,line[i]);
					strtok(timezone, ",");
					break;
				}
			}							
		support_degree(sen_val,k);
	}
	j=i;
	}
	fclose(fptr);		
}

	
void write_to_output_file(int counter_outof_range[],int size_eliminated,sensor sensor_data[],double fused_output,int size,int group_no){	
	/**
		* function to write results 
		* @param counter_outof_range
		* @param size_eliminated
		* @param sensor_data
		* @param fused_output
		* @param size
		* @param group_no
		* @return type void
	*/
	FILE *fptr = NULL;
	int i,j,counter_range=0;

	
	if((group_no-1) == 0){
			/**
				* when you start writing the output fie
			*/
		if((fptr = fopen(filenameglobal, "w"))==NULL){
			/** 
				* Open the output file in write mode for group 1 of sensors
			*/	
			printf("Cannot open file.\n");
  		}
  	fprintf(fptr, "%s %g  \n", "Fused Output = ", fused_output);
  	fprintf(fptr, "%s\n", "Sensor Values =\nTime,Name,Value");
  	for(i=0;i<size;i++){					
			if(i!=counter_outof_range[j]){								
				fprintf(fptr, "%s,%s,%g\n", sensor_data[i].time,sensor_data[i].sensor_name,sensor_data[i].value);
			}
			else
			j++;		  	 		
		}
	fprintf(fptr, "%s\n", "Eliminated Sensors =\nTime,Name,Value");	
	for(int j=0;j<size_eliminated;j++){	
			counter_range=counter_outof_range[j];							
			fprintf(fptr, "%s,%s,%g\n", sensor_data[counter_range].time,sensor_data[counter_range].sensor_name,sensor_data[counter_range].value);	  	 		
		}
					
	}
	else{
		j=0,counter_range=0;
		fptr = fopen(filenameglobal, "a");								
		/** 
			* Open the output file in append mode for all other groups of sensors
		*/	
		fprintf(fptr, "%s %g  \n", "Fused Output = ", fused_output);
		fprintf(fptr, "%s\n ", "Sensor Values =\nTime,Name,Value");
	  	for(i=0;i<size;i++){					
			if(i!=counter_outof_range[j]){								
				fprintf(fptr, "%s,%s,%g\n", sensor_data[i].time,sensor_data[i].sensor_name,sensor_data[i].value);
			}
			else
			j++;		  	 		
		}
		fprintf(fptr, "%s\n", "Eliminated Sensors =\nTime,Name,Value");	
		for(int j=0;j<size_eliminated;j++){	
			counter_range=counter_outof_range[j];							
				fprintf(fptr, "%s,%s,%g\n", sensor_data[counter_range].time,sensor_data[counter_range].sensor_name,sensor_data[counter_range].value);	  	 		
		}
		
	}
fclose(fptr);
}
	
	
