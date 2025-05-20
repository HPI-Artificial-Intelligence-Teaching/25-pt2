TARGETS = selection_sort insertion_sort bubble_sort shell_sort merge_sort bottom_up_merge_sort quick_sort
CXX = g++
CPPFLAGS = -std=c++17 -O3
LDLIBS=-lm

all: $(TARGETS)

selection_sort: selection_sort.cpp sort.h
	$(CXX) $(CPPFLAGS) -o $@ $<

insertion_sort: insertion_sort.cpp sort.h
	$(CXX) $(CPPFLAGS) -o $@ $<

bubble_sort: bubble_sort.cpp sort.h
	$(CXX) $(CPPFLAGS) -o $@ $<

shell_sort: shell_sort.cpp sort.h
	$(CXX) $(CPPFLAGS) -o $@ $<

merge_sort: merge_sort.cpp sort.h
	$(CXX) $(CPPFLAGS) -o $@ $<

bottom_up_merge_sort: bottom_up_merge_sort.cpp sort.h
	$(CXX) $(CPPFLAGS) -o $@ $<

quick_sort: quick_sort.cpp sort.h
	$(CXX) $(CPPFLAGS) -o $@ $<

clean:
	$(RM) $(TARGETS)

.PHONY: all clean