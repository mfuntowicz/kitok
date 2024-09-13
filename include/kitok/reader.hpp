//
// Created by Morgan Funtowicz on 9/12/2024.
//

#ifndef KITOK_READER_HPP
#define KITOK_READER_HPP

#include <expected>
#include <filesystem>
#include "kitok/vocabulary.hpp"

namespace kitok {
    std::expected<kitok_vocabulary_t, std::string> kitok_vocabulary_from_tokenizers(const std::filesystem::path& root);
}


#endif //KITOK_READER_HPP
