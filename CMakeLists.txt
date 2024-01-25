cmake_minimum_required(VERSION 3.16)

project(PeriodCalendar)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORRC ON)

if (NOT WIN32)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
endif()

if (WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()


find_package(Qt5 REQUIRED COMPONENTS Widgets)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

add_subdirectory(src/core)

set(SRC
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE
calendar
Qt5::Widgets
fmt::fmt
)
