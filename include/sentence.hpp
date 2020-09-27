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
        sentence(std::initializer_list< std::shared_ptr< word > > sentence);
    public:
        std::string get_whole_sentence_string();

    private:
        /**
         * Whole sentence comprised of words.
         */
        std::vector< std::shared_ptr< word > > whole_sentence;

    };
}
