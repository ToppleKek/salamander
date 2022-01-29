#ifndef SALAMANDER_RAWFILESYSTEM_H
#define SALAMANDER_RAWFILESYSTEM_H

#include <string>
#include <vector>
#include <map>
#include "Services.h"

class RawFilesystem : public FilesystemService {
public:
    explicit RawFilesystem(std::string pack_file);

    std::vector<char> get_file(const std::string &filename) override;

private:
    std::string m_asset_dir;
    std::map<std::string, std::vector<char>> m_cache;
};

#endif //SALAMANDER_RAWFILESYSTEM_H
