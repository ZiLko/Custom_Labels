cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(CustomLabels VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    src/custom_setting.cpp
    src/globals.cpp
    src/label_cell.cpp
    src/label_list_layer.cpp
    src/add_label_layer.cpp
    src/settings_layer.cpp
    src/default_label_settings.cpp
    src/custom_label_settings.cpp
    src/clicks_label_settings.cpp
    src/time_label_settings.cpp
    src/clock_label_settings.cpp
    src/jumps_label_settings.cpp
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME} EXTERNALS geode.node-ids:1.8.1)
