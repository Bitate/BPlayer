include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(sentence_test 
    sentence_test.cpp
)
target_link_libraries(sentence_test
    BPlayer
    gtest_main
)

add_executable(word_test
    word_test.cpp
)
target_link_libraries(word_test
    BPlayer
    gtest_main
)