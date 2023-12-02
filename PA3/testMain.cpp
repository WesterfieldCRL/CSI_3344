#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <functional>

struct HuffmanNode {
    int data;
    char symbol;
    HuffmanNode *left, *right;

    HuffmanNode(int data, char symbol) : data(data), symbol(symbol), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
    bool operator()(HuffmanNode* left, HuffmanNode* right) const {
        return left->data > right->data;
    }
};

void buildHuffmanTree(const int chunkCounts[], std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes>& minHeap) {
    for (int i = 0; i < 256; ++i) {
        if (chunkCounts[i] > 0) {
            HuffmanNode* node = new HuffmanNode(chunkCounts[i], static_cast<char>(i));
            minHeap.push(node);
        }
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();

        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* mergedNode = new HuffmanNode(left->data + right->data, '\0');
        mergedNode->left = left;
        mergedNode->right = right;

        minHeap.push(mergedNode);
    }
}

void generateHuffmanCodes(HuffmanNode* root, std::unordered_map<char, std::string>& huffmanCodes, std::string currentCode = "") {
    if (root == nullptr) {
        return;
    }

    if (root->symbol != '\0') {
        huffmanCodes[root->symbol] = currentCode;
    }

    generateHuffmanCodes(root->left, huffmanCodes, currentCode + "0");
    generateHuffmanCodes(root->right, huffmanCodes, currentCode + "1");
}

void serializeTree(HuffmanNode* node, std::ofstream& outputFile) {
    if (node == nullptr) {
        outputFile.put(0); // Null marker
        return;
    }

    outputFile.put(1); // Non-null marker
    outputFile.put(node->symbol);
    serializeTree(node->left, outputFile);
    serializeTree(node->right, outputFile);
}

void encodeFile(const std::string& inputFileName, const std::string& outputFileName, const std::unordered_map<char, std::string>& huffmanCodes, HuffmanNode* root) {
    std::ofstream outputFile(outputFileName, std::ios::binary);

    if (outputFile.is_open()) {
        // Serialize the Huffman tree and write it to the file
        // For simplicity, we are using preorder traversal to serialize the tree
        serializeTree(root, outputFile);

        std::ifstream inputFile(inputFileName, std::ios::binary);
        if (inputFile.is_open()) {
            char byte;
            std::string encodedBits;

            while (inputFile.get(byte)) {
                encodedBits += huffmanCodes.at(byte);
            }

            // Write the size of the encoded data as an integer (4 bytes)
            int size = encodedBits.length();
            outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

            // Write the encoded bits
            for (std::size_t i = 0; i < encodedBits.length(); i += 8) {
                std::bitset<8> bits(encodedBits.substr(i, 8));
                char encodedByte = static_cast<char>(bits.to_ulong());
                outputFile.write(&encodedByte, sizeof(encodedByte));
            }

            inputFile.close();
            outputFile.close();
        } else {
            std::cerr << "Unable to open input file." << std::endl;
        }
    } else {
        std::cerr << "Unable to open output file." << std::endl;
    }
}

int main() {
    const int CHUNK_SIZE = 256;
    int chunkCounts[CHUNK_SIZE] = {0};

    std::ifstream file("testFile.txt", std::ios::binary);

    if (file.is_open()) {
        char byte;
        while (file.get(byte)) {
            chunkCounts[static_cast<unsigned char>(byte)]++;
        }

        file.close();

        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> minHeap;
        buildHuffmanTree(chunkCounts, minHeap);

        HuffmanNode* root = minHeap.top();

        std::unordered_map<char, std::string> huffmanCodes;
        generateHuffmanCodes(root, huffmanCodes);

        // Encode the file and include the Huffman tree in the compressed file
        encodeFile("testFile.txt", "compressed_file.bin", huffmanCodes, root);

        // Perform further actions using the compressed file as needed
    } else {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    return 0;
}

