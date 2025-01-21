#include <bits/stdc++.h>
using namespace std;

// Definition of Node
struct Node {
    Node* links[26]; // Array to store references to child nodes (for 'a' to 'z')
    bool flag = false; // Flag to mark the end of a word
    unordered_map<string, int> freqMap; // Map to store the frequency of words passing through or ending at this node
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> minHeap; // Min-heap to store top K frequent terms

    // Checks if the node contains a reference for the given character
    bool containsKey(char ch) {
        return (links[ch - 'a'] != NULL);
    }

    // Adds a reference to the given character in the child array
    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    // Retrieves the reference to the next node for the given character
    Node* get(char ch) {
        return links[ch - 'a'];
    }

    // Marks the current node as the end of a word
    void setEnd() {
        flag = true;
    }

    // Checks if the current node marks the end of a word
    bool isEnd() {
        return flag == true;
    }
};

// Definition of Trie
class Trie {
private:
    Node* root; // Root of the Trie
    int K; // Number of top frequent terms to maintain (top K)

public:
    // Constructor to initialize the Trie and set the value of K
    Trie(int k) {
        root = new Node();
        K = k;
    }

    // Inserts a word into the Trie and updates its frequency
    void insert(string word) {
        Node* node = root; // Start at the root of the Trie
        for (char ch : word) { // Traverse each character in the word
            if (!node->containsKey(ch)) { // If the current character is not present, add it
                node->put(ch, new Node());
            }
            node = node->get(ch); // Move to the next node

            // Update the frequency map and maintain the top K terms in the min-heap
            node->freqMap[word]++; // Increment the frequency of the word at this node
            updateHeap(node, word); // Update the min-heap for this node
        }
        node->setEnd(); // Mark the last node as the end of the word
    }

    // Updates the min-heap for a node to maintain the top K frequent terms
    void updateHeap(Node* node, string word) {
        int freq = node->freqMap[word]; // Get the frequency of the current word
        auto& heap = node->minHeap; // Reference to the min-heap of the node

        // Check if the word already exists in the heap
        bool exists = false; // Flag to indicate if the word is already in the heap
        vector<pair<int, string>> temp; // Temporary vector to store heap elements
        while (!heap.empty()) { // Traverse the heap
            if (heap.top().second == word) { // If the word is found in the heap
                heap.pop(); // Remove it from the heap
                exists = true; // Mark as found
                break;
            }
            temp.push_back(heap.top()); // Store the current heap element in the temporary vector
            heap.pop(); // Remove the current element from the heap
        }
        for (auto& p : temp) { // Push all elements back into the heap
            heap.push(p);
        }

        // Add the updated word to the heap
        heap.push({freq, word}); // Add the current word with its updated frequency
        if (heap.size() > K) { // If the heap size exceeds K
            heap.pop(); // Remove the least frequent word
        }
    }

    // Retrieves the top K frequent terms with a given prefix
    vector<string> getTopK(string prefix) {
        Node* node = root; // Start at the root of the Trie
        for (char ch : prefix) { // Traverse each character in the prefix
            if (!node->containsKey(ch)) { // If the prefix does not exist, return an empty result
                return {};
            }
            node = node->get(ch); // Move to the next node
        }

        // Extract terms from the min-heap at the node
        vector<string> result;
        auto heap = node->minHeap; // Make a copy of the heap to preserve its state
        while (!heap.empty()) { // Traverse the heap
            result.push_back(heap.top().second); // Add the word to the result
            heap.pop(); // Remove the top element
        }
        reverse(result.begin(), result.end()); // Reverse the result to get descending order of frequency
        return result; // Return the list of top K terms
    }
};

// Example usage of the Trie
int main() {
    Trie trie(3); // Initialize a Trie with K = 3 for top 3 terms

    // Insert words and update their frequencies
    trie.insert("apple");
    trie.insert("app");
    trie.insert("app");
    trie.insert("apple");
    trie.insert("ape");
    trie.insert("apex");
    trie.insert("apex");
    trie.insert("apex");
    trie.insert("applause");

    // Retrieve top K terms for the prefix "app"
    vector<string> topK = trie.getTopK("app");
    for (string s : topK) { // Print the result
        cout << s << " ";
    }

    return 0;
}


/*
Insert:

Time Complexity: O(L + logK), where:
- L is the length of the word being inserted.
- logK is the cost of maintaining the min-heap for the top K frequent terms at each node.

Space Complexity: O(L × N), where:
- L is the maximum length of the word being stored in the Trie.
- N is the total number of unique words stored in the Trie.

Retrieve Top K:

Time Complexity: O(L + K), where:
- L is the length of the prefix being queried.
- K is the size of the min-heap used to return the top K frequent terms.

Space Complexity: O(K), as the min-heap is used temporarily during retrieval.
*/
