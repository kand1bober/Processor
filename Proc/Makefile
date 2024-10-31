
# CC = g++
# # CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra
# CFLAGS = -D _DEBUG -O0 -Wall -Wextra


# SOURCES_DIR_PROC = Sources
# SOURCES_DIR_STACK = ../Stack/Sources

# SOURCES_PROC = $(wildcard $(SOURCES_DIR_PROC)/*cpp ) 
# SOURCES_STACK = $(wildcard $(SOURCES_DIR_STACK)/*cpp ) 


# OBJECTS_PROC = $(SOURCES_PROC:.cpp =.o) 
# OBJECTS_STACK = $(SOURCES_STACK:.cpp =.o) 

# EXECUTABLE = Processor 


# PRINT := 0
# DEB   := 0


# ifeq ($(PRINT), 1)
# 	CFLAGS += -DOTHER_PRINTS
# endif

# ifeq ($(DEB), 1)
# 	CFLAGS += -DUSE_DEBUG
# endif


# all: $(EXECUTABLE)

# $(EXECUTABLE): $(OBJECTS_PROC) $(OBJECTS_STACK)
# 	$(CC) $(OBJECTS_PROC) $(OBJECTS_STACK) $(CFLAGS) -o $(EXECUTABLE)


# $(OBJECTS_PROC): %.o: %.cpp
# 	$(CC) -c $(CFLAGS) -IHeaders $< -o $@

# $(OBJECTS_STACK): %.o: %.cpp
# 	$(CC) -c $(CFLAGS) -I../Stack/Headers $< -o $@


# clean:
# 	@rm  -rf $(SOURCES_PROC/*.o)  $(SOURCES_STACK/*.o)  $(EXECUTABLE)




#=================== WORKING VARIANT ==============================

CC = g++
# CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra
CFLAGS = -D _DEBUG -O0 -Wall -Wextra


SOURCES_DIR_PROC = Sources
SOURCES_DIR_STACK = ../Stack/Sources

SOURCES_PROC = $(wildcard $(SOURCES_DIR_PROC)/*cpp ) 
SOURCES_STACK = $(wildcard $(SOURCES_DIR_STACK)/*cpp ) 


OBJECTS_PROC = $(SOURCES_PROC:.cpp =.o) 
OBJECTS_STACK = $(SOURCES_STACK:.cpp =.o) 

EXECUTABLE = Processor 


PRINT := 0
DEB   := 0


ifeq ($(PRINT), 1)
	CFLAGS += -DOTHER_PRINTS
endif

ifeq ($(DEB), 1)
	CFLAGS += -DUSE_DEBUG
endif


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_PROC) $(OBJECTS_STACK)
	$(CC) $(OBJECTS_PROC) $(OBJECTS_STACK) $(CFLAGS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# $(OBJECTS_PROC): 


clean:
	@rm  -rf $(SOURCES_PROC/*.o)  $(SOURCES_STACK/*.o)  $(EXECUTABLE)

# =====================================================================