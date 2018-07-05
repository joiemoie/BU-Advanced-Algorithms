//
//  MyBloomFilter.h
//  MyBloomFilter
//
//  Created by Joseph Liba, modified from Tali Morshet
//

#ifndef MyBloomFilter_h
#define MyBloomFilter_h

#include <string>
#include "BloomFilter.h"

using namespace std;

class MyBloomFilter : public BloomFilter {
public:
    /**
     * Instantiate an empty Bloom filter of length 'len' chars.
     */
    MyBloomFilter (int len) : BloomFilter(len){ length=len; }
    
    /**
     * Inserts item into the filter
     */
    void insert(string item);
    
    /**
     * Checks whether item is in the filter.
     * Returns true if the item is probably in the filter
     *         false if the item is definitely not in the filter
     */
    bool exists(string item);
    
    /**
     * Returns a string of characters representing the Bloom filter
     */
    string output();
    
protected:
    int length;     /** The length of the Bloom filter, in chars. */
};

#endif /* MyBloomFilter_h */
