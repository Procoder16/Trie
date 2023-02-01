#include<bits/stdc++.h>
using namespace std;

struct Node{
    Node* links[26];

    bool containsKey(char ch){
        return links[ch - 'a'] != NULL;
    }

    void put(char ch, Node* node){
        links[ch - 'a'] = node;
    }

    Node* get(char ch){
        return links[ch - 'a'];
    }
};

class Trie{
    Node* root;
    public:

    Trie(){
        root = new Node();
    }

    void insert(string word, int &count){
        Node* node = root;
        int len = word.length();
        for(int i = 0; i < len; i++){
            if(!node -> containsKey(word[i])){
                node -> put(word[i], new Node());
                count++;
            }
            node = node -> get(word[i]);
        }
    }
};

int countDistinctSubstrings(string &s){
    Trie *obj = new Trie();
    int count = 0;

    for(int i = 0; i < s.length(); i++){
        string str = s.substr(i);
        obj -> insert(str, count);
    }

    count++;

    return count;
}