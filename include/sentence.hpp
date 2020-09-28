#pragma once    

#include "word.hpp"

#include <string>
#include <vector>
#include <memory>
#include <initializer_list>

namespace BPlayer
{
    class sentence
    {
    public:
        
    public:
        sentence();
        ~sentence();

        sentence(const sentence&);
        sentence& operator=(const sentence&);

        sentence(sentence&&) noexcept;
        sentence& operator=(sentence&&) noexcept;

    public:
        /**
         * @brief  Construct a sentence based on given list of words.
         * @param  sentence  Given sentence.
         */
        sentence(std::initializer_list< std::shared_ptr< word > > words);
    public:
        /**
         * @brief  Get whole/complete sentence in the form of std::string.
         * @return  Whole sentence string.
         */
        std::string get_whole_sentence_string();

    private:
        /**
         * Whole sentence comprised of words.
         */
        std::vector< std::shared_ptr< word > > whole_sentence;

    };
}
