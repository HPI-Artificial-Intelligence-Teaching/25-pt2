#include "btree.h"

#include <iomanip>
#include <iostream>

using namespace std;

// test a stack of characters
void test_char_tree(void) {
    BTree<char> t;

    t.insert('D');
    t.insert('B');
    t.insert('F');
    t.insert('A');
    t.insert('C');
    t.insert('E');
    t.insert('G');

    cout << setw(20) << "In order: ";
    t.traverse_in_order([](auto c) { cout << c << " "; });
    cout << endl;
    cout << setw(20) << "Pre order: ";
    t.traverse_pre_order([](auto c) { cout << c << " "; });
    cout << endl;
    cout << setw(20) << "Post order: ";
    t.traverse_post_order([](auto c) { cout << c << " "; });
    cout << endl;
    cout << setw(20) << "BFS order: ";
    t.traverse_bfs_order([](auto c) { cout << c << " "; });
    cout << endl;

    return;
}

int main(void) {
    test_char_tree();

    return (0);
}