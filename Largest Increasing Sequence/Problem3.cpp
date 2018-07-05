// Copyright 2017 Joseph Liba joiemoie@bu.edu

/*
The highest increasing sequence uses recursion. First, we determine all the potential starting points for sequences.
Once all the potential starting points are found, we traverse forwards through the array. Whenever we
run into a number higher than the previous one in the current sequence, we split into two paths. The first path adds the number,
and the second path skips it. Once we reach the end, we check how long the path is and return the count / total.
Whichever path has the highest count / total is ultimately returned in the end.
*/
#include<iostream>
#include<fstream>
#include <cstdlib> 
#include<vector>

using std::malloc;
using std::vector;

//this helper function returns the highest count and total
//it also stores the longest sequence inside of result
vector<int> MaxIncSeqHelper(int * nums, int *currentNum, int * prevNum, vector <int> * longestLength, vector <int*> * result, int length, vector<int> countTotal, int * highestTotal) {
  
  //if at the end of the array, clear result if the current count is better than the existing. Then return the countTotal
  if (currentNum == nums + length) {
    if (countTotal[0] > (*result).size() || (countTotal[0] == (*result).size() && countTotal[1] > *highestTotal)) {
      (*result).clear();
      *highestTotal = countTotal[1];
    }
    return countTotal;
  }

  // if the highest count reached before at a number is higher than the current count, break from this path
  if (countTotal[0] < (*longestLength)[currentNum-nums]) return countTotal;

  // the current value is higher than the previous, then split into two paths. The first path adds the current number to the second, and the second path skips it.
  if (*currentNum >= *prevNum) {
    if (countTotal[0] > (*longestLength)[currentNum-nums]) (*longestLength)[currentNum-nums] = countTotal[0];

    vector<int> countTotal2 = MaxIncSeqHelper(nums, currentNum+1, prevNum, longestLength,result,length, countTotal, highestTotal);
    countTotal[0]++; countTotal[1]+=*currentNum;
    vector<int> countTotal1 = MaxIncSeqHelper(nums, currentNum+1, currentNum, longestLength,result,length, countTotal, highestTotal);

    // return the highest count/total
    if (countTotal1[0] > countTotal2[0] || (countTotal[0] == countTotal[0] && countTotal1[1] > countTotal2[1])) {
      (*result).insert((*result).begin(),currentNum);
      return countTotal1;
    }
    else {return countTotal2;}
  }
  else {
    //if the current value is less than the previous, skip this current value.
    return MaxIncSeqHelper(nums, currentNum+1, prevNum, longestLength, result, length, countTotal, highestTotal);
  }

}
void MaxIncSeq(int * nums, int length) {
  vector<int *> currentLongest; // current longest sequence
  vector<int > longestLength(length); // stores the highest length for any sequence that reaches a number
  vector<int> highestCountTotal(2); // highest count/total for the longest sequence
  for (int i = 0;  i < length; i++) {
    vector<int *> temp; // creates a temporary sequence
    int highestTotal = 0;
    if (longestLength[i] == 0) {
      vector<int> countTotal {1,*(nums+i)}; // starts the count and total at 1
      vector<int> countTotal2 = MaxIncSeqHelper(nums, nums+1+i, nums+i, &longestLength, &temp, length, countTotal, &highestTotal); // returns the highest count and total
      temp.insert(temp.begin(), nums+i); //insert the initial value into temp

      //checks if the current sequence is longer than the current best sequence. then replaces if it is
      if (countTotal2[0] > currentLongest.size() || (countTotal2[0] == highestCountTotal[0] && countTotal[1] >= highestCountTotal[1])) {
        currentLongest = temp;
        highestCountTotal[0] = countTotal[0];
        highestCountTotal[1] = countTotal[1];
      }
    }
  }
  
  //Prints out the longest seqeunce
  for (int * num : currentLongest) {
    std::cout << *num;
  }
}

int main(int argc, char ** argv) {
  int length;
  std::cin >> length;
  int * nums = (int*) malloc (length);

  for (int i = 0; i < length; i++) {
    std::cin >> *(nums+i);
  }

  MaxIncSeq(nums, length);
}
