struct Node{
    Node* links[26];
    bool flag = false;

    bool containsKey(char ch){
        return (links[ch - 'a'] != NULL);
    }

    void put(char ch, Node *node){
        links[ch - 'a'] = node;
    }

    Node* get(char ch){
        return links[ch - 'a'];
    }

    void setEnd(){
        flag = true;
    }

    bool isEnd(){
        return flag == true;
    }
};

class Trie {

private:
    Node* root;

public:
    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        Node* node = root;
        int len = word.length();
        for(int i = 0; i < len; i++){
            if(!node -> containsKey(word[i])){
                node -> put(word[i], new Node());
            }
            //moves to the next reference trie
            node = node -> get(word[i]);
        }

        node -> setEnd();
    }
    
    bool search(string word) {
        Node* node = root;
        for(int i = 0; i < word.length(); i++){
            if(!node -> containsKey(word[i])){
                return false;
            }
            node = node -> get(word[i]);
        }
        return node -> isEnd();
    }
    
    bool startsWith(string prefix) {
        Node* node = root;
        for(int i = 0; i < prefix.length(); i++){
            if(!node -> containsKey(prefix[i])){
                return false;
            }
            node = node -> get(prefix[i]);
        }

        return true;
    }
};

/*
Complexity Analysis:

1. Insert Operation:
   - Time Complexity: O(L), where L is the length of the word being inserted.
     - For each character in the word, we either traverse or create a new node in the Trie.
   - Space Complexity: O(L), where L is the length of the word.
     - Space is used to create new nodes in the Trie for each unique character in the word.

2. Search Operation:
   - Time Complexity: O(L), where L is the length of the word being searched.
     - For each character in the word, we traverse the Trie nodes.
   - Space Complexity: O(1), as no extra space is used during the search.

3. startsWith Operation:
   - Time Complexity: O(L), where L is the length of the prefix being checked.
     - For each character in the prefix, we traverse the Trie nodes.
   - Space Complexity: O(1), as no extra space is used during the prefix check.

Overall:
- Insert, search, and startsWith all have **linear time complexity** with respect to the length of the input string (word or prefix).
- Space usage grows proportionally to the total number of unique characters stored across all inserted words.
*/


/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
