//
// Created by Morgan Funtowicz on 9/12/2024.
//

#include <execution>
#include <fstream>
#include "kitok/vocabulary.hpp"


namespace kitok {
    std::optional<kitok_token_id_t> kitok_vocabulary_t::operator[] (std::string_view token) const {
        const auto accessor = std::find(std::execution::unseq, tokens.cbegin(), tokens.cend(), token);

        if(accessor == std::cend(tokens))
            return std::nullopt;

        const auto id = accessor - std::cbegin(tokens);
        return std::optional<kitok_token_id_t>{id};
    }

    std::optional<std::string_view> kitok_vocabulary_t::operator[](kitok_token_id_t id) const {
        if(id < tokens.size())
            return std::optional<std::string_view> { tokens[id] };

        return std::nullopt;
    }
}