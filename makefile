# MACROS

LINKER = g++
LINKERPARAMS =

COMPILER = g++
COMPILERPARAMS = -c

SOURCE = src
LIBPOLO = $(SOURCE)/libpolo
TARGET = target
OBJ = $(TARGET)/obj

EXECUTABLE = $(TARGET)/oscilloscope
OBJECTS = $(addprefix $(OBJ)/, $(addsuffix .o, main Configuration State Samples Touch FPGA Display polo))
LIBRARIES = $(addprefix -l, glut)

# LINKING

$(EXECUTABLE) : $(OBJECTS)
	$(LINKER) $(LINKERPARAMS) $(OBJECTS) $(LIBRARIES) -o $(EXECUTABLE) 

# COMPILING

$(OBJ)/main.o : $(SOURCE)/main.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/main.cpp -I $(SOURCE) -I $(LIBPOLO) -o $(OBJ)/main.o

$(OBJ)/Configuration.o : $(SOURCE)/Configuration.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Configuration.cpp -I $(SOURCE) -o $(OBJ)/Configuration.o

$(OBJ)/State.o : $(SOURCE)/State.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/State.cpp -I $(SOURCE) -o $(OBJ)/State.o

$(OBJ)/Samples.o : $(SOURCE)/Samples.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Samples.cpp -I $(SOURCE) -o $(OBJ)/Samples.o

$(OBJ)/Touch.o : $(SOURCE)/Touch.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Touch.cpp -I $(SOURCE) -o $(OBJ)/Touch.o

$(OBJ)/FPGA.o : $(SOURCE)/FPGA.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/FPGA.cpp -I $(SOURCE) -o $(OBJ)/FPGA.o

$(OBJ)/Display.o : $(SOURCE)/Display.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Display.cpp -I $(SOURCE) -I $(LIBPOLO) -o $(OBJ)/Display.o

$(OBJ)/polo.o : $(LIBPOLO)/polo.c
	$(COMPILER) $(COMPILERPARAMS) $(LIBPOLO)/polo.c -I $(LIBPOLO) -o $(OBJ)/polo.o

# SOURCES

$(SOURCE)/main.cpp : $(SOURCE)/Configuration.hpp $(SOURCE)/State.hpp $(SOURCE)/Samples.hpp $(SOURCE)/Touch.hpp $(SOURCE)/FPGA.hpp $(SOURCE)/Display.hpp $(LIBPOLO)/polo.h

$(SOURCE)/Configuration.cpp : $(SOURCE)/Configuration.hpp

$(SOURCE)/State.cpp : $(SOURCE)/State.hpp

$(SOURCE)/Samples.cpp : $(SOURCE)/Samples.hpp

$(SOURCE)/Touch.cpp : $(SOURCE)/Touch.hpp

$(SOURCE)/FPGA.cpp : $(SOURCE)/FPGA.hpp

$(SOURCE)/Display.cpp : $(SOURCE)/Display.hpp $(LIBPOLO)/polo.h

$(LIBPOLO)/polo.c : $(LIBPOLO)/polo.h

# HEADERS

$(SOURCE)/Configuration.hpp :

$(SOURCE)/State.hpp : $(SOURCE)/Configuration.hpp

$(SOURCE)/Samples.hpp : $(SOURCE)/Configuration.hpp

$(SOURCE)/Touch.hpp : $(SOURCE)/Configuration.hpp $(SOURCE)/State.hpp $(SOURCE)/Samples.hpp

$(SOURCE)/FPGA.hpp : $(SOURCE)/Configuration.hpp $(SOURCE)/Samples.hpp

$(SOURCE)/Display.hpp : $(SOURCE)/Configuration.hpp $(SOURCE)/State.hpp $(SOURCE)/Samples.hpp

$(LIBPOLO)/polo.h :

# MAKING DIRECTORIES

$(OBJECTS) : | $(OBJ)

$(OBJ) : | $(TARGET)
	mkdir $(OBJ)

$(TARGET) :
	mkdir $(TARGET)

#CLEANING

clean :
	rm -r $(TARGET)

