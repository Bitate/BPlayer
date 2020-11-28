include_directories(${CMAKE_SOURCE_DIR}/include)

set(header_files
	../include/sentence.hpp
	../include/audio.hpp
	../include/video.hpp	
	../include/word.hpp
    ../include/srtHandler.hpp
)
set(source_files
	sentence.cpp
	audio.cpp
	video.cpp
	word.cpp
	srtHandler.cpp
)

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

add_library(BPlayer
	${header_files}
	${source_files}
)
target_link_libraries(BPlayer
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
    Qt${QT_VERSION_MAJOR}::MultimediaQuick
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Widgets
)


# Find OpenCV binaries
find_package(OpenCV REQUIRED)
# Include directory that contains OpenCV header files
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_library(BVideo
    ../include/video.hpp
    video.cpp
)
target_link_libraries(BVideo 
    ${OpenCV_LIBS}
)
