file(GLOB_RECURSE SRC_FILES source/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_executable(${PROJECT_NAME} ${SRC_FILES})

if(MSVC)
    if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
        add_definitions(/MP)				# parallelize each target, unless Ninja is the generator
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
                                    #SDL3_image::SDL3_image
                                    #SDL3_mixer::SDL3_mixer
                                    #SDL3_ttf::SDL3_ttf
                                    imgui
                                    #implot
                                    tomlplusplus::tomlplusplus
                                    podofo::podofo
                                    SDL3::SDL3)   # If using satelite libraries, SDL must be the last item in the list

#target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source/pch.hpp)