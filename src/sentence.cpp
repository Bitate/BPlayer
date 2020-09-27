#include "sentence.hpp"

namespace BPlayer
{
    sentence::sentence()
    {
        
    }
    sentence::~sentence()
    {

    }

    sentence::sentence(const sentence& other)
    {

    }
    sentence& sentence::operator=(const sentence& other)
    {
        return *this;
    }

    sentence::sentence(sentence&& other) noexcept
    {
    
    }

    sentence& sentence::operator=(sentence&& other) noexcept
    {
        return *this;
    }
    
    sentence::sentence(std::initializer_list< std::unique_ptr< word > > sentence)
    {
        for(const auto& word : sentence)
        {
            whole_sentence.push_back( word );
        }
    }

    std::string sentence::get_whole_sentence_string()
    {
        
    }

}