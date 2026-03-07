#include <iostream>
#include <vector>

using namespace std;

struct Node {
public:
    vector<Node *> children = vector<Node*>(26, nullptr);
    bool isLeaf;
    int countOfPrefix;

    bool hasChildren() {
        for (int i = 0; i < 26; i++) {
            if(children[i] != nullptr)
                return true;
        }
        return false;
    }
};

class Trie {
private:
    Node* root;
    Node* removeWord(Node* root, string word, int depth = 0) {
        if (root == nullptr)
            return nullptr;

        if (depth == word.size()) {
            if (root->isLeaf) {
                root->isLeaf = false;
            }
            root->countOfPrefix--;

            //if the node has no other children then delete this node
            if (root->hasChildren() == false) {
                delete (root);
                root = nullptr;
            }
            return root;
        }

        char c = word[depth];
        root->children[c - 'a'] = removeWord(root->children[c - 'a'], word, depth + 1);

        root->countOfPrefix--;

        //if the node is not leaf node and has no other children then delete this node
        //deleting apple from trie [app, apple]. when root is at last p then p->isLeaf = true.
        //this means we have another word ending at this p so we cannot delete this p.
        //if trie[apple] then at last p we will have p->isLeaf = false and also it would not have any children
        //(deleted in the recursion above) so we can safely remove it.
        if (root->isLeaf == false && root->hasChildren() == false) {
            delete(root);
            root = nullptr;
        }
        return root;
    }

public:
    Trie() {
        root = new Node();
    }

    //insert a word into trie
    void insert(string word) {
        Node* node = root;
        for (char c : word) {
            if(node->children[c - 'a'] == nullptr) {
                node->children[c - 'a'] = new Node();
            }
            node->countOfPrefix++;

            //move to the reference trie
            node = node->children[c - 'a'];
        }
        node->isLeaf = true;
    }

    //search a word in Trie
    bool search(string word) {
        Node* node = root;
        for (char c : word) {
            if (node->children[c - 'a'] == nullptr)
                return false;
            node = node->children[c - 'a'];
        }
        return node->isLeaf;
    }

    //search prefix of a word in Trie
    bool startsWith(string prefix) {
        Node* node = root;

        for (char c : prefix) {
            if (node->children[c - 'a'] == nullptr)
                return false;
            node = node->children[c - 'a'];
        }

        //we finished traversing the prefix in trie.
        return true;
    }

    void removeWord(string word) {
        removeWord(root, word, 0);
    }
};


int main()
{
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