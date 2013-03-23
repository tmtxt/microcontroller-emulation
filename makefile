main: main.cpp main.h microcontroller.cpp microcontroller.h macrochippic34f42.cpp macrochippic34f42.h mopsr500.cpp mopsr500.h rotomola34hc22.cpp rotomola34hc22.h
	g++ -Wall -g microcontroller.cpp macrochippic34f42.cpp mopsr500.cpp rotomola34hc22.cpp main.cpp -o main
