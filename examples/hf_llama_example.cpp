//
// Created by Morgan Funtowicz on 9/12/2024.
//
#include <chrono>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <spdlog/fmt/chrono.h>
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

        const auto start = std::chrono::steady_clock::now();
        const auto id = vocab["am"];
        const auto end = std::chrono::steady_clock::now();
        const auto exec = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        if(id.has_value()) {
            SPDLOG_INFO(FMT_STRING("['am'] -> {:d} (took: {})"), *id, exec);
        }
    } else {
        SPDLOG_ERROR("Failed to read vocabulary content: {}", maybeVocab.error());
    }

    return 0;
}