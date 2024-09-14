//
// Created by Morgan Funtowicz on 9/12/2024.
//

#ifndef KITOK_VOCABULARY_HPP
#define KITOK_VOCABULARY_HPP

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <set>
#include <algorithm>
#include <bitset>
#include <expected>


#define FLAGS_SPECIAL_TOKEN 0
#define FLAGS_SINGLE_WORD 1
#define FLAGS_LSTRIP 2
#define FLAGS_RSTRIP 3
#define FLAGS_NORMALIZED 4


namespace kitok {

    using kitok_string_t = std::string;
    using kitok_token_id_t = uint32_t;

    class kitok_token_flags_t {
    private:
        std::bitset<5> flags;

    public:
        [[nodiscard]] bool IsSpecial() const {
            return flags[FLAGS_SPECIAL_TOKEN] == 1;
        }

        [[nodiscard]] bool Normalized() const {
            return flags[FLAGS_NORMALIZED];
        }

        [[nodiscard]] bool SingleWord() const {
            return flags[FLAGS_SINGLE_WORD];
        }

        [[nodiscard]] bool StripLeft() const {
            return flags[FLAGS_LSTRIP];
        }

        [[nodiscard]] bool StripRight() const {
            return flags[FLAGS_RSTRIP];
        }
    };

    class kitok_vocabulary_t {
    private:
        std::vector<std::pair<kitok_string_t, kitok_token_id_t>> tokens;
        std::vector<kitok_token_flags_t> flags;

    public:
        kitok_vocabulary_t() = default;
        explicit kitok_vocabulary_t(std::vector<std::pair<kitok_string_t, kitok_token_id_t>>&& tokens, std::vector<kitok_token_flags_t> &&flags):
            tokens(tokens), flags(flags) {}

        /**
         * Number of tokens present in this vocabulary
         * @return
         */
        [[nodiscard]] size_t size() const { return tokens.size(); }
        std::optional<kitok_token_id_t> operator[](std::string_view token) const;
    };
}
#endif //KITOK_VOCABULARY_HPP
