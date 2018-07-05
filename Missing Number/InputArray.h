//
//  InputArray.h
//  InputArray
//
//  Copyright © 2017 Tali Moreshet. All rights reserved.
//

#ifndef InputArray_h
#define InputArray_h

#include <stdio.h>
#include <bitset>

using namespace std;

class InputArray {
public:
    int n;
    InputArray();
    ~InputArray();
    bool findBit(int, int);
private:
    int *Array;
};

#endif /* InputArray_h */
