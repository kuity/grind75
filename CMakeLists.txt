cmake_minimum_required(VERSION 3.10)
project(LeetCode-Indexer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# this should generate compile_commands.json in the project root which allows clangd to find 
# the external libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE "Indexer")

file(GLOB LIB_SOURCES "lib/*.cpp")

add_executable(${EXECUTABLE} ${LIB_SOURCES} "src/indexer.cpp")

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(${EXECUTABLE} PRIVATE cpr::cpr)

set(BOOST_REQUIRED_COMPONENTS
    filesystem
)
# Here you can either append or set a root to look into
# In general, **don't do that**! Your boost build and installation
# should come with the correct CMake configure scripts to automate this!
# If you set it here, the people trying to build your code on a different
# machine **WILL** hate you.
set(BOOST_MIN_VERSION 1.82.0) # or whatever you need!
set(BOOST_ROOT "/Users/lingzhang.jiang/projects/tools/cpp/boost_1_82_0")
find_package(
    Boost ${BOOST_MIN_VERSION} REQUIRED
    COMPONENTS ${BOOST_REQUIRED_COMPONENTS}
)
target_link_libraries(${EXECUTABLE} PUBLIC  
    Boost::filesystem
)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(${EXECUTABLE} PRIVATE nlohmann_json::nlohmann_json)

include_directories("/usr/local/include")
link_directories("/usr/local/lib")
target_link_libraries(${EXECUTABLE} PRIVATE "/usr/local/lib/libgumbo.dylib")
