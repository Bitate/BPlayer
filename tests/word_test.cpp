#include "word.hpp"

#include <gtest/gtest.h>

TEST(word_tests, key_word_test)
{
    BPlayer::word w1( "fly" );
    ASSERT_FALSE( w1.is_key_word() );
    w1.set_flag( true );
    ASSERT_TRUE( w1.is_key_word() );

    BPlayer::word w2( "fly", true );
    ASSERT_TRUE( w2.is_key_word() );
    w2.set_flag( false );
    ASSERT_FALSE( w2.is_key_word() );
}