# Specify pre-defined variables to change the build process
CXXFLAGS = -Wall -g

# Specify the main executable
EXEC = main

# Specify *.o units here, but not the .cpp file with main()
OBJS = microcontroller.o macrochippic32f42.o mopsr500.o rotamola34hc22.o microcontrollerfactory.o

# all target
.PHONY: all
all: $(EXEC)

# all target depends on this
$(EXEC): $(EXEC).cpp $(OBJS)

# target for each cpp file and its dependency
microcontroller.o: microcontroller.h
macrochippic32f42.o: macrochippic32f42.h microcontroller.h
mopsr500.o: mopsr500.h microcontroller.h
rotamola34hc22.o: rotamola34hc22.h microcontroller.h
microcontrollerfactory.o: microcontrollerfactory.h microcontroller.h mopsr500.h rotamola34hc22.h macrochippic32f42.h

.PHONY: clean
clean:
	$(RM) -r $(OBJS) $(EXEC) $(EXEC).dSYM
