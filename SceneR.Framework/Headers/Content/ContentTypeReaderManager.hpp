// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENTTYPEREADERMANAGER_HPP
#define CONTENTTYPEREADERMANAGER_HPP

#include <map>
#include <string>

#include "ContentTypeReader.hpp"

namespace SceneR
{
    namespace Content
    {
        /**
         * content_manager type reader manager.
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
             * Gets the content type reader for the specified content_manager tpe
             */
            ContentTypeReader* get_by_reader_name(const std::string& name);

        private:
            void register_known_type_readers();

            template<class T>
            void register_type_reader(const std::string& name)
            {
                _readers[name] = new T;
            }

        private:
            ContentTypeReaderManager(const ContentTypeReaderManager& manager) = delete;
            ContentTypeReaderManager& operator=(const ContentTypeReaderManager& manager) = delete;

        private:
            std::map<std::string, ContentTypeReader*> _readers;
        };
    }
}

#endif  /* CONTENTTYPEREADERMANAGER_HPP */
