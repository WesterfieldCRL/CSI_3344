#include <iostream>
#include <fstream>
#include <cstdint>
#include <bitset>
#include <vector>
#include <iomanip>
#include <queue>
#include <map>

using namespace std;

struct Node
{
    int count;
    int data;
    Node* left;
    Node* right;
    Node(int count, int data) : count(count), data(data), left(nullptr), right(nullptr) {}

    bool operator<(const Node& rhs) const
    {
        return count < rhs.count;
    }

    bool operator>(const Node& rhs) const
    {
        return count > rhs.count;
    }

    bool operator==(const Node& rhs) const
    {
        return count == rhs.count;
    }

};

void generateHuffmanCodes(Node* root, map<int, string>& huffmanCodes, std::string currentCode = "") {
    if (root == NULL) {
        return;
    }

    /*if (root->data != -1) {
        huffmanCodes[root->data] = currentCode;
    }*/
    if (root->left == NULL && root->right == NULL)
    {
        huffmanCodes[root->data] = currentCode;
    }

    generateHuffmanCodes(root->left, huffmanCodes, currentCode + "0");
    generateHuffmanCodes(root->right, huffmanCodes, currentCode + "1");
}

void huff(string source, string destination)
{
    vector<int> chunkCounts;

    ifstream file("testFile.txt", std::ios::binary);

    if (file.is_open()) {
        char byte;
        while (file.get(byte)) {
            if (chunkCounts.size() < static_cast<unsigned char>(byte) + 1) {
                chunkCounts.resize(static_cast<unsigned char>(byte) + 1);
            }
            chunkCounts[static_cast<unsigned char>(byte)]++;
        }

        priority_queue<Node*> minHeap;

        for (int i = 0; i < chunkCounts.size(); ++i) {
            if (chunkCounts[i] > 0) {
                Node* node = new Node(chunkCounts[i], i);
                minHeap.push(node);
            }
        }

        while (minHeap.size() > 1) {
            Node* left = minHeap.top();
            minHeap.pop();

            Node* right = minHeap.top();
            minHeap.pop();

            Node* mergedNode = new Node(left->count + right->count, -1);
            mergedNode->left = left;
            mergedNode->right = right;

            minHeap.push(mergedNode);
        }

        

        map<int, string> huffmanCodes;
        generateHuffmanCodes(minHeap.top(), huffmanCodes);

        for (int i = 0; i < huffmanCodes.size(); ++i) {
            cout << huffmanCodes[i] << endl;
        }

        file.close();
    }
}

void unhuff(string source, string destination)
{

}

int main (int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " -huff/-unhuff <source> <destination>" << endl;
        return 1;
    }
    else if ((string)argv[1] == "-huff")
    {
        huff(argv[2], argv[3]);
    }
    else if ((string)argv[1] == "-unhuff")
    {
        unhuff(argv[2], argv[3]);
    }
    else
    {
        cout << "Usage: " << argv[0] << " -huff/-unhuff <source> <destination>" << endl;
        return 1;
    }

    return 0;
}