main: main.cpp main.h microcontroller.cpp microcontroller.h macrochippic32f42.cpp macrochippic32f42.h mopsr500.cpp mopsr500.h rotamola34hc22.cpp rotamola34hc22.h
	g++ -Wall -g microcontroller.cpp macrochippic32f42.cpp mopsr500.cpp rotamola34hc22.cpp main.cpp -o main
