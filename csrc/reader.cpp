//
// Created by Morgan Funtowicz on 9/13/2024.
//

#include <execution>
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
            auto tokens = std::vector<std::string>(vocab.size());
            const auto begin = tokens.cbegin();
            const auto items = vocab.items();

            std::for_each(std::execution::par_unseq, items.begin(), items.end(), [&tokens](auto item){
                auto& [token, idx] = item;
                tokens[idx] = token;
            });

            return kitok_vocabulary_t{std::move(tokens), std::move(std::vector<kitok_token_flags_t>())};

        } else {
            return std::unexpected(
                fmt::format(FMT_STRING("Tokenizers schema version {} is not supported"), version)
            );
        }


        return {};
    }
}