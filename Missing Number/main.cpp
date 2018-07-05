//
//  Main.cpp
//
//  Copyright © 2017 Joseph Liba. All rights reserved.
//

#include "InputArray.h"
#include <cmath>
#include <iostream>

/* 
 This algorithm runs in O(n) time. This uses a form of counting sort.
 First, I read each integer in the array and then store the value 1
 into the index corresponding to the number. This takes linear time since
 I know each integer is 32 bits, so I call findBit (n-1) * 32 times. 
 Since findBit is constant time, this means thats it takes linear time to fill
 the new array with 1's. It again takes linear time to read through this
 new array and find the index with the 0 element. That index is the missing number.
*/

int missingNum(InputArray * inputArray, int n) {
	int result[n] = { 0 };
	for (int i = 0; i < n; i++) {
		int num = 0;
		for (int j = 0; j<32; j++) {
			num += (inputArray->findBit(i, j)) ? pow(2, j) : 0;
		}
		result[num] = 1;
	}
	int missingNum = -1;
	for (int i = 0; i < n; i++) {
		if (result[i] == 0) missingNum = i;
	}
	return missingNum;
}
int main() {
	InputArray inputArray = InputArray();
	int num = missingNum(&inputArray, 7);
	std::cout<<num;
	return 1;
}
