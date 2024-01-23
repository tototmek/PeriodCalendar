cmake_minimum_required(VERSION 3.16)

project(PeriodCalendar)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORRC ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

if (WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()


find_package(Qt5 REQUIRED COMPONENTS Widgets)

include_directories(src/core)

set(SRC
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)