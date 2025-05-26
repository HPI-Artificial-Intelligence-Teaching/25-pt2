TARGETS = ssst_test hash_st_test

CXX = g++
CPPFLAGS = -std=c++17 -O3
LDLIBS=-lm

all: $(TARGETS)

ssst_test: ssst_test.cpp ssst.h st.h queue.h
	$(CXX) $(CPPFLAGS) $< -o $@

hash_st_test: hash_st_test.cpp hash_st.h st.h queue.h
	$(CXX) $(CPPFLAGS) $< -o $@

clean:
	$(RM) $(TARGETS)

.PHONY: all clean