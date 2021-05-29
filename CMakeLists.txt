# SDL2pp tutorial
#
# Written in 2015 by Dmitry Marakasiv <amdmi3@amdmi3.ru>
#
# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication along with
# this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

PROJECT(SDL2pp-tutorial)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(CMAKE_CXX_STANDARD 20)
# set up SDL2pp library
SET(SDL2PP_WITH_IMAGE YES)
SET(SDL2PP WITH_GFX YES)
SET(SDL2PP_WITH_TTF YES)
SET(SDL2PP_WITH_MIXER YES)
SET(SDL2PP_STATIC YES)
SET(SDL2PP_WITH_EXPERIMENTAL_OPTIONAL YES)
ADD_SUBDIRECTORY(vendor/SDL2pp)
# Download automatically, you can also just copy the conan.cmake file



SET(CMAKE_CXX_STANDARD 20)
ADD_DEFINITIONS(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
INCLUDE_DIRECTORIES(${SDL2PP_INCLUDE_DIRS})

set(FLATBUFFERS_SRC_DIR vendor/flatbuffers)
add_subdirectory(${FLATBUFFERS_SRC_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/flatbuffers-build
        EXCLUDE_FROM_ALL)
include(${FLATBUFFERS_SRC_DIR}/CMake/BuildFlatBuffers.cmake)

set(GFLAGS_SRC_DIR vendor/gflags)
set(gflags_DIR ${GFLAGS_SRC_DIR})
add_subdirectory(${GFLAGS_SRC_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/gflags-build
        EXCLUDE_FROM_ALL
        )
set(gflags_NAMESPACE "gflags" CACHE INTERNAL "Namespace for gflags")

set(GLOG_SRC_DIR vendor/glog)
add_subdirectory(${GLOG_SRC_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/glog-build
        EXCLUDE_FROM_ALL)

include_directories(vendor/asio/asio/include)
include_directories(vendor/readerwriterqueue)
# # define targets
# ADD_EXECUTABLE(lesson00 lesson00.cc)
# TARGET_LINK_LIBRARIES(lesson00 ${SDL2PP_LIBRARIES})

# ADD_EXECUTABLE(lesson01 lesson01.cc)
# TARGET_LINK_LIBRARIES(lesson01 ${SDL2PP_LIBRARIES})

# ADD_EXECUTABLE(lesson02 lesson02.cc)
# TARGET_LINK_LIBRARIES(lesson02 ${SDL2PP_LIBRARIES})

# ADD_EXECUTABLE(lesson03 lesson03.cc)
# TARGET_LINK_LIBRARIES(lesson03 ${SDL2PP_LIBRARIES})

# ADD_EXECUTABLE(lesson04 lesson04.cc)
# TARGET_LINK_LIBRARIES(lesson04 ${SDL2PP_LIBRARIES})

# ADD_EXECUTABLE(lesson05 lesson05.cc)
# TARGET_LINK_LIBRARIES(lesson05 ${SDL2PP_LIBRARIES})

# ADD_EXECUTABLE(lesson06 lesson06.cc)
# TARGET_LINK_LIBRARIES(lesson06 ${SDL2PP_LIBRARIES})

# ADD_EXECUTABLE(lesson07 lesson07.cc)
# TARGET_LINK_LIBRARIES(lesson07 ${SDL2PP_LIBRARIES})
#build_flatbuffers("./State.fbs" "${CMAKE_CURRENT_BINARY_PATH}" "State")
ADD_EXECUTABLE(server server/main.cpp server/GameServer.cpp State_generated.h )
target_link_libraries(server flatbuffers glog::glog)
ADD_EXECUTABLE(main main.cpp Game.cpp Ball.cpp AutoPlayer.cpp Player.cpp HumanPlayer.cpp HumanPlayer.hpp Constants.cpp)
target_link_libraries(main ${SDL2PP_LIBRARIES} glog::glog gflags flatbuffers pthread)
target_link_libraries(server pthread)

# ADD_EXECUTABLE(example example.cc)
# target_link_libraries(example ${SDL2PP_LIBRARIES})

# ADD_EXECUTABLE(loggingExample third_party_library_examples/loggingExample.cpp)