/******************************************************************************
 *
 * Symbol table implementation with sequential search in an unordered linked list of key-value pairs.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *
 *  % ./ssst_test < ../data/tinyST.txt
 *  L 11
 *  P 10
 *  M 9
 *  X 7
 *  H 5
 *  C 4
 *  R 3
 *  A 8
 *  E 12
 *  S 0
 *
 ******************************************************************************/

#include "ssst.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main(void) {
    SequentialSearchST<string, int> st;
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