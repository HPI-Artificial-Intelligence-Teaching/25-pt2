/******************************************************************************
 *
 * An test application for heaps
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *      ./heap_test < ../data/words3.txt
 *
 *  7 1 4 5 3 6 2
 *  1 2 3 4 5 6 7
 *  bed bug dad yes zoo now for tip ilk dim tag jot sob nob sky hut men egg few jay owl joy rap gig wee was wad fee tap tar dug jam all bad yet
 *  all bad bed bug dad dim dug egg fee few for gig hut ilk jam jay jot joy men nob now owl rap sky sob tag tap tar tip wad was wee yes yet zoo
 ******************************************************************************/

#include "heap.h"

#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

// test integer sorting
void test_int_sort(void) {
    int arr[]{7, 1, 4, 5, 3, 6, 2};
    const int n = sizeof(arr) / sizeof(int);

    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    heap_sort(arr, n);

    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    return;
}

// test large integer sorting
void test_large_int_sort(int n = 1000000) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> uniform(1, 10 * n);  // distribution in range [1, 10*n]

    int* arr = new int[n];

    cout << "Initializing " << n << " random numbers" << endl;
    for (int i = 0; i < n; i++) arr[i] = uniform(rng);

    cout << "Sorting " << n << " random numbers" << endl;
    heap_sort(arr, n);

    cout << "Finished sorting" << endl;

    delete[] arr;
    return;
}

// test string sorting
void test_string_sort(void) {
    string val;
    vector<string> data;
    while (cin >> val)
        data.push_back(val);
    auto n = data.size();

    for (int i = 0; i < n; i++) cout << data[i] << " ";
    cout << endl;

    heap_sort(data.data(), n);

    for (int i = 0; i < n; i++) cout << data[i] << " ";
    cout << endl;

    return;
}

int main(void) {
    test_int_sort();
    // test_large_int_sort();
    test_string_sort();

    return (0);
}