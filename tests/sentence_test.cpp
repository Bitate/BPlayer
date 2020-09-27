#include "sentence.hpp"
#include "word.hpp"

#include <gtest/gtest.h>
#include <initializer_list>
#include <iostream>

TEST(sentence_tests, construct_sentence_test)
{
    using word_ptr = std::shared_ptr< BPlayer::word >;
    using word = BPlayer::word;
    word_ptr w1 = std::make_shared< word >( "I" );
    word_ptr w2 = std::make_shared< word >( "am" );
    word_ptr w3 = std::make_shared< word >( "Bitate" );

    BPlayer::sentence st( { w1, w2, w3 } );
    EXPECT_EQ( st.get_whole_sentence_string(), "I am Bitate ");
}