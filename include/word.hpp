#pragma once

#include <string>

namespace BPlayer
{   
    class word
    {
        public:
        /**
         * @brief  Construct a single word.
         * @param  word  Single word.
         */
        word( std::string word );

        /**
         * @brief  Construct a single word with a flag.
         * @param  word  Single word.
         * @param  flag  Whether the word is key word.
         */
        word( std::string word, bool flag );

        word& operator+=( const word& rhs);
        
    public:
        /**
         * @brief  Whether the word is key word.
         * @return  True if it is.
         */
        bool is_key_word();

        /**
         * @brief  Change key-word flag.
         * @param  new_flag  New flag.
         */
        void set_flag( bool new_flag );

        /**
         * @brief  Get word string.
         * @return  Word in the form of std::string.
         */
        std::string get_word_string();

    private:
        /**
         * Single word.
         */
        std::string single_word;

        /**
         * Flag to denote whether the word is a key word
         */
        bool is_key_word_flag = false;
    };   
}