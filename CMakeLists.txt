project(mmap_asan_rss_usage CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mmap_asan_rss_usage main.cpp)
