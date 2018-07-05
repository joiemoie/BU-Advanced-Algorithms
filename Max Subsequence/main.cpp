//
//  main.cpp
//  Dijkstra
//
//  Created by Joseph Liba
//  Copyright © 2017 Joseph Liba. All rights reserved.
//  Full credit: https://en.wikipedia.org/wiki/Longest_common_subsequence_problem#Solution_for_two_sequences

#include <iostream>
#include <string>

using namespace std;

/* int ** c is a 2d array containing the length of the longest sequence in c[m][n], where
m is the length of s1 and n is the length of s2. The other values in the array c[i][j]
contain the longest common sequence up from 0...i and 0...j for s1 and s2.
*/
int** findMaxLength(string s1, string s2) {
	int m = s1.length();
	int n = s2.length();
	int ** c = (int **)malloc(sizeof(int *) * m);
	for (int i = 0; i < m; i++) {
		c[i] = (int *)malloc(sizeof(int) * n);
		c[i][0] = 0;
	}
	for (int i = 0; i < n; i++) {
		c[0][i] = 0;
	}
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			if (s1[i] == s2[j]) c[i][j] = c[i - 1][j - 1] + 1;
			else c[i][j] = (c[i - 1][j] > c[i][j - 1]) ? c[i - 1][j] : c[i][j - 1];
		}
	}
	return c;
}

/* Recursively traces back through the c array starting from c[m][n] until it
gets down to c[0][0]. Visualize the 2d array as starting from the top left corner at 0,0
going down to the bottom right at m,n. Starting at m,n, it goes either left, up, or
up left. Whenever the character matches in both strings, it prepends the character and
goes up left. If it does not match, it either goes up or left depending on which path
leads to the next longest subsequence.
*/

string backtrack(int ** c, string s1, string s2, int i, int j) {
	if (i == 0 || j == 0) return "";
	if (s1[i] == s2[j])	return backtrack(c, s1, s2, i - 1, j - 1) + s1[i];
	if (c[i][j - 1] > c[i - 1][j])	return backtrack(c, s1, s2, i, j - 1);
	return backtrack(c, s1, s2, i - 1, j);
}

// Given two sequences A and B, finds the longest sequence C such that
// C is a subsequence (not necessarily contiguous) of both A and B
string findMaxSubSeq(string str1, string str2)
{
	// the maximum common subsequence
	string subseq = "";
	
	int ** c = findMaxLength(str1, str2);
	subseq = backtrack(c, str1, str2, str1.length(), str2.length());
	for (int i = 0; i < str1.length(); i++) {
		free(c[i]);
	}
	free(c);
	return subseq;
}

int main(int argc, char const *argv[])
{
	string a;
	string b;

	cout << "String 1: ";
	cin >> a;
	cout << "String 2: ";
	cin >> b;

	// maximum subsequence in example sequences
	string maxSubSeq = findMaxSubSeq(a, b);

	cout << "Maximum common subsequence for " << a << " and " << b << " : " << maxSubSeq << endl;

	return 0;
}