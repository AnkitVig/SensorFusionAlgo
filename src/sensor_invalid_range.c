#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/sensor_weight_coefficient.h"

/** 
	* detecting and eliminating out of range sensors 
	* @param integrated_support_degree
	* @param sum_integrated_support_degree
	* @param sensor_data
	* @param size
	* @param X_Thresh
*/

void detect_out_of_range_sensor(double *integrated_support_degree,double sum_integrated_support_degree,sensor *sensor_data,int size,double X_Thresh){
	int *counter_outof_range = (int *)malloc(size * sizeof(int));
	int i;
	int size_eliminated=0;
	for(i=0;i<size;i++){
		if(abs(integrated_support_degree[i])<X_Thresh){
			counter_outof_range[size_eliminated++]=i;
		}
		else
		continue;
	}
	calc_weight_coefficient(counter_outof_range,size_eliminated,integrated_support_degree, sum_integrated_support_degree,sensor_data,size);
} 



