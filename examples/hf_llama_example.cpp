//
// Created by Morgan Funtowicz on 9/12/2024.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include "kitok/kitok.hpp"


int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << "You need to provide the folder where to find tokenizer_config.json and tokenizer.json";
        return 1;
    }

    const auto folder = std::filesystem::path(argv[1]);

    auto vocab = kitok::kitok_vocabulary_from_tokenizers(folder);
    return 0;
}