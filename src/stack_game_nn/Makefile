ELF = bin/main.elf


LIBS_PATH=$(HOME)/programming/libs
INC+= -I.
INC+= -I$(LIBS_PATH)/common
INC+= -I$(LIBS_PATH)/dataset
INC+= -I$(LIBS_PATH)/robotics
INC+= -I$(LIBS_PATH)/nn
INC+= -I$(LIBS_PATH)/reinforcement_learning
INC+= -I$(LIBS_PATH)/visualisation
INC+= -I$(LIBS_PATH)/rl_game

LIBS+= $(LIBS_PATH)/libs.a


CC = g++
CU = nvcc
LD = g++
OBJCOPY = objcopy
OBJDUMP = objdump
SIZE = size

# DEGUBFLAGS = -g -pg

CFLAGS = $(DEGUBFLAGS) -O2 -Os -s -Wall -Wextra -pedantic -std=c++11 $(INC)
CUDAFLAGS = -O3 -D_FORCE_INLINES -ccbin=$(CXX) -Xcompiler -fPIC -std=c++11 $(INC)

LDFLAGS = $(DEGUBFLAGS) -lm -lpthread -pthread -std=c++11 -lglut -lGL -lGLU -lX11 -lSOIL -ljsoncpp -L/usr/local/cuda/lib64 -lcuda -lcudart


SRCS+= $(shell find -name '*.cpp')
SRCS_CUDA+= $(shell find -name '*.cu')


OBJS = $(SRCS:.cpp=.o)
OBJS_CUDA = $(SRCS_CUDA:.cu=.oc)

all: $(ELF)
	$(SIZE) $(ELF)

$(ELF): $(LIBS) $(OBJS) $(OBJS_CUDA)
	$(LD) -o $@ $(OBJS) $(OBJS_CUDA) $(LIBS) $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

%.oc: %.cu
	$(CU) -c $(CUDAFLAGS) $< -o $@

clean:
	rm $(OBJS) -rf
	rm $(OBJS_CUDA) -rf
	rm $(ELF) -rf
