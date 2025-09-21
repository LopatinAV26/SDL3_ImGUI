
file(GLOB_RECURSE SRC_FILES source/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_executable(${PROJECT_NAME} ${SRC_FILES})

if(MSVC)
    if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
        add_definitions(/MP)				# parallelize each target, unless Ninja is the generator
    endif()
endif()

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
#find_package(SDL3_mixer CONFIG REQUIRED)
#find_package(SDL3_ttf CONFIG REQUIRED)

# SDL_image
set(SDLIMAGE_VENDORED ON)
set(SDLIMAGE_AVIF OFF)	# disable formats we don't use to make the build faster and smaller.
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_JPEG OFF)
set(SDLIMAGE_WEBP OFF)

# SDL_mixer
set(SDLMIXER_MIDI_NATIVE OFF)     # disable formats we don't use to make the build faster and smaller. Also some of these don't work on all platforms so you'll need to do some experimentation.
set(SDLMIXER_GME OFF)
set(SDLMIXER_WAVPACK OFF)
set(SDLMIXER_MOD OFF)
set(SDLMIXER_OPUS OFF)
set(SDLMIXER_VENDORED ON)   # tell SDL_mixer to build its own dependencies

# SDL_ttf
set(SDLTTF_VENDORED ON) # tell SDL_ttf to build its own dependencies

target_link_libraries(${PROJECT_NAME} PRIVATE
                                    SDL3_image::SDL3_image
                                    #SDL3_mixer::SDL3_mixer
                                    #SDL3_ttf::SDL3_ttf
                                    SDL3::SDL3)   # If using satelite libraries, SDL must be the last item in the list

#target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source/pch.hpp)

target_link_libraries(${PROJECT_NAME} PRIVATE imgui)