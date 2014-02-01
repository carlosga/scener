//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef FILE_HPP
#define FILE_HPP

#include <System/Core.hpp>
#include <System/Text/Encoding.hpp>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>

namespace System
{
    namespace IO
    {
        /**
         * Provides static methods for file access handling.
         */
        class File
        {
        public:
			/**
			 * Checks whether the given file exists.
			 */ 
			static Boolean Exists(const System::String& path)
			{
			    auto result = true;
				auto file   = std::fstream(System::Text::Encoding::Convert(path), std::ios::in);

				if (!file || !file.good())
                {
				    result = false;
                }
				else
				{
				    file.close();
				}
				
				return result;
			};
		
            /**
             * Opens a text file, reads all lines of the file, and then closes the file.
             */
            static System::String ReadAllText(const System::String& path)
            {
                auto stream = std::wifstream(System::Text::Encoding::Convert(path), std::ios::in | std::ios::binary);

                assert(stream.is_open());

                stream.seekg(0, std::ios_base::beg);
                std::wstringstream buffer;

                buffer << stream.rdbuf();

                stream.close();

                auto text = buffer.str();

                return String(text.begin(), text.end());
            };

        private:
            File() = delete;
			File(const File& file) = delete;
			File& operator=(const File& file) = delete;
        };
    }
}

#endif  /* FILE_HPP */
