cmake_minimum_required (VERSION 3.0)

project (test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# Source files
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE source_list "${SRC}/*.cpp" "${SRC}/*.h")
add_executable(test ${source_list})

# Compile features
target_compile_features(test PRIVATE cxx_std_17)

# SDL 2
if(WIN32)
    set(SLD2_PATH ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2-2.0.9)
    set(SDL2_INCLUDE_DIRS "include" ${SLD2_PATH}/include)
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_LIBRARIES "${SLD2_PATH}/lib/x64/SDL2.lib;${SLD2_PATH}/lib/x64/SDL2main.lib")
        add_custom_command(TARGET test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SLD2_PATH}/lib/x64/SDL2.DLL"
        $<TARGET_FILE_DIR:test>)
    else ()
        set(SDL2_LIBRARIES "${SLD2_PATH}/lib/x86/SDL2.lib;${SLD2_PATH}/lib/x86/SDL2main.lib")
        add_custom_command(TARGET test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SLD2_PATH}/lib/x86/SDL2.DLL"
        $<TARGET_FILE_DIR:test>)
    endif ()
    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
else()
    find_package(SDL2 REQUIRED)
endif()

# Libraries
include_directories(${SDL2_INCLUDE_DIRS})

message(${SDL2_INCLUDE_DIRS} pouezt ${SDL2_LIBRARIES} ${SDL2_LIBRARY})
target_link_libraries(test  ${SDL2_LIBRARIES})
