//
// Created by Morgan Funtowicz on 9/12/2024.
//

#include <filesystem>
#include <fstream>
#include "kitok/vocabulary.hpp"


namespace kitok {
    std::optional<kitok_token_id_t> kitok_vocabulary_t::operator[] (std::string_view token) const {
        const auto accessor = std::lower_bound(tokens.begin(), tokens.end(), token);
        if(accessor == std::cend(tokens))
            return std::nullopt;

        const auto id = accessor - std::cbegin(tokens);
        return std::optional<kitok_token_id_t>{id};
    }
}