/******************************************************************************
 *
 * An performance counter application for symbol tables
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *     ./freq_counter_bst 8 < ../data/tale.txt
 *
 *  business 122
 *  distinct = 5131
 *  words    = 14350
 *
 *      ./freq_counter_redblack_bst 8 < ../data/tale.txt
 *
 *  business 122
 *  distinct = 5131
 *  words    = 14350
 *
 *
 *  To see the time difference more pronounced, try the following two commands (assuming you downloaded the
 *  leipzig100K dataset from https://introcs.cs.princeton.edu/java/data/leipzig/leipzig100k.txt)
 *
 *      time tr -s '[[:punct:][:space:]]' '\n' < ~/Downloads/leipzig100K.txt | sort | ./freq_counter_redblack_bst 10
 *
 *  government 3374
 *  distinct = 13148
 *  words    = 121247
 *  tr -s '[[:punct:][:space:]]' '\n' < ~/Downloads/leipzig100K.txt  0.85s user 0.01s system 99% cpu 0.861 total
 *  sort  1.90s user 0.07s system 52% cpu 3.751 total
 *  ./freq_counter_redblack_bst 10  2.14s user 0.01s system 56% cpu 3.769 total
 *
 *      time tr -s '[[:punct:][:space:]]' '\n' < ~/Downloads/leipzig100K.txt | sort | ./freq_counter_bst 10
 *
 *  government 3374
 *  distinct = 13148
 *  words    = 121247
 *  tr -s '[[:punct:][:space:]]' '\n' < ~/Downloads/leipzig100K.txt  0.85s user 0.01s system 99% cpu 0.861 total
 *  sort  2.03s user 0.06s system 5% cpu 36.591 total
 *  ./freq_counter_bst 10  36.62s user 0.13s system 95% cpu 38.370 total
 ******************************************************************************/

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#include "st.h"

#ifdef BST_SEARCH
#include "bst.h"
#endif

#ifdef REDBLACK_BST_SEARCH
#include "redblack_bst.h"
#endif

using namespace std;

// a linked list to store the individual keys that we have encountered when parsing the input
struct List {
    string key;
    List* next;
    List(const string& k, List* n) : key(k), next(n) {}
};

// adds a keyword to the keyword list
List* add_keyword(List* head, const string& k) {
    return (new List(k, head));
}

// deletes the keyword list
void delete_keywords(List* head) {
    while (head) {
        List* t = head->next;
        delete head;
        head = t;
    }
    return;
}

// performs the frequency counting test
void freq_counter(ST<string, int>* st, int min_len) {
    int distinct = 0, words = 0;
    string max_str = "";
    int max_cnt = 0;

    // first parse all the input strings and put them both in the list and count them with the symbol table
    string key;
    List* keywords = nullptr;
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
            keywords = add_keyword(keywords, key);
            st->put(key, 1);
            distinct++;
        }
    }

    // now iterate through all the keywords and remove them from the symbol table again
    for (List* t = keywords; t != nullptr; t = t->next) {
        st->remove(t->key);
    }
    delete_keywords(keywords);

    // finally, check that the tree is empty
    if (!st->is_empty()) {
        cerr << "Something went wrong in the put or delete (" << st->size() << ")" << endl;
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

// compute frequency counts
#ifdef BST_SEARCH
    BST<string, int>* bst = new BST<string, int>();
    freq_counter(bst, min_len);
    delete bst;
#endif

#ifdef REDBLACK_BST_SEARCH
    RedBlackBST<string, int>* red_black_bst = new RedBlackBST<string, int>();
    freq_counter(red_black_bst, min_len);
    delete red_black_bst;
#endif

    return (0);
}
