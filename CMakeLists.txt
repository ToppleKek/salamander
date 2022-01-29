cmake_minimum_required(VERSION 3.16)
project(salamander)

set(CMAKE_CXX_STANDARD 20)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf)

add_executable(salamander
        main.cpp
        engine/Engine.cpp
        engine/Engine.h
        engine/Game.h
        engine/GameObject.h
        engine/Logger.h
        TheSalamander.cpp
        TheSalamander.h
        engine/RenderComponent.h
        engine/Sprite.cpp
        engine/Sprite.h
        engine/RawFilesystem.cpp
        engine/RawFilesystem.h
        engine/ServiceLocator.cpp
        engine/ServiceLocator.h
        engine/Services.h
        engine/SpriteRenderComponent.cpp
        engine/SpriteRenderComponent.h
        objects/Player.cpp objects/Player.h
        engine/resource/TextureLoader.cpp
        engine/resource/TextureLoader.h
        engine/resource/MappedTextureCache.h
        engine/Scene.h
        engine/Vector2D.h
        engine/FollowCamera.cpp
        engine/FollowCamera.h
        MainScene.cpp
        MainScene.h
        objects/Ground.h
        TitleScene.cpp
        TitleScene.h
        objects/House.cpp
        objects/House.h
        engine/Mt19937Rng.h
        objects/Flame.cpp
        objects/Flame.h
        objects/StopWall.h
        objects/Spike.cpp
        objects/Spike.h
        ResultsScene.cpp
        ResultsScene.h)
target_compile_options(salamander PRIVATE -Wall -Wextra -Wpedantic)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(engine/thirdparty/fmt)
target_include_directories(salamander PRIVATE engine/thirdparty/fmt/include)

target_link_libraries(salamander PRIVATE ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} fmt::fmt)