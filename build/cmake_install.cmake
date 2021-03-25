# Install script for directory: /home/lk/index_rocksdb/learned-leveldb

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE STATIC_LIBRARY FILES "/home/lk/index_rocksdb/learned-leveldb/build/libleveldb.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/leveldb" TYPE FILE FILES
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/c.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/cache.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/comparator.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/db.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/dumpfile.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/env.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/export.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/filter_policy.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/iterator.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/options.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/slice.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/status.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/learned_index.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/table_builder.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/table.h"
    "/home/lk/index_rocksdb/learned-leveldb/include/leveldb/write_batch.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/leveldb/leveldbTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/leveldb/leveldbTargets.cmake"
         "/home/lk/index_rocksdb/learned-leveldb/build/CMakeFiles/Export/lib64/cmake/leveldb/leveldbTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/leveldb/leveldbTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/leveldb/leveldbTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/leveldb" TYPE FILE FILES "/home/lk/index_rocksdb/learned-leveldb/build/CMakeFiles/Export/lib64/cmake/leveldb/leveldbTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/leveldb" TYPE FILE FILES "/home/lk/index_rocksdb/learned-leveldb/build/CMakeFiles/Export/lib64/cmake/leveldb/leveldbTargets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/leveldb" TYPE FILE FILES
    "/home/lk/index_rocksdb/learned-leveldb/cmake/leveldbConfig.cmake"
    "/home/lk/index_rocksdb/learned-leveldb/build/leveldbConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/lk/index_rocksdb/learned-leveldb/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
