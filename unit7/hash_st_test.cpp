/******************************************************************************
 *
 * A symbol table implemented with a separate-chaining hash table.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *
 *  % ./hash_st_test < ../data/tinyST.txt
 *  R 3
 *  S 0
 *  P 10
 *  M 9
 *  X 7
 *  H 5
 *  A 8
 *  E 12
 *  L 11
 *  C 4
 *
 ******************************************************************************/

#include "hash_st.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main(void) {
    SeparateChainingHashST<string, int> st;
    string item;
    int i = 0;
    while (cin >> item) {
        st.put(item, i++);
    }

    for (auto& s : st.keys()) {
        cout << s << " " << *st.get(s) << endl;
    }

    return (0);
}