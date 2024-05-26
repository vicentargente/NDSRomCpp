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
    #File
    src/file/NDSFileByteArray.cpp
    include/file/NDSFileByteArray.hpp
    include/file/NDSFile.hpp
    #Util
    src/util/BinaryReader.cpp
    include/util/BinaryReader.hpp
    src/util/BinaryWriter.cpp
    include/util/BinaryWriter.hpp
    include/util/CRC.hpp
    include/util/FileCopier.hpp
    include/util/Number.hpp
    #Model
    include/model/files/Nsbmd.hpp
    src/model/files/Nsbmd.cpp
    include/model/subfiles/mdl/model/Model.hpp
    src/model/subfiles/mdl/model/Model.cpp
    include/model/subfiles/mdl/Mdl.hpp
    src/model/subfiles/mdl/Mdl.cpp
    include/model/subfiles/mdl/model/mesh/MeshList.hpp
    src/model/subfiles/mdl/model/mesh/MeshList.cpp
    include/model/subfiles/mdl/model/mesh/Mesh.hpp
    src/model/subfiles/mdl/model/mesh/Mesh.cpp
    include/model/subfiles/mdl/model/mesh/CommandBlob.hpp
    src/model/subfiles/mdl/model/mesh/CommandBlob.cpp
    include/model/subfiles/tex/Tex.hpp
    src/model/subfiles/tex/Tex.cpp
    include/model/common/Container.hpp
    src/model/common/Container.cpp
    include/model/common/NameList.hpp
    include/model/common/Name.hpp
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

    add_executable(NameListTest tests/model/NameListTest.cpp)
    target_link_libraries(NameListTest ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} NdsCpp)

    add_executable(NsbmdTest tests/model/NsbmdTest.cpp)
    target_link_libraries(NsbmdTest ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} NdsCpp)

    add_executable(NumberTest tests/util/NumberTest.cpp)
    target_link_libraries(NumberTest ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} NdsCpp)

    add_executable(MeshListTest tests/model/MeshListTest.cpp)
    target_link_libraries(MeshListTest ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} NdsCpp)

    add_executable(MeshTest tests/model/MeshTest.cpp)
    target_link_libraries(MeshTest ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} NdsCpp)

    add_test(NAME Header COMMAND HeaderTest)
    add_test(NAME FileNameTable COMMAND FileNameTableTest)
    add_test(NAME FileAllocationTable COMMAND FileAllocationTableTest)
    add_test(NAME NDSFileByteArray COMMAND NDSFileByteArrayTest)
    add_test(NAME NameList COMMAND NameListTest)
    add_test(NAME Nsbmd COMMAND NsbmdTest)
    add_test(NAME Number COMMAND NumberTest)
    add_test(NAME MeshList COMMAND MeshListTest)
    add_test(NAME Mesh COMMAND MeshTest)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
