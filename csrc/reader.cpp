//
// Created by Morgan Funtowicz on 9/13/2024.
//

#include <fstream>
#include "nlohmann/json.hpp"
#include "kitok/reader.hpp"

using json = nlohmann::json;

namespace kitok {
    std::expected<kitok_vocabulary_t, std::string> kitok_vocabulary_from_tokenizers(const std::filesystem::path& root) {
            std::ifstream fConfig(root / "tokenizer_config.json");
            std::ifstream fTokenizer(root / "tokenizer.json");

            auto config = json::parse(fConfig);
            auto tokenizer = json::parse(fTokenizer);
            auto val = config["/model/vocab"_json_pointer];

            return {};
    }
}