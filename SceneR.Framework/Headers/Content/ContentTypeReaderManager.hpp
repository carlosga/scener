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

#ifndef CONTENTTYPEREADERMANAGER_HPP
#define CONTENTTYPEREADERMANAGER_HPP

#include <Content/ContentTypeReader.hpp>
#include <System/Core.hpp>
#include <map>

namespace SceneR
{
    namespace Content
    {
        /**
         * Content type reader manager.
         */
        class ContentTypeReaderManager
        {
        public:
            /**
             * Initializes a new instance of the ContentTypeReaderManager class.
             */
            ContentTypeReaderManager();

            /**
             * Releases all resources being used by this ContentTypeReaderManager instance.
             */
            ~ContentTypeReaderManager();

        public:
            /**
             * Gets the content type reader for the specified content tpe
             */
            ContentTypeReader* GetByReaderName(const System::String& name);

        private:
            void RegisterKnownTypeReaders();

            template<class T>
            void RegisterTypeReader(const System::String& name)
            {
                this->readers[name] = new T;
            };

        private:
            std::map<System::String, ContentTypeReader*> readers;
        };
    }
}

#endif  /* CONTENTTYPEREADERMANAGER_HPP */
