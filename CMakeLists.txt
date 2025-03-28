cmake_minimum_required(VERSION 3.5)

project(module7_diplom_QC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(module7_diplom_QC main.cpp
    safe_queue.h safe_queue.cpp
    thread_pool.h thread_pool.cpp)

include(GNUInstallDirs)
install(TARGETS module7_diplom_QC
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
