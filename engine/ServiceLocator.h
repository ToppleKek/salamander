#ifndef SALAMANDER_SERVICELOCATOR_H
#define SALAMANDER_SERVICELOCATOR_H

#include "Services.h"

class ServiceLocator {
public:
    static void provide(FilesystemService *filesystem_service) noexcept;
    static void provide(TextureCacheService *render_service) noexcept;
    static void provide(RngService *rng_service) noexcept;
    [[nodiscard]] static FilesystemService &filesystem() noexcept;
    [[nodiscard]] static TextureCacheService &texture_cache() noexcept;
    [[nodiscard]] static RngService &rng() noexcept;

private:
    static FilesystemService *m_filesystem_service;
    static TextureCacheService *m_texture_cache_service;
    static RngService *m_rng_service;
};

#endif //SALAMANDER_SERVICELOCATOR_H
