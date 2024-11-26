#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

// XOR encryption/decryption
std::string xorEncryptDecrypt(const std::string& input, const std::string& key) {
    std::string result = input;
    size_t keyLen = key.length();

    for (size_t i = 0; i < input.length(); i++) {
        result[i] = input[i] ^ key[i % keyLen];
    }

    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: encrypt_tool.exe <text_or_file_path> <key> <output_file>\n";
        return 1;
    }

    std::string input = argv[1];
    std::string key = argv[2];
    std::string outputFile = argv[3];

    std::string data;

    if (std::filesystem::exists(input)) {
        std::ifstream inFile(input, std::ios::binary);
        if (!inFile) {
            std::cerr << "Error: Unable to open file.\n";
            return 1;
        }
        data.assign((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        inFile.close();
    } else {
        data = input;
    }

    std::string encrypted = xorEncryptDecrypt(data, key);

    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Unable to write to output file.\n";
        return 1;
    }
    outFile << encrypted;
    outFile.close();

    std::cout << "Encryption complete. Output saved to " << outputFile << "\n";
    return 0;
}
