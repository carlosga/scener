#ifndef UNICODE_HPP
#define UNICODE_HPP

#include <System/Core.hpp>
#include <iostream>
#include <locale>
#include <string>

namespace System
{
    namespace Text
    {
        class Unicode
        {
        public:
            static std::string Narrow(const std::wstring& source)
            {
                std::string narrowed(source.begin(), source.end());

                return narrowed;
            };

        private:
            Unicode() = default;
        };
    }
}


#endif /* UNICODE_HPP */
