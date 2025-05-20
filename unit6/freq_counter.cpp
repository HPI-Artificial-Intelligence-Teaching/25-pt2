/*
    ./freq_counter_seq_search 8 < ../data/tale.txt

business 122
distinct = 5131
words    = 14350

    ./freq_counter_binary_search 8 < ../data/tale.txt

business 122
distinct = 5131
words    = 14350

    ./freq_counter_fib_search 8 < ../data/tale.txt

business 122
distinct = 5131
words    = 14350

*/

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#include "st.h"

#ifdef SEQ_SEARCH
#include "seqsearch.h"
#endif

#ifdef BINARY_SEARCH
#include "binarysearch.h"
#endif

#ifdef FIBONACCI_SEARCH
#include "fibsearch.h"
#endif

using namespace std;

// performs the frequency counting test
void freq_counter(ST<string, int>* st, int min_len) {
    int distinct = 0, words = 0;
    string max_str = "";
    int max_cnt = 0;

    string key;
    while (cin >> key) {
        if (key.length() < min_len) continue;

        words++;
        if (st->contains(key)) {
            auto new_count = *(st->get(key)) + 1;
            if (new_count > max_cnt) {
                max_cnt = new_count;
                max_str = key;
            }
            st->put(key, new_count);
        } else {
            st->put(key, 1);
            distinct++;
        }
    }

    // output final statistics
    cout << max_str << " " << max_cnt << endl;
    cout << "distinct = " << distinct << endl;
    cout << "words    = " << words << endl;

    return;
}

// main entry point of the program
int main(int argc, char* argv[]) {
    int min_len = (argc == 2) ? atoi(argv[1]) : 1;

#ifdef SEQ_SEARCH
    // compute frequency counts
    SeqSearchST<string, int>* seq_search_st = new SeqSearchST<string, int>();
    freq_counter(seq_search_st, min_len);
    delete seq_search_st;
#endif

#ifdef BINARY_SEARCH
    // compute frequency counts
    BinarySearchST<string, int>* binary_search_st = new BinarySearchST<string, int>();
    freq_counter(binary_search_st, min_len);
    delete binary_search_st;
#endif

#ifdef FIBONACCI_SEARCH
    // compute frequency counts
    FibonacciSearchST<string, int>* fib_search_st = new FibonacciSearchST<string, int>();
    freq_counter(fib_search_st, min_len);
    delete fib_search_st;
#endif

    return (0);
}