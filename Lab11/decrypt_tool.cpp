#include <iostream>
#include <fstream>
#include <string>

void xorEncryptDecrypt(const std::string& input, const std::string& key, const std::string& output) {
    std::ifstream inFile(input, std::ios::binary);
    std::ofstream outFile(output, std::ios::binary);
    
    if (!inFile || !outFile) {
        std::cerr << "Error: Unable to open file.\n";
        return;
    }

    char ch;
    size_t keyLen = key.length();
    size_t i = 0;

    while (inFile.get(ch)) {
        outFile.put(ch ^ key[i % keyLen]); // XOR operation
        i++;
    }

    inFile.close();
    outFile.close();
    std::cout << "Decryption complete. Output saved to " << output << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: decrypt_tool.exe <input_file> <key> <output_file>\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string key = argv[2];
    std::string outputFile = argv[3];

    xorEncryptDecrypt(inputFile, key, outputFile);
    return 0;
}
