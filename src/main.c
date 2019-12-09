#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/file_operations.h"
#include "../include/sensor_invalid_range.h"
#include "../include/sensorstructure.h"

int main(int argc, char ** argv) {

    if (argc < 2) {
       printf("Wrong parameters entered. The program must be invoked as follow:");
       printf (" path of the input file %s",argv[0]  );
        return 1; 
    }
  
    char * i_input =  argv[1];
	printf (" Input file is : %s",i_input  );
	read_from_file(i_input);
//	double *p;
//	p=getfusedoutput();

//	int size_fusedvalues=return_itr();
//	int size_sensor=return_size();
//	for(int i=0;i<size_fusedvalues;i++)
//	printf("%g\n",p[i]);
	
//	sensor *sens;
//	sens = returnsensors();

//	for(int i=0;i<size_sensor;i++)
//	{
//	printf("%g\n",sens[i].value);			
//	}
//	free(p);
//	free(sens);
	//write_to_output_file(i_input);
	return 0;
	}
