
#ifndef ASSIGNMENT4_TREE_H
#define ASSIGNMENT4_TREE_H

#include <map>
#include <string>
#include <vector>

using namespace std;


class Tree {
public:
    map<char, string> encode;//characters and their codes

    struct Node
    {
        char ch;
        int freq;
        Node* right;
        Node* left;

    };
    Node*root;

    struct compare
    {
        bool operator()(Node* l, Node* r)
        {
            return (l->freq < r->freq);
        }
    };
    vector<Node*> nodeVector;


    void initialFreq(string str);
    void HuffmanTree(vector<Node*> g);
    void saveTable(Node *root, ofstream& outFile);
    void codes(struct Node* root, string str);

    void encodeString(string s);
    void decode(string decode);
    void character(string character);

};


#endif

