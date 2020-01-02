
GCC := g++

OUTPUT := dispatcher_demo
SOURCES := $(wildcard *.cpp)
CCFLAGS := -std=c++11 -g3

all: $(OUTPUT)
	
$(OUTPUT):
	$(GCC) -o $(OUTPUT) $(CCFLAGS) -pthread $(SOURCES)
	
clean:
	rm $(OUTPUT)
	
.PHONY: all
