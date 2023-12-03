/*
Author: Wesley Anastasi
Class: CSI 3344
Due Date: December 3, 2023
*/

/*
This program uses Huffman's algorithm to compress and decompress files. It
takes in a file and outputs a compressed version of the file. It can also
take in a compressed file and output the original file.

huff takes in a file and outputs a compressed version of the file. It does
this by first reading the file and counting the number of times each byte
occurs. It then uses a priority queue to create a Huffman tree. It then
uses the Huffman tree to generate Huffman codes for each byte. It then
writes the Huffman tree to the output file, followed by the encoded data.

unhuff takes in a compressed file and outputs the original file. It does
this by first reading the Huffman tree from the file. It then uses the
Huffman tree to decode the data and write it to the output file.

*/

#include <iostream>
#include <fstream>
#include <cstdint>
#include <bitset>
#include <vector>
#include <iomanip>
#include <queue>
#include <map>

using namespace std;

int magicNumber = 5;

/**
 * Node
 * 
 * A node for a Huffman tree
 */
struct Node
{
    int count;
    int data;
    Node* left;
    Node* right;
    Node(int count, int data) : count(count), data(data), left(nullptr), right(nullptr) {}

};

/**
 * CompareNodes
 * 
 * A comparator for the priority queue
 */
struct CompareNodes {
    bool operator()(Node* left, Node* right) const {
        return left->count > right->count;
    }
};

/**
 * generateHuffmanCodes
 * 
 * Generates Huffman codes for each byte in the file
 * 
 * Parameters:
 *   root - the root of the Huffman tree
 *   huffmanCodes - a map to store the Huffman codes
 *   currentCode - the current Huffman code with a default value of ""
 * 
 * Return value: none
 */
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

/**
 * writeTree
 * 
 * Writes the Huffman tree to the output file
 * 
 * Parameters:
 *   node - the current node
 *   outputFile - the output file
 * 
 * Return value: none
 */
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

/**
 * writeData
 * 
 * Writes the encoded data to the output file
 * 
 * Parameters:
 *   outputFile - the output file
 *   inputFile - the input file
 *   huffmanCodes - the Huffman codes
 * 
 * Return value: none
 */
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

/**
 * readTree
 * 
 * Reads the Huffman tree from the input file
 * 
 * Parameters:
 *   inputFile - the input file
 * 
 * Return value: the root of the Huffman tree
 */
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

/**
 * printTree
 * 
 * Prints the Huffman tree
 * 
 * Parameters:
 *   node - the current node
 * 
 * Return value: none
 */
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

/**
 * printCodes
 * 
 * Prints the Huffman codes
 * 
 * Parameters:
 *   huffmanCodes - the Huffman codes
 * 
 * Return value: none
 */
void printCodes(map<int, string>& huffmanCodes)
{
    for (auto it = huffmanCodes.begin(); it != huffmanCodes.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }
}

/**
 * huff
 * 
 * Performs Huffman compression on a file and outputs the compressed file
 * to the destination
 * 
 * Parameters:
 *   source - the source file
 *   destination - the destination file
 * 
 * Return value: none
 */
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

            outputFile.put(magicNumber);

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

/**
 * unhuff
 * 
 * Performs Huffman decompression on a file and outputs the decompressed file
 * to the destination
 * 
 * Parameters:
 *   source - the source file
 *   destination - the destination file
 * 
 * Return value: none
 */
void unhuff(string source, string destination)
{
    Node* root;
    ifstream inputFile(source, ios::binary);

    if (inputFile.is_open())
    {
        char magicNumber;
        inputFile.get(magicNumber);
        if (magicNumber != magicNumber)
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

/**
 * main
 * 
 * Gets input from command line and calls huff or unhuff
 * If arguments are invalid, prints usage
 * 
 * Parameters:
 *   argc - number of arguments passed
 *   argv - array of arguments passed
 * 
 * Return value: integer representing success or failure
 */
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