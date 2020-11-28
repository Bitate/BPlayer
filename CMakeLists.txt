cmake_minimum_required(VERSION 3.8)

project(BPlayer CXX)

enable_testing()

# Force googletest to link dynamically
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


add_subdirectory(googletest)
add_subdirectory(src)
add_subdirectory(tests)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS
    Widgets
    Core
    Gui
    Quick
    Multimedia
    MultimediaWidgets
    MultimediaQuick

    REQUIRED
)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS
    Widgets
    Core
    Gui
    Quick
    Multimedia
    MultimediaWidgets
    MultimediaQuick

    REQUIRED
)

add_executable(main_exec
    main.cpp
    main.qrc
)
target_link_libraries(main_exec
    BPlayer
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
    Qt${QT_VERSION_MAJOR}::MultimediaQuick
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Widgets
)
