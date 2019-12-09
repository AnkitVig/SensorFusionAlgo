#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/file_operations.h"
#include "../include/fusion_algorithm.h"
#include "../include/sensorstructure.h"
#define LSIZ 500
#define RSIZ 1000
#define LINESTRUCT 500
char *filenameglobal =(char *) malloc(100);
int totallines;

void read_from_file(char *filename) {

   	
		char line[RSIZ][LSIZ];
		char line_temp[RSIZ][LSIZ];
		char fname[20];
		sensor *sen_val ;
		sen_val = (sensor *) malloc(LINESTRUCT * sizeof(sensor));
		strcpy(filenameglobal,filename);		
		FILE *fptr = NULL;
		int i = 0,j=0,k=0,k1=0;
		int total = 0,count=0;

		fptr = fopen(filename, "r");
			while(fgets(line[i], LSIZ, fptr))
				{
					line[i][strlen(line[i]) - 1] = '\0';
					i++;
				}
		char timezone[50];
		strcpy(timezone,line[0]);
		strtok(timezone, ",");
		total = i;
		printf("\n val of total :%d",total);
		totallines=total;
		printf("\n The content of the file %s  are : \n",filename);
		int len = strlen(filenameglobal);
   		 filenameglobal[len-4] = '\0';
		printf("%s\n",strcat(filenameglobal,"_output.csv"));
		while(j<total)
			{		
				char temp2[50] ;
				strcpy(temp2,line[j]);
				strtok(temp2, ",");
 
				if (strcmp (timezone,temp2)==0)
				{ 	k=0;
					for(i = count; i < total; i++)
						{ 	char temp[50] ;
							strcpy(temp,line[i]);
							strtok(temp, ",");
 
							if (strcmp (timezone,temp)==0)
							{
   
								char* token = strtok(line[i], ",");
     
							   strcpy(sen_val[k].time, token) ;
							   token = strtok(NULL, ",") ;
							   strcpy(sen_val[k].sensor_name, token) ;
							   token = strtok(NULL, "\n") ;
							   sen_val[k].value = atof(token) ;
								k++;
								count++;
							}
							else
							{
								strcpy(timezone,line[i]);
								strtok(timezone, ",");
								break;
							}

						}
							printf("\n .........");
				support_degree(sen_val,k);
				}
				j=i;
				}
				
	}

	
void write_to_output_file(int counter_outof_range[],int size_eliminated,sensor sensor_data[],double fused_output,int size,int group_no,int size_group){
	FILE *fptr = NULL;
	int i;
	//printf("%s",filenameglobal);
	char fileop[20]="../my_output.csv";
	

	for(int j=0;j<size_eliminated;j++)
	printf("%d\n",counter_outof_range[j]);
	if((group_no-1) == 0){
		 if((fptr = fopen(filenameglobal, "w"))==NULL) {
		    printf("Cannot open file.\n");
  			}
  	 	fprintf(fptr, "%s %g  \n", "Fused Output = ", fused_output);
  	 	fprintf(fptr, "%s\n", "Sensor Values =\nTime\tName\tValue");
  	 	for(i=0;i<size;i++){
			for(int j=0;j<size_eliminated;j++)
			if(i!=counter_outof_range[j])		
  	 		fprintf(fptr, "%s\t%s\t%g\n", sensor_data[i].time,sensor_data[i].sensor_name,sensor_data[i].value);
		   }
		}

	else{
	fptr = fopen(filenameglobal, "a");	
	 fprintf(fptr, "%s %g  \n", "Fused Output = ", fused_output);
	 fprintf(fptr, "%s\n ", "Sensor Values =\nTime\tName\tValue");
	 for(i=0;i<size;i++){
		for(int j=0;j<size_eliminated;j++)
			if(i!=counter_outof_range[j])		
  	 		fprintf(fptr, "%s\t%s\t%g\n", sensor_data[i].time,sensor_data[i].sensor_name,sensor_data[i].value);
		   }
	}
fclose(fptr);
	//fptr = fopen(filename, "r");
}
	
	
