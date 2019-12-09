
#ifndef __FUSION_ALGORITHM_H__
#define __FUSION_ALGORITHM_H__
#include "sensorstructure.h"

void support_degree(sensor sensor_data[],int size);
void eign_value_vector_generation (double ** degreematrix ,sensor sensor_data[], int size);
void calc_principal_component (int size,double arr_eigenvalue[],double **arr_eigenvector,double **degreematrix,sensor sensor_data[]);
void cal_contribution_rate (double arr_eigenvalue[],double ** principal_component,sensor sensor_data[],int size);
void cal_integrated_support_degree (double contribution_rate[],double sum_contribution_rate[],double ** principal_component,sensor sensor_data[],int size);
void calc_threshold(double integrated_support_degree[] , double sum_integrated_support_degree,sensor sensor_data[],int size);

#endif // __FUSION_ALGORITHM_H__
