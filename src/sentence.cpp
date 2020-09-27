#include "sentence.hpp"

namespace BPlayer
{
    sentence::sentence()
    {
        
    }
    sentence::~sentence()
    {

    }

    sentence::sentence(sentence&& other) noexcept
    {
    
    }

    sentence& sentence::operator=(sentence&& other) noexcept
    {
        return *this;
    }
    
    sentence::sentence(std::initializer_list< std::shared_ptr< word > > sentence)
    {
        for(const auto& word : sentence)
        {
            whole_sentence.push_back( word );
        }
    }

    std::string sentence::get_whole_sentence_string()
    {
        std::string s;
        for(const auto& word_ptr : whole_sentence)
        {
            if( word_ptr && word_ptr->get_word_string().size() > 0)
            {
                s += word_ptr->get_word_string();
                s += " ";
            }
        }
        return s;
    }

}