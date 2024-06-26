cmake_minimum_required(VERSION 3.0.0)
project(NdsCpp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)


option(BUILD_TESTS "Build the tests" OFF)

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
endif()

add_library(
    NdsCpp
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
    target_link_libraries(HeaderTest ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} NdsCpp)

    add_executable(FileNameTableTest tests/FileNameTableTest.cpp)
    target_link_libraries(FileNameTableTest ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} NdsCpp)

    add_executable(FileAllocationTableTest tests/FileAllocationTableTest.cpp)
    target_link_libraries(FileAllocationTableTest ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} NdsCpp)

    add_executable(NDSFileByteArrayTest tests/NDSFileByteArrayTest.cpp)
    target_link_libraries(NDSFileByteArrayTest ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} NdsCpp)

    add_test(NAME Header COMMAND HeaderTest)
    add_test(NAME FileNameTable COMMAND FileNameTableTest)
    add_test(NAME FileAllocationTable COMMAND FileAllocationTableTest)
    add_test(NAME NDSFileByteArray COMMAND NDSFileByteArrayTest)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
