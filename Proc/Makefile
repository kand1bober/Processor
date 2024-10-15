CC = g++

SOURCES_DIR_PROC=Sources
SOURCES_DIR_STACK=../Stack/Sources

SOURCES_PROC = $(wildcard $(SOURCES_DIR_PROC)/*.cpp)  
SOURCES_STACK = $(wildcard $(SOURCES_DIR_STACK)/*.cpp)  

OBJECTS_PROC = $(SOURCES_PROC:.cpp =.o) 
OBJECTS_STACK = $(SOURCES_STACK:.cpp =.o) 

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

$(EXECUTABLE): $(OBJECTS_PROC) $(OBJECTS_STACK)
	$(CC) $^ -o $(EXECUTABLE)

$(OBJECTS_PROC): $(SOURCES_PROC)
	$(CC) -c $(CFLAGS) -IHeaders $< -o $@

$(OBJECTS_STACK): $(SOURCES_STACK)
	$(CC) -c $(CFLAGS) -I../Stack/Headers $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
