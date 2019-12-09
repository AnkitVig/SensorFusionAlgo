#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/sensor_invalid_range.h"
#include "../include/sensorstructure.h"
#include "../include/file_operations.h"


int itr,var;
double *all_fused_outputs = (double *)malloc( (100) * sizeof(double));
sensor *sensor_final;
int size_final;

void detect_out_of_range_sensor(double integrated_support_degree[],double sum_integrated_support_degree,sensor sensor_data[],int size,double X_Thresh){
	int *counter_outof_range = (int *)malloc(size * sizeof(int));
	int i;
	int size_eliminated=0;
	for(i=0;i<size;i++)	{
		if(abs(integrated_support_degree[i])<X_Thresh)	{
			counter_outof_range[size_eliminated++]=i;
		}
		else
		continue;
	
	}
	for (i=0;i<size_eliminated;i++)
	printf("eliminated sensors  = %d\n",counter_outof_range[i]);	
	calc_weight_coefficient(counter_outof_range,size_eliminated,integrated_support_degree, sum_integrated_support_degree,sensor_data,size);
} 

void calc_weight_coefficient(int counter_outof_range[],int size_eliminated,double integrated_support_degree[],double sum_integrated_support_degree,sensor sensor_data[],int size){
int i,k;
double *weight_coefficient = (double *)malloc(size * sizeof(double));
for(i=0;i<size;i++)
{	for(k=0;k<size_eliminated;k++)
	{
	if(i != counter_outof_range[k])
	weight_coefficient[i]=integrated_support_degree[i]/sum_integrated_support_degree;	
	
	}

}
valid_fused_output(counter_outof_range,size_eliminated,weight_coefficient, sensor_data,size);
}

void valid_fused_output(int counter_outof_range[],int size_eliminated,double weight_coefficient[],sensor sensor_data[],int size){
	int i;
	double fused_output;
	for(i=0;i<size;i++)
	{	
		fused_output += weight_coefficient[i] * sensor_data[i].value;
	}
	printf("Fused output = %g\n",fused_output);
		itr++;
//	printf("%d\n",itr);
	size_final+=size;
	write_to_output_file(counter_outof_range,size_eliminated,sensor_data,fused_output,size,itr,size_final);                                       
}


