#include<iostream>
#include<unordered_map>

using namespace std;

class Node{
    public:
    char data;
    unordered_map<char, Node*> children;
    char terminal;  // boolean value of whether it is the last/terminal node

    Node(char d){
        data = d;
        terminal = false;  
    }
};

class Trie{

    Node* root;
    int cnt;

    public:

    Trie(){
        root = new Node('\0');
        cnt = 0;
    }

    void insert(char *w){
        Node* temp = root;
        for(int i = 0; w[i] !='\0'; i++){
            char ch = w[i];
            if(temp -> children.count(ch)){
                temp = temp -> children[ch];
            }
            else{
                Node* n = new Node(ch);
                temp -> children[ch] = n;
                temp = n;
            }
        }
        temp -> terminal = true;
    }

    bool find(char *w){
        Node* temp = root;
        for(int i = 0; w[i]!='\0'; i++){
            char ch = w[i];
            if(temp -> children.count(ch)){
                temp = temp -> children[ch];
            }
            else{
                return false;
            }
        }
        return temp -> terminal;
    }
};

int main(){

    Trie t;
    char words[][10] = {"a", "hello", "news", "not", "apple"};

    char w[10];
    cout<<"ENTER THE WORD YOU WANT TO SEARCH:";
    cin>>w;

    for(int i = 0; i < 5; i++){
        t.insert(words[i]);
    }

    if(t.find(w)){
        cout<<"PRESENT";
    }
    else{
        cout<<"ABSENT";
    }
    return 0;
}