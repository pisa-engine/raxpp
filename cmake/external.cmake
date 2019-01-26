include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(rax
    GIT_REPOSITORY    "https://github.com/antirez/rax.git"
    SOURCE_DIR        "${CMAKE_BINARY_DIR}/rax-src"
    BINARY_DIR        "${CMAKE_BINARY_DIR}/rax-src"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     cc -c -fPIC -std=c99 rax.c -o librax.a
    INSTALL_COMMAND   mkdir -p ${EXTERNAL_INSTALL_LOCATION}
                        && cp librax.a ${EXTERNAL_INSTALL_LOCATION}/librax.a
                        && cp rax.h ${EXTERNAL_INSTALL_LOCATION}/rax.h)

ExternalProject_Add(Catch
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    SOURCE_DIR        "${CMAKE_BINARY_DIR}/Catch2-src"
    BINARY_DIR        "${CMAKE_BINARY_DIR}/Catch2-src"
    CMAKE_ARGS -DBUILD_TESTING=OFF -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION})

list(APPEND CMAKE_MODULE_PATH ${EXTERNAL_INSTALL_LOCATION})
list(APPEND CMAKE_PREFIX_PATH ${EXTERNAL_INSTALL_LOCATION})
