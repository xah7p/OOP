cmake_minimum_required(VERSION 3.16)
project(lab3_oop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)
list(FILTER APP_SOURCES EXCLUDE REGEX ".*/AAETALON/.*")
list(FILTER APP_SOURCES EXCLUDE REGEX ".*/out/.*")
list(FILTER APP_SOURCES EXCLUDE REGEX ".*/build/.*")

file(GLOB_RECURSE ALL_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
set(INCLUDE_DIRS "")
foreach(hdr ${ALL_HEADERS})
    get_filename_component(hdr_dir "${hdr}" DIRECTORY)
    if(hdr_dir MATCHES ".*/AAETALON/.*")
        continue()
    endif()
    list(APPEND INCLUDE_DIRS "${hdr_dir}")
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

add_executable(lab3 ${APP_SOURCES})
target_include_directories(lab3 PRIVATE ${INCLUDE_DIRS})
target_link_libraries(lab3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
