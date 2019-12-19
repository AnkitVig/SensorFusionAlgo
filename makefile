CC=g++
CFLAGS = -c -std=c99
MCMODEL = -mcmodel=large
GSL = `gsl-config --cflags --libs`

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)

#TARGET TO COMPILE ALL THE TESTS TOGETHER 

main.o: src/main.c
	$(CC) -g -c $(MCMODEL)  src/main.c -o build/main.o
	
file_operations.o: src/file_operations.c
	$(CC) -g -c $(MCMODEL) src/file_operations.c -o build/file_operations.o
	
fusion_algorithm_support_degree.o: src/fusion_algorithm_support_degree.c
	$(CC) -g -c $(MCMODEL) src/fusion_algorithm_support_degree.c -o build/fusion_algorithm_support_degree.o

fusion_contribution_rate.o: src/fusion_contribution_rate.c
	$(CC) -g -c $(MCMODEL) src/fusion_contribution_rate.c -o build/fusion_contribution_rate.o

fusion_eign_value_vector_generation.o: src/fusion_eign_value_vector_generation.c
	$(CC) -g -c $(MCMODEL) src/fusion_eign_value_vector_generation.c -o build/fusion_eign_value_vector_generation.o  $(GSL) 

fusion_integrated_sd.o: src/fusion_integrated_sd.c
	$(CC) -g -c $(MCMODEL) src/fusion_integrated_sd.c -o build/fusion_integrated_sd.o					

fusion_principal_component.o: src/fusion_principal_component.c
	$(CC) -g -c $(MCMODEL) src/fusion_principal_component.c -o build/fusion_principal_component.o  $(GSL) 

fusion_threshold.o: src/fusion_threshold.c
	$(CC) -g -c $(MCMODEL) src/fusion_threshold.c -o build/fusion_threshold.o


sensor_fused_output.o: src/sensor_fused_output.c
	$(CC) -g -c $(MCMODEL) src/sensor_fused_output.c -o build/sensor_fused_output.o  $(GSL) 

sensor_invalid_range.o: src/sensor_invalid_range.c
	$(CC) -g -c $(MCMODEL) src/sensor_invalid_range.c -o build/sensor_invalid_range.o

sensor_weight_coefficient.o: src/sensor_weight_coefficient.c
	$(CC) -g -c $(MCMODEL) src/sensor_weight_coefficient.c -o build/sensor_weight_coefficient.o  $(GSL) 


tests: main.o file_operations.o fusion_algorithm_support_degree.o fusion_contribution_rate.o fusion_eign_value_vector_generation.o fusion_integrated_sd.o fusion_principal_component.o fusion_threshold.o sensor_fused_output.o sensor_invalid_range.o sensor_weight_coefficient.o
		$(CC) -g -o bin/MAIN build/main.o  build/file_operations.o build/fusion_algorithm_support_degree.o build/fusion_contribution_rate.o build/fusion_eign_value_vector_generation.o build/fusion_integrated_sd.o build/fusion_principal_component.o build/fusion_threshold.o build/sensor_fused_output.o build/sensor_invalid_range.o build/sensor_weight_coefficient.o   $(GSL) 
		

	
#TARGET TO COMPILE EVERYTHING
all: tests

#CLEAN COMMANDS
clean: 

	rm -f bin/* build/*