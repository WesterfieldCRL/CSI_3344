#include <iostream>
#include <fstream>
#include <bitset>

struct HuffmanNode {
    int data;
    char symbol;
    HuffmanNode *left, *right;

    HuffmanNode(int data, char symbol) : data(data), symbol(symbol), left(nullptr), right(nullptr) {}
};

// Deserialize Huffman tree from the compressed file
HuffmanNode* deserializeTree(std::ifstream& inputFile) {
    char marker;
    inputFile.get(marker);

    if (marker == 0) {
        return nullptr;
    } else {
        char symbol;
        inputFile.get(symbol);
        HuffmanNode* node = new HuffmanNode(0, symbol);
        node->left = deserializeTree(inputFile);
        node->right = deserializeTree(inputFile);
        return node;
    }
}

// Function to delete the Huffman tree after decoding
void deleteTree(HuffmanNode* root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

// Decode the compressed file using the Huffman tree
void decodeFile(const std::string& inputFileName, const std::string& outputFileName) {
    std::ifstream inputFile(inputFileName, std::ios::binary);
    std::ofstream outputFile(outputFileName, std::ios::binary);

    if (inputFile.is_open() && outputFile.is_open()) {
        // Deserialize Huffman tree from the compressed file
        HuffmanNode* root = deserializeTree(inputFile);

        // Read the size of the encoded data
        int size;
        inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));

        // Read the encoded bits
        char byte;
        std::string encodedBits;
        while (inputFile.get(byte)) {
            encodedBits += std::bitset<8>(byte).to_string();
        }

        // Trim the extra bits
        encodedBits = encodedBits.substr(0, size);

        // Decode the bits and write to the output file
        HuffmanNode* current = root;
        for (char bit : encodedBits) {
            if (bit == '0') {
                current = current->left;
            } else {
                current = current->right;
            }

            if (current->left == nullptr && current->right == nullptr) {
                // Leaf node reached, write the symbol to the output file
                outputFile.put(current->symbol);
                current = root; // Reset to the root for the next symbol
            }
        }

        // Clean up the Huffman tree
        deleteTree(root);

        inputFile.close();
        outputFile.close();
    } else {
        std::cerr << "Unable to open files." << std::endl;
    }
}

int main() {
    // Decode the compressed file and create a text file
    decodeFile("compressed_file.bin", "decompressed_file.txt");

    // Perform further actions using the decompressed file as needed

    return 0;
}
