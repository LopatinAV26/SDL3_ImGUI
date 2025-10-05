# SDL --------------------------------------------------------------------------------------
find_package(SDL3 CONFIG REQUIRED)	#Пока не подключена локально, требуется для imgui
#add_library(sdl3 INTERFACE)
#target_include_directories(sdl3 INTERFACE $ENV{VULKAN_SDK}/Include/SDL3 )
#target_link_directories(sdl3 INTERFACE $ENV{VULKAN_SDK}/Lib )
#target_link_libraries(sdl3 INTERFACE SDL3 SDL3main)
#---------------------------------------------------------------------------------------------

# imgui --------------------------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/imgui")
add_library(imgui STATIC)

file(GLOB_RECURSE SRC_FILES imgui/*.cpp CMAKE_CONFIGURE_DEPENDS)
target_sources(imgui PRIVATE ${SRC_FILES})

target_link_libraries(imgui PRIVATE SDL3::SDL3)

# toml++ ------------------------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/toml++")


#json--------------------------------------
#target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/Third_party/nlohmann")