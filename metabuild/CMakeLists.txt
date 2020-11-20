cmake_minimum_required(VERSION 3.0)
project(ls3icons_meta)
include(ExternalProject)

# If there is a CMAKE_BUILD_TYPE it is important to ensure it is passed down.
if(CMAKE_BUILD_TYPE)
  list(APPEND External_DEFAULT_ARGS
    "-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}")
endif()

ExternalProject_Add(ls3icons64
  SOURCE_DIR ..
  CMAKE_COMMAND x86_64-w64-mingw32.static-cmake
  CMAKE_CACHE_ARGS "${External_DEFAULT_ARGS};-DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/prefix64"
  INSTALL_COMMAND x86_64-w64-mingw32.static-cmake --build . --target install/strip
  BUILD_ALWAYS ON)
install(FILES ${CMAKE_BINARY_DIR}/prefix64/bin/Ls3Icons.dll DESTINATION bin64)
ExternalProject_Add(ls3icons32
  SOURCE_DIR ..
  CMAKE_COMMAND i686-w64-mingw32.static-cmake
  CMAKE_CACHE_ARGS "${External_DEFAULT_ARGS};-DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/prefix32"
  INSTALL_COMMAND i686-w64-mingw32.static-cmake --build . --target install/strip
  BUILD_ALWAYS ON)
install(FILES ${CMAKE_BINARY_DIR}/prefix32/bin/Ls3Icons.dll DESTINATION bin32)

set(CPACK_GENERATOR NSIS)
set(CPACK_PACKAGE_NAME "ls3icons")
set(CPACK_PACKAGE_VENDOR "Zusitools")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Symbole für LS3-Dateien im Windows-Explorer")
set(CPACK_PACKAGE_VERSION "2.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "ls3icons")

set(CPACK_NSIS_MODIFY_PATH OFF)
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)

list(APPEND CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
    ExecWait '\\\"\$SYSDIR\\\\regsvr32.exe\\\" /s \\\"\$INSTDIR\\\\bin64\\\\Ls3Icons.dll\\\"'
    ExecWait '\\\"\$SYSDIR\\\\regsvr32.exe\\\" /s \\\"\$INSTDIR\\\\bin32\\\\Ls3Icons.dll\\\"'
")
list(APPEND CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
    ExecWait '\\\"\$SYSDIR\\\\regsvr32.exe\\\" /s /u \\\"\$INSTDIR\\\\bin64\\\\Ls3Icons.dll\\\"'
    ExecWait '\\\"\$SYSDIR\\\\regsvr32.exe\\\" /s /u \\\"\$INSTDIR\\\\bin32\\\\Ls3Icons.dll\\\"'
")

INCLUDE(CPack)
