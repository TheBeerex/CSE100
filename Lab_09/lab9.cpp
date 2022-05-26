// Author: TheBeerex
// Lab_09 ~~ Huffman Codes

#include <iostream>
#include <vector>
#include <queue>
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

// Finds huffman codes from the root of Huffman Tree w/ preorder traversal, putting them into codes[].
void findCodes (Node* root, string str, char chars[], string codes[]) {

	if (!root)
		return;

	// if it's a leaf node
	if (root->data != '$') {
		// codes[i] = character's code
		for (int i = 0; i < 6; i++) {
			if (root->data == chars[i]) {
				codes[i] = str;
			}
		}
	}

	// traverse left/right nodes
	findCodes(root->left, str + "0", chars, codes);
	findCodes(root->right, str + "1", chars, codes);
}

// Needed for priority_queue used in HuffmanCodes
struct compare {

    bool operator()(Node* l, Node* r) {
        return (l->freq > r->freq);
    }

};

// Builds a Huffman Tree and print codes by traversing the built Huffman Tree
void HuffmanCodes (char data[], int freq[]) {
	Node *left, *right, *top;

	// priority_queue automatically sorts the nodes with respect to their freq value, as dictaed in struct compare
	priority_queue<Node*, vector<Node*>, compare> trees;

	// Create leaf nodes from data[] and freq[]
	for (int i = 0; i < 6; i++) {
		trees.push(new Node(data[i], freq[i]));
	}

	// Build huffman tree
	while (trees.size() != 1) {
		// least significant node
		left = trees.top();
		trees.pop();

		// second least significant node
		right = trees.top();
		trees.pop();

		// internal nodes have data->'$'
		top = new Node('$', left->freq + right->freq);

		// set new node's children
		top->left = left;
		top->right = right;

		// push it to priority_queue
		trees.push(top);
	}

	string codes[6];
	// finds and prints codes
	findCodes(trees.top(), "", data, codes);
	for (int i = 0; i < 6; i++) {
		cout << data[i] << ":" << codes[i] << endl;
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
