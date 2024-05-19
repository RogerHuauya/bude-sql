cmake_minimum_required(VERSION 3.23)
project(bude_sql)


# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

add_executable(${PROJECT_NAME} src/proxy/test_proxy.cpp
        src/proxy/proxy.h
        src/bplus/bplus.cpp
        src/bplus/bplus.h
        src/model/apple.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/
        ${PROJECT_SOURCE_DIR}/src/proxy
        ${PROJECT_SOURCE_DIR}/src/model
)


add_executable(test_bplus src/bplus/test_bplus.cpp src/bplus/bplus.cpp src/bplus/bplus.h)

target_include_directories(
        test_bplus PRIVATE
        ${PROJECT_SOURCE_DIR}/src/
        ${PROJECT_SOURCE_DIR}/src/bplus/
        ${PROJECT_SOURCE_DIR}/src/model
)

add_executable(test_exhash src/proxy/test_proxy.cpp src/proxy/proxy.cpp src/model/apple.cpp
        src/parser/parser.cpp src/parser/scanner.cpp src/parser/statement.cpp
        src/parser/query.cpp src/bplus/bplus.cpp src/exhash/ExHash.hpp src/exhash/utils.hpp src/exhash/test_exhash.cpp)

target_include_directories(
        test_exhash PRIVATE
        ${PROJECT_SOURCE_DIR}/src/model
        ${PROJECT_SOURCE_DIR}/src/proxy
        ${PROJECT_SOURCE_DIR}/src/parser
        ${PROJECT_SOURCE_DIR}/src/bplus
        ${PROJECT_SOURCE_DIR}/src/exhash
        ${PROJECT_SOURCE_DIR}/src/avl
)


add_executable(test_parser src/parser/test_parser.cpp src/parser/parser.cpp src/parser/parser.h
        src/parser/scanner.h src/parser/scanner.cpp src/parser/statement.h src/parser/statement.cpp src/model/apple.cpp src/bplus/bplus.cpp)

target_include_directories(
        test_parser PRIVATE
        ${PROJECT_SOURCE_DIR}/src/
        ${PROJECT_SOURCE_DIR}/src/parser/
        ${PROJECT_SOURCE_DIR}/src/model
        ${PROJECT_SOURCE_DIR}/src/bplus
)


add_executable(test_proxy src/proxy/test_proxy.cpp src/proxy/proxy.cpp src/model/apple.cpp
        src/parser/parser.cpp src/parser/scanner.cpp src/parser/statement.cpp
        src/parser/query.cpp src/bplus/bplus.cpp src/exhash/ExHash.hpp src/exhash/utils.hpp src/exhash/test_exhash.cpp)

target_include_directories(
        test_proxy PRIVATE
        ${PROJECT_SOURCE_DIR}/src/model
        ${PROJECT_SOURCE_DIR}/src/proxy
        ${PROJECT_SOURCE_DIR}/src/parser
        ${PROJECT_SOURCE_DIR}/src/bplus
        ${PROJECT_SOURCE_DIR}/src/exhash
        ${PROJECT_SOURCE_DIR}/src/avl
)

add_executable(test_raylib
        UI/test_raylib.cpp

        src/bplus/bplus.h
        src/bplus/bplusnode.h
        src/bplus/bplus.cpp

        src/model/apple.h
        src/model/apple.cpp

        src/parser/parser.cpp
        src/parser/parser.h
        src/parser/scanner.cpp
        src/parser/scanner.h
        src/parser/statement.h
        src/parser/statement.cpp
        src/parser/query.cpp
        src/parser/query.h

        src/proxy/proxy.h
        src/proxy/proxy.cpp

        UI/Scenes.hpp
        UI/Scenes/DAvl.hpp
        UI/Scenes/DBTree.hpp
        UI/Scenes/DExtendible.hpp
        UI/Scenes/SceneCredits.hpp
        UI/Scenes/SceneDocumen.hpp
        UI/Scenes/SceneMainMenu.hpp
        UI/Scenes/SceneStructuresDocumen.cpp
        UI/Scenes/SceneStructuresVisualize.cpp
        UI/Scenes/SceneVisualize.hpp
        UI/Scenes/VAVL.cpp
        UI/Scenes/VAvl.hpp
        UI/Scenes/VBtree.cpp
        UI/Scenes/VBTree.hpp
        UI/Scenes/VExtendible.cpp
        UI/Scenes/VExtendible.hpp

        UI/Util/Button.hpp
        UI/Util/GUIManager.hpp
        UI/Util/QueryVisual.hpp
        )

target_include_directories(
        test_raylib PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/bplus
        ${PROJECT_SOURCE_DIR}/src/model
        ${PROJECT_SOURCE_DIR}/src/parser
        ${PROJECT_SOURCE_DIR}/src/proxy
        ${PROJECT_SOURCE_DIR}/UI
        ${PROJECT_SOURCE_DIR}/UI/Scenes
        ${PROJECT_SOURCE_DIR}/UI/Util
        )

#set(raylib_VERBOSE 1)
target_link_libraries(test_raylib raylib)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()