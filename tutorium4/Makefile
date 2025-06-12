CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SOURCES = array.cpp bitset.cpp closure.cpp vector.cpp knuths_hash.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLES = $(SOURCES:.cpp=)

all: $(EXECUTABLES)

%: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLES)

rebuild: clean all

.PHONY: all clean rebuild