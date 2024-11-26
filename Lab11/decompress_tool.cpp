#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

std::string decompress(const std::string& input) {
    std::string decompressed;
    size_t len = input.length();

    for (size_t i = 0; i < len; ++i) {
        char ch = input[i];
        std::string countStr;
        while (i + 1 < len && std::isdigit(input[i + 1])) {
            countStr += input[++i];
        }
        size_t count = std::stoi(countStr);
        decompressed.append(count, ch);
    }

    return decompressed;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: decompress_tool.exe <input_file_or_text> <output_file>\n";
        return 1;
    }

    std::string input = argv[1];
    std::string outputFile = argv[2];
    std::string data;

    std::ifstream inFile(input, std::ios::binary);
    if (inFile) {
        data.assign((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        inFile.close();
    } else {
        data = input;
    }

    std::string decompressed = decompress(data);

    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Unable to write to output file.\n";
        return 1;
    }
    outFile << decompressed;
    outFile.close();

    std::cout << "Decompression complete. Output saved to " << outputFile << "\n";
    return 0;
}
