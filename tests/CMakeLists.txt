include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(sentence_test 
    sentence_test.cpp
)
target_link_libraries(sentence_test
    gtest_main
    BPlayer
)