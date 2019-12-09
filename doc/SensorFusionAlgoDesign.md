# Sensor Fusion Algorithm Software Design(Architecture)

## Project folder structure

```
SensorFusionAlgo
│   README.md
|   .gitignore
|   .gitmodules
│   makefile
|       
│
└───src
│   │   file_operations.c
│   │   fusion_algorithm.c
│   │   sensor_valid_range.c
│   │   main.c
|
|
└───include
│   │   file_operations.h
│   │   fusion_algorithm.h
│   │   sensor_valid_range.h
│   │   main.h
|   
|
└───build
│   │   file_operations.o
│   │   fusion_algorithm.o
│   │   sensor_valid_range.o
│   │   main.o
|   
|   
└───bin
│   │   
|
└───test
│   │   ...
|   |
│   └───files
│       │   input_file_1.txt
│   
└───lib
│   │   gsl (GNU Scientific Library)
|
└───doc
│   │   SensorFusionAlgoDesign.md
|   |   SensorFusionAlgoDesign.JPG
|   |  SensorFusionAlgoDesign.doc
|   |  SensorFusionCodeDocumentation.doc
|   |  UserGuide.doc
```

## Visual representation of the schematic design

![SensorFusionAlgo](https://github.com/shreyataneja/SensorFusionAlgo/blob/master/doc/SensorFusionAlgoDesign.jpg "SensorFusionAlgo")

## Description of the architecture

<div style="text-align: center"> 
We are purposing a fundamental architecture for the SensorFusionAlgo. The purpose of the document is to define the architecture of the SensorFusion algorithm project i.e. a brief description of the structure of files folders and behaviour of the file.
We are following the approach so that most of the calculations are separated in between different functions and c files. 
The main.c call the file input functions from file_operations.c to read the sensor data from the input file  and then the data is parsed using the parse function formatting the data in a particular data structure, then the fusion algorithm calculations are performed as per the sensor fusion algorithm and fused output is returned by calling different functions defined in fusion.c. The fused values are then validated to be in the valid range by the sensor_invalid_range.c function and the valid range of fused output is returned to main.c and the output is sent to write_file() function to write data. 

</div>
