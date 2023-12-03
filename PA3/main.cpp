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

};

struct CompareNodes {
    bool operator()(Node* left, Node* right) const {
        return left->count > right->count;
    }
};

void generateHuffmanCodes(Node* root, map<int, string>& huffmanCodes, string currentCode = "") {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr)
    {
        huffmanCodes[root->data] = currentCode;
    }

    generateHuffmanCodes(root->left, huffmanCodes, currentCode + "0");
    generateHuffmanCodes(root->right, huffmanCodes, currentCode + "1");
}

void writeTree(Node* node, ofstream& outputFile)
{
    if (node == nullptr)
    {
        outputFile.put(0);
        return;
    }
    else
    {
        outputFile.put(1);
        outputFile.put(node->data);
        writeTree(node->left, outputFile);
        writeTree(node->right, outputFile);
    }
}

void writeData(ofstream& outputFile, ifstream& inputFile, map<int, string>& huffmanCodes)
{

    string code;

    char byte;
    while (inputFile.get(byte))
    {
        code += huffmanCodes.at(static_cast<unsigned char>(byte));
    }

    int size = code.size();

    outputFile.write(reinterpret_cast<char*>(&size), sizeof(size));

    cout << size << endl;

    for (int i = 0; i < code.size(); i += 8)
    {
        bitset<8> bits(code.substr(i, 8));
        char encodedByte = static_cast<char>(bits.to_ulong());
        outputFile.put(encodedByte);
    }
}

Node* readTree(ifstream& inputFile)
{
    char marker;
    inputFile.get(marker);

    if (marker == 0)
    {
        return nullptr;
    }
    else
    {
        char symbol;
        inputFile.get(symbol);
        Node* node = new Node(0, static_cast<int>(symbol));
        node->left = readTree(inputFile);
        node->right = readTree(inputFile);
        return node;
    }
}

void printTree(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->left == nullptr && node->right == nullptr)
    {
        cout << "1" << endl;
        cout << static_cast<char>(node->data) << endl;
    }
    else
    {
        cout << "0" << endl;
        printTree(node->left);
        printTree(node->right);
    }
}

void printCodes(map<int, string>& huffmanCodes)
{
    for (auto it = huffmanCodes.begin(); it != huffmanCodes.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }
}

void huff(string source, string destination)
{
    vector<int> chunkCounts;

    ifstream file(source, ios::binary);

    if (file.is_open()) {

        char byte;
        while (file.get(byte)) {
            if (chunkCounts.size() <static_cast<unsigned char>(byte) + 1) {
                chunkCounts.resize(static_cast<unsigned char>(byte) + 1);
            }
            chunkCounts[static_cast<unsigned char>(byte)]++;
        }

        priority_queue<Node*, vector<Node*>, CompareNodes> minHeap;

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

        //printTree(minHeap.top());

        //printCodes(huffmanCodes);
        file.close();
        
        file.open(source, ios::binary);

        ofstream outputFile(destination, ios::binary);


        if (outputFile.is_open()) {

            outputFile.put(5); //Magic Number

            writeTree(minHeap.top(), outputFile);

            writeData(outputFile, file, huffmanCodes);

            outputFile.close();
        }
        else
        {
            cout << "Unable to open output file" << endl;
        }

        
    }
    else
    {
        cout << "Unable to open input file" << endl;
    }
}

void unhuff(string source, string destination)
{
    Node* root;
    ifstream inputFile(source, ios::binary);

    if (inputFile.is_open())
    {
        char magicNumber;
        inputFile.get(magicNumber);
        if (magicNumber != 5)
        {
            cout << "Invalid file" << endl;
            return;
        }
        root = readTree(inputFile);

        //printTree(root);

        map<int, string> huffmanCodes; 
        generateHuffmanCodes(root, huffmanCodes);

        //printCodes(huffmanCodes);

        ofstream outputFile(destination, ios::binary);
        
        if (outputFile.is_open())
        {
            int size;
            inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));

            cout << size << endl;

            char byte;
            string encodedBits;
            while (inputFile.get(byte)) {
                encodedBits += bitset<8>(byte).to_string();
            }

            encodedBits = encodedBits.substr(0, size);

            Node* current = root;
            for (char bit : encodedBits) {
                if (bit == '0') {
                    current = current->left;
                } else {
                    current = current->right;
                }

                if (current->left == nullptr && current->right == nullptr) {
                    outputFile.put(current->data);
                    current = root;
                }
            }

            inputFile.close();
            outputFile.close();
        }
        else
        {
            cout << "Unable to open file" << endl;
        }

        inputFile.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
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