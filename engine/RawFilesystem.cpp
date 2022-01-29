#include "RawFilesystem.h"
#include <filesystem>
#include <fstream>
#include <utility>
#include <cassert>

RawFilesystem::RawFilesystem(std::string pack_file) : m_asset_dir(std::move(pack_file)) {}

std::vector<char> RawFilesystem::get_file(const std::string &filename) {
    /* TODO: Write pack format- for now the pack file is the assets directory
    std::ifstream pack;
    pack.open(m_asset_dir);
     */

    // Dev mode assets
    const std::string pathname = m_asset_dir + filename;
    std::filesystem::path path(pathname);
    assert(std::filesystem::exists(path));

    std::ifstream file;
    file.open(pathname, std::ios::binary);

    return std::vector<char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}
