CC = g++

SOURCES_DIR_PROC = Proc/Sources
SOURCES_DIR_STACK = Stack/Sources
SOURCES_DIR_ASSEMBLER = Assembl/Sources

SOURCES = $(wildcard $(SOURCES_DIR_PROC)/*.cpp ) $(wildcard $(SOURCES_DIR_STACK)/*.cpp )
OBJECTS = $(SOURCES:.cpp =.o)

CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra

EXECUTABLE = Processor 

PRINT := 0
DEB   := 0


ifeq ($(PRINT), 1)
	CFLAGS += -DOTHER_PRINTS
endif

ifeq ($(DEB), 1)
	CFLAGS += -DUSE_DEBUG
endif


all: build

build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -IStack/Headers -IProc/Headers $(CFLAGS)  -o $(EXECUTABLE)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@     

clean:
	rm -rf /*.o Processor


