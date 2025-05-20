TARGETS = freq_counter_seq_search freq_counter_binary_search freq_counter_fib_search
CXX = g++
CPPFLAGS = -std=c++17
LDLIBS=-lm

all: $(TARGETS)

freq_counter_seq_search: freq_counter.cpp seqsearch.h st.h
	$(CXX) $(CPPFLAGS) -DSEQ_SEARCH -o $@ $<

freq_counter_binary_search: freq_counter.cpp binarysearch.h st.h
	$(CXX) $(CPPFLAGS) -DBINARY_SEARCH -o $@ $<

freq_counter_fib_search: freq_counter.cpp fibsearch.h st.h
	$(CXX) $(CPPFLAGS) -DFIBONACCI_SEARCH -o $@ $<

clean:
	$(RM) $(TARGETS)

.PHONY: all clean