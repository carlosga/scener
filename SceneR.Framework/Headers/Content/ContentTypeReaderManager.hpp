// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENTTYPEREADERMANAGER_HPP
#define CONTENTTYPEREADERMANAGER_HPP

#include <map>
#include <string>

#include <System/Core.hpp>
#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Content type reader manager.
         */
        class ContentTypeReaderManager final
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
            ContentTypeReader* GetByReaderName(const std::u16string& name);

        private:
            void RegisterKnownTypeReaders();

            template<class T>
            void RegisterTypeReader(const std::u16string& name)
            {
                this->readers[name] = new T;
            }

        private:
            ContentTypeReaderManager(const ContentTypeReaderManager& manager) = delete;
            ContentTypeReaderManager& operator=(const ContentTypeReaderManager& manager) = delete;

        private:
            std::map<std::u16string, ContentTypeReader*> readers;
        };
    }
}

#endif  /* CONTENTTYPEREADERMANAGER_HPP */
