#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    
    Examples:
    ---------
    
    Approach:
    ----------
    Insert {app}                                                     |
                                    []              - level=0   word{app}
                                  /                                   |
                                 a                  - level=1   word{app}
                            {eow=false
                         countOfPrefix=1}
                              /                                        | 
                             p                      - level=2   word{app}
                        {eow=false
                     countOfPrefix=1}
                          /                                              |
                         p                          - level=3   word{app}
                    {eow=true
                 countOfPrefix=1}

    Insert {apple}                                                   |
                                    []              - level=0   word{apple}
                                  /                                   |
                                 a                  - level=1   word{apple}
                            {eow=false
                         countOfPrefix=2}
                              /                                        |
                             p                      - level=2   word{apple}
                        {eow=false
                     countOfPrefix=2}
                          /                                             |
                         p                          - level=3   word{apple}
                    {eow=true
                 countOfPrefix=2}
                     /                                                   |               
                    l                               - level=4   word{apple}
                 {eow=false
             countOfPrefix=1}
                 /                                                         |
                e                                   - level=5   word{apple}
             {eow=true
          countOfPrefix=1}

    
    
*/

struct TrieNode {
    vector<TrieNode*> children = vector<TrieNode*>(26, nullptr);
    bool isEndOfWord = false;
    int countOfPrefix = 0;

    //used in remove word to determine if the node can be deleted or not
    bool hasChildren() {
        for (int i = 0; i < 26; i++) {
            if (children[i] != nullptr)
                return true;
        }
        return false;
    }
};

class Trie {
    TrieNode* root;

    //delete the node in a post order fashion
    TrieNode* removeWordUtil(TrieNode* root, string& word, int level) {
        if (root == nullptr)
            return root;

        if (level == word.length()) {
            root->countOfPrefix--;

            if (root->isEndOfWord)
                root->isEndOfWord = false;

            if (root->hasChildren() == false) {
                delete(root);
                root = nullptr;
            }

            return root;
        }

        char c = word[level];
        root->children[c - 'a'] = removeWordUtil(root->children[c - 'a'], word, level + 1);
        root->countOfPrefix--;

        //if the node is not leaf node and has no other children then delete this node
        //deleting apple from trie [app, apple]. when root is at last p then p->isLeaf = true.
        //this means we have another word ending at this p so we cannot delete this p.
        //if trie[apple] then at last p we will have p->isLeaf = false and also it would not have any children
        //(deleted in the recursion above) so we can safely remove it.
        if (root->isEndOfWord && root->hasChildren() == false) {
            delete(root);
            root = nullptr;
        }
        
        return root;
    }
public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* current = root;
        for (char &c : word) {
            //if the current character doesnot exists in the trie
            if (current->children[c - 'a'] == nullptr) {
                current->children[c - 'a'] = new TrieNode();
            }
            //goto that character node in trie.
            current = current->children[c - 'a'];
            current->countOfPrefix++;
        }
        //set this as the end of word in trie
        current->isEndOfWord = true;

        cout << "Inserted word: " << word << endl;
    }

    bool search(string word) {
        TrieNode* current = root;

        for (char& c : word) {
            //if the current character doesnot exist in the trie return false
            if (current->children[c - 'a'] == nullptr) {
                return false;
            }
            //goto that character node in trie.
            current = current->children[c - 'a'];
        }

        //is this the end of word in trie
        return current->isEndOfWord == true;
    }

    bool startsWith(string prefix) {
        TrieNode* current = root;

        for (char& c : prefix) {
            //if the current character doesnot exist in the trie return false
            if (current->children[c - 'a'] == nullptr) {
                return false;
            }
            //goto that character node in trie.
            current = current->children[c - 'a'];
        }

        //we finished traversing the prefix in trie.
        return true;
    }

    void removeWord(string word) {
        removeWordUtil(root, word, 0);
        cout << "Removed word: " << word << endl;
    }
};

int main() {
    
    Trie* trie = new Trie();
    trie->insert("apple");
    trie->insert("app");

    trie->search("app") == true ? cout << "app: Found" << endl : cout << "app: Not Found" << endl;
    trie->search("apple") == true ? cout << "apple: Found" << endl : cout << "apple: Not Found" << endl;
    trie->search("ap") == true ? cout << "ap: Found" << endl : cout << "ap: Not Found" << endl;
    trie->startsWith("ap") == true ? cout << "ap: Found Prefix" << endl : cout << "ap: Not Found Prefix" << endl;

    trie->removeWord("apple");

    trie->search("app") == true ? cout << "app: Found" << endl : cout << "app: Not Found" << endl;
    trie->search("apple") == true ? cout << "apple: Found" << endl : cout << "apple: Not Found" << endl;
    trie->search("ap") == true ? cout << "ap: Found" << endl : cout << "ap: Not Found" << endl;
    trie->startsWith("ap") == true ? cout << "ap: Found Prefix" << endl : cout << "ap: Not Found Prefix" << endl;

    return 0;
}