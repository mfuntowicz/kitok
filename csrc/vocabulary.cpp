//
// Created by Morgan Funtowicz on 9/12/2024.
//

#include <filesystem>
#include <fstream>
#include "kitok/vocabulary.hpp"


namespace kitok {
    std::optional<kitok_token_id_t> kitok_vocabulary_t::operator[] (std::string_view token) const {
        const auto [accessor, _] = std::equal_range(tokens.begin(), tokens.end(), std::pair{token, 0}, [](auto& lhs, auto& rhs) {
            return lhs.first < rhs.first;
        });

        if(accessor == std::cend(tokens))
            return std::nullopt;

        const auto id = accessor - std::cbegin(tokens);
        return std::optional<kitok_token_id_t>{id};
    }
}