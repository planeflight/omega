#include "texture_atlas.h"

#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

static void split(std::string str, std::vector<std::string> &ret_vec, const std::string &del = " ") {
    char *s = &str[0]; // get pointer to string
    // start splitting string
    char *piece = strtok(s, del.c_str());
    while (piece != nullptr) {
        ret_vec.push_back(std::string(piece));
        piece = strtok(nullptr, del.c_str());
    }
}

namespace omega::gfx::texture {

TextureAtlas::TextureAtlas(const std::string &atlas_file_path, GLenum min_filter, GLenum mag_filter) : tex(nullptr) {
    // open file
    FILE *atlas_file = fopen(atlas_file_path.c_str(), "r");
    if (atlas_file == nullptr) {
        util::error("Unable to open texture atlas");
        return;
    }
    // load file data
    char buff[256];
    std::vector<std::string> lines;
    while (fgets(buff, sizeof(buff), atlas_file)) {
        std::string line(buff);
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        lines.push_back(line);
    }
    fclose(atlas_file);
    atlas_file = nullptr;

    // parse lines
    uint32_t x, y, w, h;
    std::string tex_region_key;
    for (size_t i = 0; i < lines.size(); i++) {
        const auto &line = lines[i];
        // split line into words
        std::vector<std::string> words;
        split(line, words, " ");
        // must be line 1 -> contains image
        if (i == 0) {
            // get full path to image file
            std::string path = atlas_file_path.substr(0, atlas_file_path.size() - 5);
            path += "png";
            tex = Texture::create_from_file(path, min_filter, mag_filter);
            continue;
        }
        size_t num_words = words.size();
        // if only 1 word -> must be new tex region
        if (num_words == 1) {
            tex_region_key = words[0];
            continue;
        }
        // must be size / attributes
        if (num_words == 5) {
            x = std::stoi(words[1]);
            y = std::stoi(words[2]);
            w = std::stoi(words[3]);
            h = std::stoi(words[4]);
            // create TextureRegion
            tex_regions[tex_region_key] = create_sptr<TextureRegion>(tex.get(), x, y, w, h);
        }
    }
}

TextureAtlas::~TextureAtlas() {
}

sptr<TextureRegion> TextureAtlas::get(const std::string &texture_name) {
    return tex_regions[texture_name];
}

} // namespace omega::gfx::texture
