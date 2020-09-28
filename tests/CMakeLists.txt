include_directories(${CMAKE_SOURCE_DIR}/include)

# Run all test suits at the same time
set(all_test_source_files
    sentence_test.cpp
    word_test.cpp
    audio_test.cpp
)
add_executable(all_tests
    ${all_test_source_files}
)
target_link_libraries(all_tests
    BPlayer
    gtest_main
)

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

add_executable(audio_test
    audio_test.cpp
)
target_link_libraries(audio_test
    BPlayer
    gtest_main
)