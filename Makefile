CC = g++
CFLAGS = -Iinclude -std=c++11
SOURCES = src/main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = SimpleDB

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
