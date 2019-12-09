#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_eigen.h>


#include "../include/sensorstructure.h"
#include "../include/fusion_algorithm.h"
#include "../include/sensor_invalid_range.h"

void support_degree(sensor sensor_data[],int size)
{
int i,j;

    //initialize 2-D array for support degree matrix
	double **degreematrix ;
	degreematrix = (double **)malloc(sizeof(double *) * size); 
//	 double degreematrix[size][size] ;
    for (i=0; i<size; i++) 
         degreematrix[i] = (double *)malloc( sizeof(double) * size); 

    for(i = 0; i < size;i++)
    {
        for (j=0; j< size; j++)
        {
            double d =abs(sensor_data[i].value - sensor_data[j].value);
        //   printf(" d is %lf\n",d);
            degreematrix[i][j] = exp(-d);
        //   printf("i:%d j:%d degreematrix:%lf\n",i,j,degreematrix[i][j]);
        }
    }
   eign_value_vector_generation(degreematrix,sensor_data,size);
   
 }
   
   
   
void eign_value_vector_generation(double **degreematrix,sensor sensor_data[], int size)
{	int sizeforarray = size*size;
	double *data=(double *)malloc(sizeforarray * sizeof(double));
	int i=0 , j=0 , k=0;

	for(i = 0; i < size;i++)
    {
        for (j=0; j< size; j++)
        { //data[k++]=*((degreematrix+i*size) + j);
		data[k++]= degreematrix[i][j];
		// printf("data %lf",data[--k]);
        //   printf("i:%d j:%d degreematrix:%lf\n",i,j,degreematrix[i][j]);
        }
    }
	gsl_matrix_view m   = gsl_matrix_view_array(data, size, size);

	gsl_vector *eval = gsl_vector_alloc (size);
	gsl_matrix *evec = gsl_matrix_alloc (size, size);

	gsl_eigen_symmv_workspace *w =  gsl_eigen_symmv_alloc (size);
	 
	gsl_eigen_symmv (&m.matrix, eval, evec, w);

	gsl_eigen_symmv_free(w);

	gsl_eigen_symmv_sort (eval, evec,
							GSL_EIGEN_SORT_ABS_DESC);
	 
 
	   double *arr_eigenvalue = (double *)malloc( (size) * sizeof(double));
	   double **arr_eigenvector = (double **)malloc(size * sizeof(double *)); 
		 
		for (i=0; i<size; i++) 
			 arr_eigenvector[i] = (double *)malloc(size * sizeof(double)); 

		for (i = 0; i < size; i++)
		  {
			double eval_i = gsl_vector_get(eval, i);
		   
			gsl_vector_view evec_i = gsl_matrix_column(evec, i);
			arr_eigenvalue[i]=eval_i;
	//	    printf("eigenvalue = %g\n", eval_i);
	//	printf("eigenvector = \n");
	//	   gsl_vector_fprintf(stdout,&evec_i.vector, "%g");
		   for (j = 0; j < size; j++)
				arr_eigenvector[i][j] = gsl_vector_get(&evec_i.vector,j);
		//\\ printf("""""""""""""""""""""""""""""""\n%g\n",gsl_vector_get(&evec_i.vector,j)) ;
 }

  calc_principal_component (size,arr_eigenvalue,arr_eigenvector,degreematrix,sensor_data);
 
}
	void calc_principal_component  (int size,double arr_eigenvalue[],double **arr_eigenvector,double **degreematrix,sensor sensor_data[]){
		int i,j;
	//	printf("in function calc_principal_component \n");
	

		double **principal_component = (double **)malloc(size * sizeof(double *));
		for (i=0; i<size; i++) 
			principal_component[i] = (double *)malloc(size * sizeof(double)); 

		 double sum;
		
			for(int k=0;k<size;k++)
				for (i = 0;  i < size; i++){
					for (j = 0; j < size; j++){
					
						principal_component[k][i] += arr_eigenvector [k][j] * degreematrix [i][j];;
						//printf("\n Eigenvalue= \  %g\t\n",arr_eigenvalue[j]);
						 //printf("\n EigenVector=    %g\t\n",x);
					 
						}

					}
		
			for (i = 0;  i < size; i++){
				for (j = 0; j < size; j++){
					printf("Principal compnent %d    %d :  %g\n\t",i,j, principal_component[i][j]);
				//	printf("\n");
				}
			}
		cal_contribution_rate(arr_eigenvalue,principal_component,sensor_data,size);
}

void cal_contribution_rate(double arr_eigenvalue[],double ** principal_component,sensor sensor_data[],int size){
		double *contribution_rate = (double *)malloc( (size) * sizeof(double));
			double *sum_contribution_rate =  (double *)malloc( (size) * sizeof(double));
			int r,c;
			double egval_sum = 0;
			for(c = 0;c<size;c++){
				egval_sum = egval_sum + arr_eigenvalue[c];
			   
			}
			//printf("egval_sum final : %g \t\n ",egval_sum);
			for(r = 0;r<size;r++){
			// printf(" Eigen Values %g \t\n",arr_eigenvalue[r]);
			// printf("egval_sum : %g \t\n ",egval_sum);
			double s = 0;
			s = arr_eigenvalue[r];
			contribution_rate[r] =  (s)/(egval_sum);
				printf("contribution_rate\t: %lg\n", contribution_rate[r]);
		}
			double sum=0;
			for(r = 0;r<size;r++){
				sum += contribution_rate[r];
			  sum_contribution_rate[r] = sum ;
			  
			  printf("sum_contribution_rate\t: %lg\n", sum_contribution_rate[r]);
			}
	cal_integrated_support_degree(contribution_rate,sum_contribution_rate, principal_component,sensor_data, size);
}

void cal_integrated_support_degree(double contribution_rate[], double sum_contribution_rate[],double ** principal_component,sensor sensor_data[],int size){
	double *integrated_support_degree = (double *)malloc( (size) * sizeof(double));
	double sum_integrated_support_degree;
	int counter;
	 int i,j;
	for(i=0;i<size;i++)
	{
		if(sum_contribution_rate[i]*100 <=85)
		counter ++;
		else
		break;
	}
	printf("\n%d\n",counter);
    double **calc_integrated_support =  (double **)malloc(size * sizeof(double *));
		for (i=0; i<size; i++) 
			calc_integrated_support[i] = (double *)malloc(size * sizeof(double)); 
   
    
     for(i = 0; i < counter;i++)
    {
        for (j=0; j< size; j++)
        {
       
        calc_integrated_support[i][j] = principal_component[i][j] * contribution_rate[i];
       printf(" integrated_support_degree: %lg \t\n", calc_integrated_support[i][j]);
        }
       
    }
   

double sum;
   for(i = 0; i < size;i++)
    {  sum = 0;
        for (j=0; j< counter; j++)
        {
       
        sum += calc_integrated_support[j][i];
       
        }
      // printf(" sum of columns of integrated_support_degree: %lg \t\n", sum);
    	integrated_support_degree[i]=sum;
	}
   
      //printf(" sum integrated_support_degree: %lg \t\n", sum_integrated_support_degree);
    // printf(" mean integrated_support_degree: %lg \t\n", sum_integrated_support_degree/size);

 	for(i=0;i<size;i++)
 	 printf(" array of columns of integrated_support_degree: %lg \t\n", 	integrated_support_degree[i]);
 	 
 	 for(i=0;i<size;i++)
 	 {
 	 	sum_integrated_support_degree +=integrated_support_degree[i];
	  }
	  
	  printf(" SUM of integrated support degree: %lg \t\n", sum_integrated_support_degree);
   
  calc_threshold(integrated_support_degree,sum_integrated_support_degree,sensor_data,size);

}


void calc_threshold(double integrated_support_degree[] , double sum_integrated_support_degree,sensor sensor_data[],int size)
{
 	double X_Thresh ;
   
    X_Thresh = abs(sum_integrated_support_degree/size)*(0.7);
	printf(" Threshold: %lf \t\n", X_Thresh);	
	detect_out_of_range_sensor(integrated_support_degree,sum_integrated_support_degree,sensor_data,size,X_Thresh);
}

