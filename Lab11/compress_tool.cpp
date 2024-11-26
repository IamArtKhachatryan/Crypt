#include <iostream>
#include <fstream>
#include <string>

std::string compress(const std::string& input) {
    std::string compressed;
    size_t len = input.length();

    for (size_t i = 0; i < len; ++i) {
        size_t count = 1;
        while (i + 1 < len && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        compressed += input[i];
        compressed += std::to_string(count);
    }

    return compressed;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: compress_tool.exe <input_file_or_text> <output_file>\n";
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

    std::string compressed = compress(data);

    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Unable to write to output file.\n";
        return 1;
    }
    outFile << compressed;
    outFile.close();

    std::cout << "Compression complete. Output saved to " << outputFile << "\n";
    return 0;
}
