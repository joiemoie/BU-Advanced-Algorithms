// Copyright 2017 Joseph Liba
// Hash functions from https://gist.github.com/TheRayTracer/9907950

#include "MyBloomFilter.h"
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using std::vector;

vector<char> bitmap;


// Java HashCode for strings: https://en.wikipedia.org/wiki/Java_hashCode()
//  s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
unsigned int hash1(string s)
{
  unsigned int hash = 0;
  for (int i = 0; i < s.length(); i++) {
    hash += s[i] * std::pow(31, s.length()-i-1);
  }
  return hash;
}

// Reverse Java Hash but modified from 31 to 29.
// I need to change 31 to 29 otherwise "abcdef" will have the same hash as "fedcba".
//  s[n-1]*30^(n-1) + s[n-2]*30^(n-2) + ... + s[0]
unsigned int hash2(string s)
{
  unsigned int hash = 0;
  for (int i = 0; i < s.length(); i++) {
    hash += s[i] * std::pow(29, i);
  }
  return hash;
}


void MyBloomFilter::insert(string item)
{
  unsigned int pos1 = hash1(item);
  unsigned int pos2 = hash2(item);
  
  // The actual length of the bitmap is 8x the number of characters since there
  // are 8 bits in a character.
  pos1 %= length * 8;
  pos2 %= length * 8;

  if (bitmap.size() < length) {
    bitmap.resize(length);
  }


  //Goes to the index and flips the individual bit in the index to 1.
  // So for example, if the hash value is 10, I go to the second character and flip bit 2.
  bitmap[pos1/8] = bitmap[pos1/8] | ( 1u << ( 7- (pos1 % 8 ) ) );
  
  bitmap[pos2/8] = bitmap[pos2/8] | ( 1u << ( 7- (pos2 % 8 ) ) );
  
}

bool MyBloomFilter::exists(string item)
{
  bool exists = false;
  unsigned int pos1 = hash1(item);
  unsigned int pos2 = hash2(item);
  
  //Calculates the index for each hash value
  pos1 %= length * 8;
  pos2 %= length * 8;
  if (bitmap.size() < length) {
    bitmap.resize(length);
  }

  // Goes to the index and checks if the individual bit is 1.
  // So for example, if I want to check the hash value of 27, I go to the 3rd character and check bit 3.
  if ( ( bitmap[pos1/8] & ( 1u << ( 7- (pos1 % 8 ) ) ) ) ==  ( 1u << ( 7- (pos1 % 8 ) ) ) ) {
   if ( ( bitmap[pos2/8] & ( 1u << ( 7- (pos2 % 8 ) ) ) ) ==  ( 1u << ( 7- (pos2 % 8 ) ) ) )
     return true;
  }
  return false;
}

/*Reads each character bit by bit, providing a new line character every 2 bytes*/
string MyBloomFilter::output(){
  
  string out = "\n";
  
  if (bitmap.size() < length) {
    bitmap.resize(length);
  }
  for(int i = 0; i < length; i++) {
    //Adds each bit of the character to the output.
    for(int j = 7; j >= 0; j--) {
        out += '0' + ((bitmap[i] >> j) & 0x01);
    }
    if (i%2==1) out += '\n';
  }
  return out;
}

