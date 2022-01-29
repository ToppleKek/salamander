#include "ServiceLocator.h"

FilesystemService *ServiceLocator::m_filesystem_service = nullptr;
TextureCacheService *ServiceLocator::m_texture_cache_service = nullptr;
RngService *ServiceLocator::m_rng_service = nullptr;

void ServiceLocator::provide(FilesystemService *filesystem_service) noexcept {
    m_filesystem_service = filesystem_service;
}

void ServiceLocator::provide(TextureCacheService *texture_cache_service) noexcept {
    m_texture_cache_service = texture_cache_service;
}

void ServiceLocator::provide(RngService *rng_service) noexcept {
    m_rng_service = rng_service;
}

FilesystemService &ServiceLocator::filesystem() noexcept {
    return *m_filesystem_service;
}

TextureCacheService &ServiceLocator::texture_cache() noexcept {
    return *m_texture_cache_service;
}

RngService &ServiceLocator::rng() noexcept {
    return *m_rng_service;
}
