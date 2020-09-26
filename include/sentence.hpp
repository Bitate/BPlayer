#pragma once    

#include <string>
#include <vector>

namespace BPlayer
{
    class sentence
    {
    public:
        sentence();
        ~sentence();

        sentence(const sentence&);
        sentence& operator=(const sentence&);

        sentence(sentence&&) noexcept;
        sentence& operator=(sentence&&) noexcept;

    private:
        std::vector< std::string > originial_sentence;

    };
}
