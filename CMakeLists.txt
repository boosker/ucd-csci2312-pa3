cmake_minimum_required(VERSION 3.3)
project(ucd_csci2312_pa3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Cluster.h
    ClusteringTests.cpp
    ClusteringTests.h
    ErrorContext.cpp
    ErrorContext.h
    Exceptions.h
    KMeans.h
    main.cpp
    Point.h
    points1.csv
    points2499.csv
    points25000.csv
    points4.csv
    points4_ex.csv
    points4_large.csv Cluster.cpp Point.cpp KMeans.cpp Exceptions.cpp)

add_executable(ucd_csci2312_pa3 ${SOURCE_FILES})