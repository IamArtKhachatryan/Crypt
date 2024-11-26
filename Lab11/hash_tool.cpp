#include <iostream>
#include <fstream>
#include <string>
#include <functional> 

std::size_t computeHash(const std::string& data) {
    std::hash<std::string> hasher;
    return hasher(data);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: hash_tool.exe <input_file_or_text>\n";
        return 1;
    }

    std::string input = argv[1];
    std::string data;

    std::ifstream inFile(input, std::ios::binary);
    if (inFile) {
        data.assign((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        inFile.close();
    } else {
        data = input;
    }

    std::size_t hashValue = computeHash(data);

    std::cout << "Hash Value: " << hashValue << "\n";
    return 0;
}
