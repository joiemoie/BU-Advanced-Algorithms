// Copyright 2017 Joseph Liba

#include <iostream>
#include <vector>
#include <string>
#include<fstream>

using namespace std;
using std::string;
using std::vector;

struct Node {
	bool isWord = false;
	Node * children[26] = {0};
};

class Trie {
	public:
		Node * lower;
		Node * upper;
		Trie();
		void AddWord(string str);
	
};

Trie::Trie() { lower = new Node(); upper = new Node(); }

void Trie::AddWord(string str) {
	Node * currentNode = upper;
	if (str[0] >= 'a') {
		currentNode = lower;
	}
	
	for (int i = 0; i < str.size(); i++) {
		int val = (str[i] >= 'a') ? str[i] - 'a' : str[i] - 'A';
		if (currentNode->children[val] != 0) {
			currentNode = currentNode->children[val];
		}
		else {
			currentNode->children[val] = new Node();
			currentNode = currentNode->children[val];
		}
	}
	currentNode->isWord = true;
}


void fourA() {
	std::ifstream myReadFile;
	myReadFile.open("BigData.txt");
	int total = 0;
	string str;
	while (myReadFile >> str) {
		if (str[0] == 'U') {
			int i = 1;
			while (i < 9 && str[i] >= '0' && str[i] <= '9') i++;
			if (i == 9 && (str[i] < '0' || str[i] > '9')) {
				total++;
			}
		}
	}
	myReadFile.close();
	std::cout<< total << '\n';
}


void fourB() {
	string str;
	std::ifstream myReadFile;
	myReadFile.open("BigData.txt");
	std::ifstream myDictionary;
	myDictionary.open("dictionary.txt");

	//Initializes the trie and pushes words into the trie from the dictionary.
	Trie trie = Trie();
	while (std::getline(myDictionary,str)) {
		trie.AddWord(str);
	}
	myDictionary.close();
	int total = 0;
	char c;

	//Creates a vector of the potential words.
	//To each new character, add it to the vector of potential words.
	//To each potential word, check if you can add another character to it.
	//Whenever you find a word, add to the total.
	vector<Node*> words;
	while (myReadFile.get(c)) {
		int val = -1;
		if (c >= 'A' && c <= 'Z'){
			val = c - 'A';
			if (c != 'J')
				words.push_back(trie.upper);
		}
		else if (c >= 'a' && c <= 'z'){
			val = c - 'a';
			if (c != 'j')
				words.push_back(trie.lower);
		}
		
		if (val >= 0) {
			for (int i = 0; i < words.size(); i++) {
				bool erased = false;
				if (words[i]->children[val] != 0) words[i] = words[i]->children[val];
				else {
					erased = true;
					words.erase(words.begin() + i);
				}
				if (!erased) {
					if (words[i]->isWord) total++;
				}
				else i--;
			}
		}
		else {
			words.clear();
		}
	}
	std::cout << total << '\n';

}

void fourC() {
	std::ifstream myReadFile;
	myReadFile.open("BigData.txt");
	int i = 0;
	int longest = 1;
	int fileLength = 0;
	char c;
	
	//Count characters in the file
	while (myReadFile.get(c)) {
		fileLength++;
	}
	myReadFile.close();

	//Copies the file onto the heap.
	char * file = (char*) malloc(fileLength * sizeof(char));
	char * fp = file;
	myReadFile.open("BigData.txt");
	while (myReadFile.get(c)) {
		*fp = c;
		fp++;
	}
	myReadFile.close();
	myReadFile.open("BigData.txt");

	for (int j = 1; j < fileLength; j++) {  

		//Finds the palindrome that is odd length.

		int left, right;
		//Checks the characters around the center character
		for (left = j -1, right = j+1; left >= 0 && right < fileLength && file[left] == file[right]; left--, right++)
		{
			if (right - left + 1 > longest)
			{
				longest = right - left + 1;
				i = left;
			}
		}

		//Finds the palindrome that is even length.
		left = j - 1;
		right = j;
		for (left = j - 1, right = j; left >= 0 && right < fileLength && file[left] == file[right]; left--, right++)
		{
			if (right - left + 1 > longest)
			{
				longest = right - left + 1;
				i = left;
			}
		}
	}
	
	for (int j = 0; j < longest; j++) {
		std::cout << file[i + j];
	}
	free(file);
}

int main(){
	fourA();
	fourB();
	fourC();
	return 0;
}