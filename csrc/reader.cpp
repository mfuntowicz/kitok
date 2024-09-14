//
// Created by Morgan Funtowicz on 9/13/2024.
//

#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include "kitok/reader.hpp"

using json = nlohmann::json;

namespace kitok {
    std::expected<kitok_vocabulary_t, std::string> kitok_vocabulary_from_tokenizers(const std::filesystem::path& root) {
        std::ifstream fConfig(root / "tokenizer_config.json");
        std::ifstream fTokenizer(root / "tokenizer.json");

        auto config = json::parse(fConfig);
        auto tokenizer = json::parse(fTokenizer);

        const auto& version = tokenizer["/version"_json_pointer].get<std::string_view>();
        if(version == "1.0") {
            SPDLOG_INFO("Reading from tokenizers v{} format", version);

            const auto& model = tokenizer["/model"_json_pointer];
            const auto vocab = model["/vocab"_json_pointer];

            SPDLOG_INFO(FMT_STRING("Detected {:d} tokens in the vocab"), vocab.size());
            auto tokens = std::vector<std::pair<std::string, kitok_token_id_t>>();
            tokens.reserve(vocab.size());

            for(auto& [token, id] : vocab.items())
                tokens.emplace_back(std::string(token), id.get<kitok_token_id_t>());

            std::sort(tokens.begin(), tokens.end());
            return kitok_vocabulary_t{std::move(tokens), std::move(std::vector<kitok_token_flags_t>())};

        } else {
            return std::unexpected(
                fmt::format(FMT_STRING("Tokenizers schema version {} is not supported"), version)
            );
        }


        return {};
    }
}