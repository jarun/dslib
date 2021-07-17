set(CMAKE_POSITION_INDEPENDENT_CODE ON)

cmake_minimum_required(VERSION 3.12)

project(dslib)

file(GLOB files CONFIGURE_DEPENDS include/*.h src/*.c)
add_library(ds SHARED ${files})

find_package(Threads REQUIRED)
target_link_libraries(ds PUBLIC Threads::Threads)

target_include_directories(ds
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/ds>
    )

if (UNIX)
    target_link_libraries(ds PRIVATE -Wl,-undefined,dynamic_lookup)
endif()

file(GLOB files CONFIGURE_DEPENDS test/*.c )
foreach(file IN LISTS files)
    get_filename_component(test_name ${file} NAME_WE)

    add_executable(${test_name} ${file})
    target_link_libraries(${test_name} PRIVATE ds)

    add_test(${test_name} ${test_name})
endforeach()

include(CTest)
