cmake_minimum_required(VERSION 3.10)
project(da_t1)

set(CMAKE_CXX_STANDARD 11)

set(CREATE_EXE TRUE)


if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_subdirectory(lib/googletest-master)
    include_directories(lib/googletest-master/googletest/include)
    include_directories(lib/googletest-master/googlemock/include)

    add_executable(da_t1 mainTest.cpp Tests/tests.cpp

            src/read_files.cpp include/read_files.h

            src/cen3.cpp include/cen3.h)

    target_link_libraries(da_t1 gtest gtest_main)
    message("Debug mode")

endif ()


if (CMAKE_BUILD_TYPE MATCHES Release)

    add_executable(da_t1 main.cpp

            src/read_files.cpp include/read_files.h

            src/cen3.cpp include/cen3.h)

    message("Release mode")

endif ()
