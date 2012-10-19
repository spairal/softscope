# MACROS

LINKER = g++
LINKERPARAMS =
COMPILER = g++
COMPILERPARAMS = -c
OUTPUT = -o
INCLUDE = -I
TOUCH = touch
MAKEDIRECTORY = mkdir
REMOVE = rm
REMOVEPARAMS = -r
SOURCE = src
LIBPOLO = $(SOURCE)/libpolo
TARGET = target
OBJ = $(TARGET)/obj
EXECUTABLE = $(TARGET)/oscilloscope
OBJECTS = $(addprefix $(OBJ)/, $(addsuffix .o, main Configuration State Samples Touch FPGA Display polo))
LIBRARIES = $(addprefix -l, glut)

# LINKING

$(EXECUTABLE) : $(OBJECTS)
	$(LINKER) $(LINKERPARAMS) $(OBJECTS) $(LIBRARIES) $(OUTPUT) $(EXECUTABLE) 

# COMPILING

$(OBJ)/main.o : $(SOURCE)/main.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/main.cpp $(INCLUDE) $(SOURCE) $(INCLUDE) $(LIBPOLO) $(OUTPUT) $(OBJ)/main.o

$(OBJ)/Configuration.o : $(SOURCE)/Configuration.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Configuration.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/Configuration.o

$(OBJ)/State.o : $(SOURCE)/State.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/State.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/State.o

$(OBJ)/Samples.o : $(SOURCE)/Samples.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Samples.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/Samples.o

$(OBJ)/Touch.o : $(SOURCE)/Touch.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Touch.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/Touch.o

$(OBJ)/FPGA.o : $(SOURCE)/FPGA.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/FPGA.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/FPGA.o

$(OBJ)/Display.o : $(SOURCE)/Display.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Display.cpp $(INCLUDE) $(SOURCE) $(INCLUDE) $(LIBPOLO) $(OUTPUT) $(OBJ)/Display.o

$(OBJ)/polo.o : $(LIBPOLO)/polo.c
	$(COMPILER) $(COMPILERPARAMS) $(LIBPOLO)/polo.c $(INCLUDE) $(LIBPOLO) $(OUTPUT) $(OBJ)/polo.o

# SOURCES

$(SOURCE)/main.cpp : $(SOURCE)/Configuration.hpp $(SOURCE)/State.hpp $(SOURCE)/Samples.hpp $(SOURCE)/Touch.hpp $(SOURCE)/FPGA.hpp $(SOURCE)/Display.hpp $(LIBPOLO)/polo.h
	$(TOUCH) $(SOURCE)/main.cpp

$(SOURCE)/Configuration.cpp : $(SOURCE)/Configuration.hpp
	$(TOUCH) $(SOURCE)/Configuration.cpp

$(SOURCE)/State.cpp : $(SOURCE)/State.hpp
	$(TOUCH) $(SOURCE)/State.cpp

$(SOURCE)/Samples.cpp : $(SOURCE)/Samples.hpp
	$(TOUCH) $(SOURCE)/Samples.cpp

$(SOURCE)/Touch.cpp : $(SOURCE)/Touch.hpp
	$(TOUCH) $(SOURCE)/Touch.cpp

$(SOURCE)/FPGA.cpp : $(SOURCE)/FPGA.hpp
	$(TOUCH) $(SOURCE)/FPGA.cpp

$(SOURCE)/Display.cpp : $(SOURCE)/Display.hpp $(LIBPOLO)/polo.h
	$(TOUCH) $(SOURCE)/Display.cpp

$(LIBPOLO)/polo.c : $(LIBPOLO)/polo.h
	$(TOUCH) $(LIBPOLO)/polo.c

# HEADERS

$(SOURCE)/Configuration.hpp :
	$(TOUCH) $(SOURCE)/Configuration.hpp

$(SOURCE)/State.hpp : $(SOURCE)/Configuration.hpp
	$(TOUCH) $(SOURCE)/State.hpp

$(SOURCE)/Samples.hpp : $(SOURCE)/Configuration.hpp
	$(TOUCH) $(SOURCE)/Samples.hpp

$(SOURCE)/Touch.hpp : $(SOURCE)/Configuration.hpp $(SOURCE)/State.hpp $(SOURCE)/Samples.hpp
	$(TOUCH) $(SOURCE)/Touch.hpp

$(SOURCE)/FPGA.hpp : $(SOURCE)/Configuration.hpp $(SOURCE)/Samples.hpp
	$(TOUCH) $(SOURCE)/FPGA.hpp

$(SOURCE)/Display.hpp : $(SOURCE)/Configuration.hpp $(SOURCE)/State.hpp $(SOURCE)/Samples.hpp
	$(TOUCH) $(SOURCE)/Display.hpp

$(LIBPOLO)/polo.h :
	$(TOUCH) $(LIBPOLO)/polo.h

# MAKING DIRECTORIES

$(OBJECTS) : | $(OBJ)

$(OBJ) : | $(TARGET)
	$(MAKEDIRECTORY) $(OBJ)

$(TARGET) :
	$(MAKEDIRECTORY) $(TARGET)

#CLEANING

clean :
	$(REMOVE) $(REMOVEPARAMS) $(TARGET)

