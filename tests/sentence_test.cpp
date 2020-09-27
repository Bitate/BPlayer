#include "sentence.hpp"
#include "word.hpp"

#include <gtest/gtest.h>
#include <initializer_list>
#include <iostream>

TEST(sentence_tests, construct_sentence_test)
{
    using word_ptr = std::unique_ptr< word >;
    word_ptr w1 = std::make_unique< BPlayer::word >("I");
}