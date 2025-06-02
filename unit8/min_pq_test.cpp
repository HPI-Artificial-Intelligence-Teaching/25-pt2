/******************************************************************************
 *
 * Generic min priority queue implementation with a binary heap.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *
 *  % ./min_pq_test < ../data/tinyPQ.txt
 *  E A E (6 left on pq)
 *
 ******************************************************************************/

#include "min_pq.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main(void) {
    MinPQ<string> pq;
    string item;
    while (cin >> item) {
        if (!(item == "-")) {
            pq.insert(item);
        } else if (!pq.is_empty()) {
            cout << pq.del_min() << " ";
        }
    }
    cout << "(" << pq.size() << " left on pq)" << endl;

    return (0);
}