//
// Created by Morgan Funtowicz on 9/12/2024.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <spdlog/spdlog.h>
#include "kitok/kitok.hpp"


int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << "You need to provide the folder where to find tokenizer_config.json and tokenizer.json";
        return 1;
    }

    const auto folder = std::filesystem::path(argv[1]);
    if(const auto maybeVocab = kitok::kitok_vocabulary_from_tokenizers(folder); maybeVocab.has_value()){
        const auto vocab = *maybeVocab;
        SPDLOG_INFO("Successfully read vocabulary content {}", vocab.size());
    } else {
        SPDLOG_ERROR("Failed to read vocabulary content: {}", maybeVocab.error());
    }

    return 0;
}