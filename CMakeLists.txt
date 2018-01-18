cmake_minimum_required (VERSION 2.6)
project(CppWebSockets)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

set(LIBWEBSOCKETS_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/../libwebsockets/build/include" CACHE PATH "OpenCV include dir")
set(LIBWEBSOCKETS_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../libwebsockets/build/lib/Release" CACHE PATH "OpenCV library dir")
set(LIBWEBSOCKETS_BINARY "${CMAKE_CURRENT_SOURCE_DIR}/../libwebsockets/build/bin/Release" CACHE PATH "OpenCV binary dir")

include_directories("${LIBWEBSOCKETS_INCLUDE}")

# link_directories("${LIBWEBSOCKETS_LIBRARY}")

file(GLOB SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(EchoServer ${SRC} "${CMAKE_CURRENT_SOURCE_DIR}/examples/echoServer/echoServer.cpp" )

target_link_libraries(EchoServer "${LIBWEBSOCKETS_LIBRARY}/websockets.lib")

STRING(REGEX REPLACE "/" "\\\\" COPY_SOURCE \"${OPENCV_BINARY}/*.dll\")
STRING(REGEX REPLACE "/" "\\\\" COPY_DEST \"${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>\")

# add_custom_command(TARGET EchoServer POST_BUILD
#     COMMAND COMMAND copy ${COPY_SOURCE} ${COPY_DEST}
#     COMMAND COMMAND copy ${ZMQ_COPY_SOURCE} ${COPY_DEST}
#     COMMENT "Copying libWebSockets DLL for EchoServer example...\n"
# )

add_custom_command(TARGET EchoServer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LIBWEBSOCKETS_BINARY}/websockets.dll"
        $<TARGET_FILE_DIR:EchoServer>)