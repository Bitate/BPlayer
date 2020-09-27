#include "word.hpp"

namespace BPlayer
{ 
    word::word( std::string word )
        : single_word(word), is_key_word_flag(false)
    {
    }

    word::word( std::string word, bool flag )
        : single_word(word), is_key_word_flag(flag)
    {
    }

    bool word::is_key_word()
    {
        return is_key_word_flag;
    }

    void word::set_flag( bool new_flag )
    {
        is_key_word_flag = new_flag;
    }

    std::string word::get_word_string()
    {
        return single_word;
    }
}