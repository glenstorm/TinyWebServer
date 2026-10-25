cmake_minimum_required(VERSION 3.16)

# Build this project inside WSL with GCC. The sources use Linux epoll.
if(NOT CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    message(FATAL_ERROR
        "Build TinyWebServer in WSL with GCC. From Visual Studio Code, "
        "install the WSL extension and choose \"Reopen Folder in WSL\", "
        "then select the \"WSL GCC Debug\" CMake preset and build the "
        "server target. On a fresh Ubuntu distro:\n"
        "  sudo apt update\n"
        "  sudo apt install build-essential cmake pkg-config libmysqlclient-dev")
endif()

project(TinyWebServer
    VERSION 1.0
    DESCRIPTION "Lightweight Linux C++ web server"
    LANGUAGES CXX
)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR
        "This build is set up for GCC (g++). The current compiler is "
        "${CMAKE_CXX_COMPILER_ID} (${CMAKE_CXX_COMPILER}). "
        "In WSL, install g++ with: sudo apt install build-essential")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The old makefile used -O2 for a non-debug build. CMake's Release flags use -O3.
string(REPLACE "-O3" "-O2" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

find_package(Threads REQUIRED)

find_package(PkgConfig QUIET)
set(MYSQL_TARGET "")
if(PkgConfig_FOUND)
    pkg_check_modules(MYSQL QUIET IMPORTED_TARGET mysqlclient)
    if(NOT MYSQL_FOUND)
        pkg_check_modules(MYSQL QUIET IMPORTED_TARGET libmariadb)
    endif()
    if(MYSQL_FOUND)
        set(MYSQL_TARGET PkgConfig::MYSQL)
    endif()
endif()

if(NOT MYSQL_TARGET)
    find_path(MYSQL_INCLUDE_DIR NAMES mysql/mysql.h)
    find_library(MYSQL_LIBRARY NAMES mysqlclient mysqlclient_r mariadb)
    if(NOT MYSQL_INCLUDE_DIR OR NOT MYSQL_LIBRARY)
        message(FATAL_ERROR
            "GCC is present, but the MySQL client library is not. "
            "In WSL run: sudo apt install libmysqlclient-dev pkg-config")
    endif()
    add_library(mysql_client UNKNOWN IMPORTED)
    set_target_properties(mysql_client PROPERTIES
        IMPORTED_LOCATION "${MYSQL_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${MYSQL_INCLUDE_DIR}"
    )
    set(MYSQL_TARGET mysql_client)
endif()

add_executable(server
    main.cpp
    config.cpp
    webserver.cpp
    http/http_conn.cpp
    timer/lst_timer.cpp
    log/log.cpp
    CGImysql/sql_connection_pool.cpp
)

target_include_directories(server PRIVATE "${CMAKE_SOURCE_DIR}")
target_link_libraries(server PRIVATE Threads::Threads ${MYSQL_TARGET})

# Run the binary from the project root so it can find the root/ pages.
set_target_properties(server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
