/******************************************************************************
 *
 * Sorts a sequence of strings from standard input using quick sort
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *      % more tiny.txt
 *      S O R T E X A M P L E
 *
 *      % ./quick_sort < ../data/tiny.txt
 *      A E E L M O P R S T X                 [ one string per line ]
 *
 *      % more words3.txt
 *      bed bug dad yes zoo ... all bad yet
 *
 *      % ./quick_sort < ../data/words3.txt
 *      all bad bed bug dad ... yes yet zoo   [ one string per line ]
 * 
 ******************************************************************************/

#include <iostream>
#include <string>
#include "sort.h"

#define MAX_STR 100 // maximum number of strings

using namespace std;

int main(void) {
    string val[MAX_STR];
    int no_of_strings = 0;

    // read the strings from standard input
    while ((no_of_strings < MAX_STR) && (cin >> val [no_of_strings])) {
        no_of_strings++;
    }

    // sort the strings
    quick_sort(val, 0, no_of_strings-1);

    // print the sorted strings
    for (auto i = 0; i < no_of_strings; i++) {
        cout << val[i] << " ";
    }
    cout << endl;

    return 0;
}