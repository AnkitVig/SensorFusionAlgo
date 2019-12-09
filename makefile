CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I ../../cadmium/include
INCLUDEDESTIMES=-I ../../DESTimes/include


#TARGET TO COMPILE ALL THE TESTS TOGETHER (NOT SIMULATOR)
sensor.o: Sensor_Ankit.c
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) Sensor_Ankit.c -o build/sensor.o
	
										
tests: sensor.o 
		$(CC) -g -o bin/Sensor build/sensor.o		

	
#TARGET TO COMPILE ONLY ABP SIMULATOR
simulator: sensor.o  
	$(CC) -g -o bin/Sensor build/sensor.o
	
#TARGET TO COMPILE EVERYTHING (ABP SIMULATOR + TESTS TOGETHER)
all: simulator tests

#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*