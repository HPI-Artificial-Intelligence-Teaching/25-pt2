TARGETS = btree freq_counter_bst freq_counter_redblack_bst min_pq_test heap_test
CXX = g++
CPPFLAGS = -std=c++17 -O3
LDLIBS=-lm

all: $(TARGETS)

btree: btree.cpp btree.h queue.h
	$(CXX) $(CPPFLAGS) -o $@ $<

freq_counter_bst: freq_counter.cpp bst.h st.h
	$(CXX) $(CPPFLAGS) -DBST_SEARCH -o $@ $<

freq_counter_redblack_bst: freq_counter.cpp redblack_bst.h st.h
	$(CXX) $(CPPFLAGS) -DREDBLACK_BST_SEARCH -o $@ $<

min_pq_test: min_pq_test.cpp min_pq.h
	$(CXX) $(CPPFLAGS) $< -o $@

heap_test: heap_test.cpp heap.h
	$(CXX) $(CPPFLAGS) -o $@ $<

clean:
	$(RM) $(TARGETS)

.PHONY: all clean