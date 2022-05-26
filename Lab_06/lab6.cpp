// Author: TheBeerex
// Lab_06 ~~ Hash Table w/ Chaining

#include <string>
#include <iostream>

using namespace std;

// Linked List class

struct Node {
    int val;
    Node* next;
};

class LinkedList {
    private:
        Node* head;
        Node* tail;

    public: 
        LinkedList() { // Constructor
            this->head == NULL;
            this->tail == NULL;
        }
        ~LinkedList() { // Deconstructor
            this->clear();
        }


        // SEARCHERS

        int searchNodes(int key) { // Searches linked list for a particular node, returns found "index"
            if (!this->isEmpty()) {
                int found = 0;
                // linked list has length of 1
                if (this->head->next == NULL) {
                    if (head->val == key)
                        return found; // return "index" of found node
                    else
                        return -1;
                }

                // linked list has length > 1
                Node* temp = this->head;
                do {
                    if (temp->val == key) {
                        return found;
                    }
                    temp = temp->next;
                    found++;
                } while (temp != NULL);
            }

            return -1;
        }


        // INSERTERS

        void insertAtFront(int key){ // Inserts new node to front
            Node* temp =  new Node; // create new node
            temp->val = key; // store data
            temp->next = this->head; // head now follows temp
            this->head = temp;
            if (this->head->next == NULL) {
                this->tail = this->head;
            }
        }


        // REMOVERS

        bool removeNode(int key) { // finds and removes node with key if found
            int index = this->searchNodes(key);
            if (index == -1) {
                return 0;
            } else {
                if(index == 0) {
                    removeFromFront();
                    return 1;
                } else {
                    Node* prev = this->head;
                    for (int i = 0; i < index-1; i++) {
                        prev = prev->next;
                    }
                    Node* old = prev->next; // save current head
                    prev->next = prev->next->next; // skip over old head
                    delete old; // delete the old head
                    return 1;
                }
            }
        }

        bool removeFromFront(){ // removes front element
            if(!this->isEmpty()){
                Node* old = this->head; // save current head
                head = head->next; // skip over old head
                delete old; // delete the old head
                return 1;
            }else
                return 0;
        }

        void clear(){ // Clears linked list
            while(!this->isEmpty())
                removeFromFront();
        }


        // UILITIES

        void print(){ // prints linked list
            Node* temp = this->head;
            if(!this->isEmpty()){
                cout << temp->val << "->";
                while (temp->next != NULL){
                    temp = temp->next;
                    cout << temp->val << "->";
                }
            }
            cout << ";";
        }

        int size(){ // Returns size of linked list
            if(this->isEmpty())
                return 0;
            else{
                int counter = 1;
                Node* temp = this->head;
                while (temp->next != NULL){
                    counter++;
                    temp = temp->next;
                }
                return counter;
            }
            return -1;
        }
        
        bool isEmpty(){ // Returns whether the linked list is empty or not
            return (this->head == NULL);
        }

};


// Hash Table class
class HashTable {
    private:
        LinkedList* theTable;
        int sizeM;

    public:
        HashTable(int n) { // Constructor
            sizeM = n;
            theTable = new LinkedList[n];
        }

        ~HashTable() { // Deconstructor
            for (int i = 0; i < sizeM; i++) {
                theTable[i].clear();
            }
        }

        void insertKey(int key) { // Inserts new key
            int index = key % sizeM;
            theTable[index].insertAtFront(key);
        }

        bool searchKey(int key) { // Searches for key
            int index = key % sizeM;
            int found = theTable[index].searchNodes(key);
            if (found != -1) {
                cout << key << ":FOUND_AT" << index << "," << found << ";" << endl;
                return 1;
            } else {
                cout << key << ":NOT_FOUND;" << endl;
                return 0;
            }
        }

        bool deleteKey(int key) { // Deletes key if it exists
            int index = key % sizeM;
            bool completed = theTable[index].removeNode(key);
            if (completed) {
                cout << key << ":DELETED;" << endl;
                return 1;
            } else {
                cout << key << ":DELETE_FAILED;" << endl;
                return 0;
            }
        }

        void printTable() { // Prints hash table
            for (int i = 0; i < sizeM; i++) {
                cout << i << ":";
                theTable[i].print();
                cout << endl;
            }
        }

};

int main() {
    int m;
    cin >> m;

    if (m > 0) {
        HashTable* myTable = new HashTable(m);
        bool running = 1;
        string temp = "";

        while (running) {
            cin >> temp;
            char action = temp[0];
            int key;
            switch (action) {
                case 'i': //insert
                    key = stoi(temp.substr(1));
                    myTable->insertKey(key);
                break;
                case 'd': //delete
                    key = stoi(temp.substr(1));
                    myTable->deleteKey(key);
                break;
                case 's': //search
                    key = stoi(temp.substr(1));
                    myTable->searchKey(key);
                break;
                case 'o': //print out
                    myTable->printTable();
                break;
                case 'e': //end
                    running = 0;
                break;
            };
        }

        delete myTable;
    }

    return 1;
}