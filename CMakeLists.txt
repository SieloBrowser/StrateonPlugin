cmake_minimum_required(VERSION 3.6)
project(StrateonPlugin)

# user config config file
include("${CMAKE_SOURCE_DIR}/user-config.cmake")

include_directories(${SIELO_DIR}/Core)
include_directories(${CMAKE_SOURCE_DIR}/includes)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

link_directories(${SIELO_LIBS_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(
    GLOB_RECURSE
    SOURCE_FILES
    *.h
    *.hpp
    *.cpp
)

file(
	GLOB_RECURSE
	QRC_FILES
	*.qrc
)

find_package(Qt5Widgets 5.11.2 REQUIRED)
find_package(Qt5WebEngine 5.11.2 REQUIRED)
find_package(Qt5Sql 5.11.2 REQUIRED)
find_package(Qt5WebEngineWidgets 5.11.2 REQUIRED)

set(SIELO_LIBS SieloCore Qt5::Widgets Qt5::WebEngine Qt5::Sql Qt5::WebEngineWidgets)

add_library(StrateonPlugin MODULE ${SOURCE_FILES} ${QRC_FILES})

target_link_libraries(StrateonPlugin PRIVATE ${SIELO_LIBS})

##### Visual Studio Filters #####
foreach(_source IN ITEMS ${SOURCE_FILES})
	get_filename_component(_source_path "${_source}" PATH)
	file(RELATIVE_PATH _source_path_rel "${CMAKE_SOURCE_DIR}" "${_source_path}")
	string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
	source_group("${_group_path}" FILES "${_source}")
endforeach()
################################