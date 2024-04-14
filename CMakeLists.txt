cmake_minimum_required(VERSION 3.0.0)
project(nds-cpp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)


option(BUILD_TESTS "Build the tests" OFF)

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
endif()

add_library(
    nds-cpp
    src/NDSRom.cpp
    include/NDSRom.hpp
    src/data_structures/Header.cpp
    include/data_structures/Header.hpp
    src/data_structures/FileNameTable.cpp
    include/data_structures/FileNameTable.hpp
    src/data_structures/FileAllocationTable.cpp
    include/data_structures/FileNameTable.hpp
    src/file/NDSFileByteArray.cpp
    include/file/NDSFileByteArray.hpp
    include/file/NDSFile.hpp src/util/BinaryReader.cpp
    include/util/BinaryReader.hpp src/util/BinaryWriter.cpp
    include/util/BinaryWriter.hpp include/util/CRC.hpp
    include/util/FileCopier.hpp
)

if(BUILD_TESTS)
    add_executable(HeaderTest tests/HeaderTest.cpp)
    target_link_libraries(HeaderTest ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} nds-cpp)

    add_test(NAME HeaderTest COMMAND HeaderTest)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
