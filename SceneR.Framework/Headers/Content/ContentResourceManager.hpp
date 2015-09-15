// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_CONTENTRESOURCEMANAGER_HPP
#define CONTENT_CONTENTRESOURCEMANAGER_HPP

#include <memory>
#include <map>

#include <System/IDisposable.hpp>
#include <Graphics/GraphicsResource.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentResourceManager final
        {
        public:
            /**
            * Initializes a new instance of the ContentResourceManager
            */
            ContentResourceManager()
            {
            }

            /**
            * Releases all resources being used by the ContentResourceManager class.
            */
            ~ContentResourceManager()
            {
            }

        public:
            template <class T>
            void add_resource(const std::u16string& name, std::shared_ptr<T> resource)
            {
                if (!has_resource(name))
                {
                    _resources[name] = std::static_pointer_cast<void>(resource);
                }
            }

            template <class T>
            std::shared_ptr<T> get_resource(const std::u16string& name) const
            {
                if (has_resource(name))
                {
                    return std::static_pointer_cast<T>(_resources.find(name)->second);
                }

                return nullptr;
            }

            bool has_resource(const std::u16string& name) const
            {
                return (_resources.find(name) != _resources.end());
            }

            void clear()
            {
                if (_resources.size() > 0)
                {
                    for (auto kvp : _resources)
                    {
                        if (kvp.second.get() != nullptr)
                        {
                            auto disposable = std::static_pointer_cast<System::IDisposable>(kvp.second);

                            if (disposable.get() != nullptr)
                            {
                                disposable->dispose();
                            }
                        }
                    }

                    _resources.clear();
                }
            }

        private:
            ContentResourceManager(const ContentResourceManager& manager) = delete;
            ContentResourceManager& operator=(const ContentResourceManager& manager) = delete;

        private:
            std::map<std::u16string, std::shared_ptr<void>> _resources;
        };
    }
}

#endif  // CONTENT_CONTENTRESOURCEMANAGER_HPP
