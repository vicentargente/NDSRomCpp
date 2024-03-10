# CMakeList.txt: proyecto de CMake para NDSRomEditor, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Habilite Recarga activa para los compiladores de MSVC si se admiten.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("NDSRomEditor")

# Agregue un origen al ejecutable de este proyecto.
add_executable (NDSRomEditor "src/NDSRomEditor.cpp" "src/NDSRomEditor.h" "include/util/CRC.h" "include/util/BinaryReader.h" "src/util/BinaryReader.cpp" "include/data_structures/Header.h" "src/data_structures/Header.cpp" "include/NDSRom.h" "src/NDSRom.cpp" "include/data_structures/FileNameTable.h" "src/data_structures/FileNameTable.cpp" "include/data_structures/FileAllocationTable.h" "src/data_structures/FileAllocationTable.cpp" "include/file/NDSFile.h" "include/file/NDSFileByteArray.h" "src/file/NDSFileByteArray.cpp" "include/util/BinaryWriter.h" "src/util/BinaryWriter.cpp" "include/util/FileCopier.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NDSRomEditor PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.
