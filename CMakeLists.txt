cmake_minimum_required(VERSION 3.0.0)
project(nds-cpp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

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

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
