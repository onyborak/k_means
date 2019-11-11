
# To build the test, add to the configuration flags:
# -DWITH_TEST=TRUE

cmake_minimum_required(VERSION 3.14.5)
project(Clustering)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE LIB_SOURCES Source/Lib/*.cpp)
add_library(ClusteringLib ${LIB_SOURCES})

target_include_directories(ClusteringLib PUBLIC Include/Lib)
target_link_libraries(ClusteringLib -lpthread)
install(TARGETS ClusteringLib
        ARCHIVE DESTINATION lib)
install(DIRECTORY Include/Lib/ DESTINATION include FILES_MATCHING PATTERN "*.h")

if (WITH_TEST)
    add_executable(TestClustering Source/Test/main.cpp)
    target_link_libraries(TestClustering ClusteringLib)
    install(TARGETS TestClustering
            RUNTIME DESTINATION test)
endif()

