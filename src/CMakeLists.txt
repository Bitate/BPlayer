include_directories(${CMAKE_SOURCE_DIR}/include)

set(header_files
	../include/sentence.hpp
	../include/audio.hpp
	../include/video.hpp	
	../include/word.hpp
)
set(source_files
	sentence.cpp
	audio.cpp
	video.cpp
	word.cpp
)

add_library(BPlayer
	${header_files}
	${source_files}
)
