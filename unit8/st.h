/******************************************************************************
 *
 * An interface for symbol tables.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __ST_H__
#define __ST_H__

// Implements the base class for a symbol table
template <typename Key, typename Value>
class ST {
   public:
    // put a key-value pair into the table
    virtual void put(const Key& key, const Value& val) = 0;
    // gets a value for a given key
    virtual const Value* get(const Key& key) const = 0;
    // removes a key from the table
    virtual void remove(const Key& key) = 0;
    // checks if there is a value paired with a key
    virtual bool contains(const Key& key) const = 0;
    // checks if the symbol table is empty
    virtual bool is_empty() const = 0;
    // number of key-value pairs in the table
    virtual int size() const = 0;
};

#endif