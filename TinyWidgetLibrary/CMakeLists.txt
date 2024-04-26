cmake_minimum_required(VERSION 3.5)
project(TinyWidgetLibrary VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core StateMachine)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core StateMachine)

qt_standard_project_setup()
qt_add_resources(RESOURCE_FILES resource.qrc)

file(GLOB_RECURSE SRC_FILES "./src/*.cpp")
file(GLOB_RECURSE INCLUDE_FILES "./MyWidget/*.h")

set(PROJECT_SOURCES
        ${SRC_FILES}
        ${INCLUDE_FILES}
)

qt_add_library(TinyWidgetLibrary STATIC
        ${PROJECT_SOURCES}
        ${RESOURCE_FILES}
        #resource.qrc
)

target_include_directories(TinyWidgetLibrary PUBLIC
        "${PROJECT_SOURCE_DIR}/MyWidget"
        "${PROJECT_SOURCE_DIR}/example"
)

target_link_libraries(TinyWidgetLibrary PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::StateMachine
)

qt_add_executable(test MANUAL_FINALIZATION main.cpp resource.qrc 
        ${RESOURCE_FILES})

target_link_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/MyWidget)

target_link_libraries(test PUBLIC TinyWidgetLibrary)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.test)
endif()

set_target_properties(test PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(test)
endif()

