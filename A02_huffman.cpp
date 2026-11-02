/*
    DAA Assignment A2: Huffman Encoding using Greedy Strategy

    Compile:
        g++ -std=c++17 -O2 A2_Huffman_Encoding.cpp -o A2_Huffman_Encoding

    Input:
        Number of distinct symbols
        Then enter: symbol frequency
        Example:
            5
            a 5
            b 9
            c 12
            d 13
            e 16

    The program builds a Huffman tree, prints each symbol's prefix code,
    and calculates the total number of encoded bits for the given frequencies.
*/

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
using namespace std;

// One node of the Huffman tree.
struct Node {
    char symbol;
    unsigned long long frequency;
    Node* left;
    Node* right;

    Node(char s, unsigned long long f, Node* l = nullptr, Node* r = nullptr)
        : symbol(s), frequency(f), left(l), right(r) {}

    // A node with children is an internal node; leaves contain symbols.
    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

// priority_queue is a max-heap by default.
// This comparator makes it behave as a min-heap by frequency.
struct CompareFrequency {
    bool operator()(const Node* a, const Node* b) const {
        return a->frequency > b->frequency;
    }
};

// Traverse the tree to generate codes.
// Going left adds 0; going right adds 1.
void generateCodes(Node* root, const string& currentCode,
                   vector<pair<char, string>>& codes) {
    if (root == nullptr) return;

    if (root->isLeaf()) {
        // A single-symbol input needs at least one bit as its code.
        string finalCode = currentCode.empty() ? "0" : currentCode;
        codes.push_back({root->symbol, finalCode});
        return;
    }

    generateCodes(root->left, currentCode + "0", codes);
    generateCodes(root->right, currentCode + "1", codes);
}

// Free dynamically allocated tree nodes.
void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    int n;
    cout << "Enter number of distinct symbols: ";
    cin >> n;

    if (n <= 0 || n > 256) {
        cout << "Enter a number from 1 to 256.\n";
        return 0;
    }

    priority_queue<Node*, vector<Node*>, CompareFrequency> minHeap;
    map<char, unsigned long long> inputFrequency;

    cout << "Enter each symbol and its positive frequency:\n";
    for (int i = 0; i < n; i++) {
        char symbol;
        unsigned long long frequency;
        cin >> symbol >> frequency;

        if (frequency == 0) {
            cout << "Frequency must be positive.\n";
            while (!minHeap.empty()) {
                delete minHeap.top();
                minHeap.pop();
            }
            return 0;
        }

        inputFrequency[symbol] = frequency;
        minHeap.push(new Node(symbol, frequency));
    }

    // Greedy construction:
    // Repeatedly combine the two nodes with the smallest frequencies.
    while (minHeap.size() > 1) {
        Node* first = minHeap.top();
        minHeap.pop();

        Node* second = minHeap.top();
        minHeap.pop();

        // The new internal node stores the sum of the two frequencies.
        Node* parent = new Node('\0',
                                first->frequency + second->frequency,
                                first, second);

        minHeap.push(parent);
    }

    Node* root = minHeap.top();

    vector<pair<char, string>> codes;
    generateCodes(root, "", codes);

    cout << "\nHuffman Codes:\n";
    cout << left << setw(12) << "Symbol"
         << setw(15) << "Frequency" << "Code\n";

    unsigned long long totalBits = 0;
    for (const auto& entry : codes) {
        char symbol = entry.first;
        const string& code = entry.second;

        cout << left << setw(12) << symbol
             << setw(15) << inputFrequency[symbol] << code << '\n';
    }

    // Calculate the weighted path length = sum(frequency * code length).
    // This is the total number of bits needed for the supplied frequencies.
    // Traverse the original leaves to match their code lengths.
    // The input frequencies are stored in the leaf nodes.
    vector<Node*> stack;
    stack.push_back(root);
    while (!stack.empty()) {
        Node* node = stack.back();
        stack.pop_back();

        if (node->isLeaf()) {
            for (const auto& entry : codes) {
                if (entry.first == node->symbol) {
                    totalBits += node->frequency * entry.second.size();
                    break;
                }
            }
        } else {
            if (node->left) stack.push_back(node->left);
            if (node->right) stack.push_back(node->right);
        }
    }

    cout << "\nTotal encoded bits for the given frequencies: "
         << totalBits << '\n';
    cout << "Tree construction uses a min-priority queue.\n";
    cout << "Time complexity: O(n log n); space complexity: O(n).\n";

    deleteTree(root);
    return 0;
}




