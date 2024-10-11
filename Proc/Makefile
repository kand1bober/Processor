PRINT := 0
DEB   := 0

CC = g++

CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra

ifeq ($(PRINT), 1)
CFLAGS += -DOTHER_PRINTS
endif

ifeq ($(DEB), 1)
CFLAGS += -DUSE_DEBUG
endif


all:
	$(CC)    ../Stack/Sources/DebugFuncs.cpp  ../Stack/Sources/functions.cpp    Sources/main.cpp $(CFLAGS) -o Processor

clean:
	rm -rf /*.o Processor
