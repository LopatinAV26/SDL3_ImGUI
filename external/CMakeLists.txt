include(FetchContent)

# SDL STATIC BUILD
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
    set(SDL_SHARED OFF)
    set(SDL_STATIC ON)

# SDL3 ---------------------------------------------------------------------------------------
FetchContent_Declare(SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG preview-3.3.2
)
FetchContent_MakeAvailable(SDL3)

# PoDoFo ------------------------------------------------------------------------------------
set(PODOFO_BUILD_LIB_ONLY TRUE CACHE BOOL "" FORCE)
set(PODOFO_BUILD_STATIC TRUE CACHE BOOL "" FORCE)
FetchContent_Declare(podofo
    GIT_REPOSITORY https://github.com/podofo/podofo.git
    GIT_TAG 1.0.2
)
FetchContent_MakeAvailable(podofo)
#Без этой команды #include <podofo/podofo.h> не включается
target_include_directories(${PROJECT_NAME} PRIVATE ${PODOFO_INCLUDE_DIRS})

# imgui --------------------------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/imgui")
add_library(imgui STATIC)
file(GLOB_RECURSE SRC_FILES imgui/*.cpp CMAKE_CONFIGURE_DEPENDS)
target_sources(imgui PRIVATE ${SRC_FILES})
target_link_libraries(imgui PRIVATE SDL3::SDL3)

# toml++ ------------------------------------------------------------------------------------
FetchContent_Declare(tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)