// Author: TheBeerex
// Lab_09 ~~ Huffman Codes
// Incorrect implementation

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// A Huffman tree node
struct Node {
	char data;
	int freq;
	Node *left, *right;

	Node (char data, int freq) {
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

// Sorts Node* vector with InsertionSort in descending order
void sortNodeVector (vector<Node*> &vect) {
	int i, j;
	Node* key;
	for ( i = 1; i < vect.size(); i++) {
		key = vect[i];
		j = i - 1;

		while (j >= 0 && vect[j]->freq < key->freq) {
			vect[j+1] = vect[j];
			j = j - 1;
		}
		vect[j+1] = key;
	}
}

// Prints huffman codes from the root of Huffman Tree w/ recursion.
void findCodes (Node* root, string str, char chars[], string codes[]) {

	if (!root)
		return;

	if (root->data != '$') {
		for (int i = 0; i < 6; i++) {
			if (root->data == chars[i]) {
				codes[i] = str;
			}
		}
	}

	findCodes(root->left, str + "0", chars, codes);
	findCodes(root->right, str + "1", chars, codes);
}

// Builds a Huffman Tree and print codes by traversing the built Huffman Tree
void HuffmanCodes (char arr[], int freq[]) {
	Node *left, *right, *top;

	vector<Node*> leaves;
	for (int i = 0; i < 6; i++) {
		leaves.push_back(new Node(arr[i], freq[i]));
	}

	sortNodeVector(leaves);

	// Initial tree
	left = leaves.back();
	leaves.pop_back();
	right = leaves.back();
	leaves.pop_back();

	top = new Node('$', left->freq+right->freq);
	top->left = left;
	top->right = right;

	// Build rest of the tree
	while (leaves.size() != 0) {
		Node* newLeaf = leaves.back();
		leaves.pop_back();

		if (newLeaf->freq < top->freq) { //newleaf gets placed left of current top
			left = newLeaf;
			right = top;
			top = new Node('$', top->freq + newLeaf->freq);
			top->left = left;
			top->right = right;
		} else { //newleaf gets placed right of current top
			left = top;
			right = newLeaf;
			top = new Node('$', top->freq + newLeaf->freq);
			top->left = left;
			top->right = right;
		}
	}

	string codes[6];
	// finds and prints codes
	findCodes(top, "", arr, codes);
	for (int i = 0; i < 6; i++) {
		cout << arr[i] << ":" << codes[i] << endl;
	}
}

// Driver Code
int main() {
    
	int size = 6;

	char chars[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
	int freq[6];

    for (int i = 0; i < size; i++) {
        cin >> freq[i];
    }

	HuffmanCodes(chars, freq);

	return 0;
}
