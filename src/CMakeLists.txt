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

add_library(BVideo STATIC
    ../include/video.hpp
    video.cpp
)

# Set OpenCVConfig.cmake Search Directory
set( OpenCV_DIR )
if( NOT CMAKE_CL_64 )
  set( OpenCV_DIR "C:/vcpkg/installed/x86-windows/share/opencv" )
else()
  set( OpenCV_DIR "C:/vcpkg/installed/x64-windows/share/opencv" )
endif()

# Find Package
find_package( OpenCV REQUIRED )

if( OpenCV_FOUND )
  # Additional Include Directories
  include_directories( ${OpenCV_INCLUDE_DIRS} )

  # Additional Library Directories
  link_directories( ${OpenCV_LIB_DIR} )

  # Additional Dependencies
  target_link_libraries( BVideo ${OpenCV_LIBS} )
endif()
