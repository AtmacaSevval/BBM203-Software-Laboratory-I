

#include "Tree.h"

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;


void Tree::initialFreq(string file)
{

    map<char, int> freq;//characters and their frequences
    for (int i=0; i<file.size(); i++) {
        freq[file[i]]++;
    }

    for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++){//adding each of them to vector as a node
        Node* node = new Node();
        node->ch = v->first;
        node->freq = v->second;
        node->left = NULL;
        node->right = NULL;
        nodeVector.push_back(node);
    }

    HuffmanTree(nodeVector);

}

void Tree::HuffmanTree(vector<Node*> nodeVector) {

    std::sort(nodeVector.begin(), nodeVector.end(), compare());
    vector<Node*> g1 = nodeVector;


    Node* tempLeft = new Node();
    Node* tempRight = new Node();
    Node* tempTop;

    int size = g1.size();
    for(int i = 0; i<size -1 ;i++){// take the lowest two frequencies
        tempLeft = g1[0];
        g1.erase(g1.begin());

        tempRight = g1[0];
        g1.erase(g1.begin());

        tempTop = new Node();//combine them and add as a new node
        tempTop->ch = '$';
        tempTop->freq = tempLeft->freq + tempRight->freq;
        tempTop->left = tempLeft;
        tempTop->right = tempRight;
        g1.push_back(tempTop);

        std::sort(g1.begin(), g1.end(), compare());//sort from small to large after add a node
    }

    root = tempTop;
    codes(root,"");

    std::ofstream outfile("table.txt");
    saveTable(root ,outfile);
    outfile.close();
}

void Tree::codes(Node* root, string str)//save codes of character to a map
{

    if (root->left == NULL && root->right == NULL) {
        encode[root->ch] = str;
        return;
    }
    codes(root->left, str + '0');
    codes(root->right, str + '1');

}


void Tree::saveTable(Node*tree, ofstream& outFile) {//save codes to "table.txt"
    if (tree == NULL) {
        return;
    }
    if (tree != NULL)
    {
        if(tree->ch != '$'){
            outFile << tree->ch << " "<<encode[tree->ch]<< "\n";
        }
        saveTable( tree->left,outFile);
        saveTable( tree->right,outFile);
    }
}


void Tree::encodeString(string file){

    string encodedString;
    for (int i=0; i<file.size(); i++) {//find codes of each character and add to a string to print
        encodedString += encode[file[i]];
    }
    cout<<encodedString<<"\n";
}

void Tree::character(string character) {

    string myText;
    ifstream MyReadFile("table.txt");

    while (getline (MyReadFile, myText)) {
        std::istringstream iss(myText);//seperate each line's character and code
        std::string ch,code;
        iss >> ch >> code;
        if(ch == character){
            cout<<code<<"\n";
            break;
        }
    }

    MyReadFile.close();
}

void Tree::decode(string decode){

    map<char, string> decode1;
    string decodedString;

    string myText;
    ifstream MyReadFile("table.txt");

    while (getline (MyReadFile, myText)) {// add characters and codes a map
        std::istringstream iss(myText);
        std::string ch,code;
        iss >> ch >> code;
        char c = ch[0];
        decode1[c] = code;
    }

    MyReadFile.close();

    string s;
    for (int i = 0; i < decode.size(); i++){
        s += decode[i];
        for (map<char, string>::iterator v=decode1.begin(); v!=decode1.end(); v++) {
            if( s == v->second){
                decodedString += v->first;
                s = "";
            }
        }
    }

    cout<<decodedString<<"\n";

}

