cmake_minimum_required(VERSION 3.31)
project(metrics-lib)

set(CMAKE_CXX_STANDARD 20)

add_executable(main
        main.cpp
        AverageMetric.cpp
        CounterMetric.cpp
        MetricsRegistry.cpp
        MetricsWriter.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(main PRIVATE Threads::Threads)