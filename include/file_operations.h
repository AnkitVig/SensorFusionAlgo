
#ifndef __FILE_OPERATIONS_H__
#define __FILE_OPERATIONS_H__
#include "../include/sensorstructure.h"


void read_from_file(char *filename);
//void collect_all_data(sensor sensor_data[],double fused_output,int size);
void write_to_output_file(int counter_outof_range[],int size_eliminated,sensor sensor_data[],double fused_output,int size,int group_no,int size_group);


#endif // __FILE_OPERATIONS_H__
