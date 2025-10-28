# SDL_mixer
#set(SDLMIXER_MIDI_NATIVE OFF)     # disable formats we don't use to make the build faster and smaller. Also some of these don't work on all platforms so you'll need to do some experimentation.
#set(SDLMIXER_GME OFF)
#set(SDLMIXER_WAVPACK OFF)
#set(SDLMIXER_MOD OFF)
#set(SDLMIXER_OPUS OFF)
#set(SDLMIXER_VENDORED ON)   # tell SDL_mixer to build its own dependencies

# SDL_ttf
#set(SDLTTF_VENDORED ON) # tell SDL_ttf to build its own dependencies

# SDL STATIC BUILD
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
    set(SDL_SHARED OFF)
    set(SDL_STATIC ON)

# SDL3 ---------------------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.24
)
FetchContent_MakeAvailable(SDL3)

# SDL_image 3.0 ---------------------------------------------------------------------------------------
FetchContent_Declare(SDL3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-3.2.4
)
#set(SDLIMAGE_VENDORED ON)
#set(SDLIMAGE_TIFF OFF)
#set(SDLIMAGE_AVIF OFF)
#set(SDLIMAGE_BMP OFF)
#set(SDLIMAGE_JPEG OFF)
#set(SDLIMAGE_WEBP OFF)
FetchContent_MakeAvailable(SDL3_image)

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

#implot -------------------------------------------------------------------------------------
#target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/implot")
#add_library(implot STATIC)
#file(GLOB_RECURSE SRC_FILES implot/*.cpp CMAKE_CONFIGURE_DEPENDS)
#target_sources(implot PRIVATE ${SRC_FILES})
#target_link_libraries(implot PRIVATE imgui)

# toml++ ------------------------------------------------------------------------------------
FetchContent_Declare(tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)