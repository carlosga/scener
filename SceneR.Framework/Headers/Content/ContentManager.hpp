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

#ifndef CONTENTMANAGER_HPP
#define CONTENTMANAGER_HPP

#include <Content/ContentLoadException.hpp>
#include <Content/ContentReader.hpp>
#include <System/Core.hpp>
#include <System/IO/File.hpp>
#include <System/IO/FileStream.hpp>
#include <System/IO/Path.hpp>
#include <memory>
#include <stdexcept>

namespace SceneR
{
    namespace Framework
    {
        class RendererServiceContainer;
    }
}

namespace SceneR
{
    namespace Content
    {
        /**
         * The ContentManager is used at runtime to load application content from files.
         */
        class ContentManager
        {
        public:
            /**
             * Initializes a new instance of the ContentManagerClass
             */
            ContentManager(SceneR::Framework::RendererServiceContainer& serviceProvider,
                           const System::String&                        rootDirectory);

            /**
             * Releases all resources being used by the ContentManager class.
             */
            ~ContentManager();

        public:
            /**
             * Gets the graphics device
             */
            SceneR::Framework::RendererServiceContainer& ServiceProvider();

            /**
             * Gets the root directory associated with this ContentManager.
             */
            const System::String RootDirectory();

            /**
             * Disposes all data that was loaded by this ContentManager.
             */
            void Unload();

            /**
             * Loads a the given asset.
             */
            template <class T>
            std::shared_ptr<T> Load(const System::String& assetName) throw(ContentLoadException)
            {
                std::shared_ptr<T> asset = nullptr;

                try
                {
                    auto filename = System::IO::Path::ChangeExtension(assetName, u"xnb");
                    auto path     = System::IO::Path::Combine(this->rootDirectory, filename);

                    if (!System::IO::File::Exists(path))
                    {
                        throw std::runtime_error("the asset file doesn't exists.");
                    }

                    System::IO::FileStream stream(path);
                    ContentReader reader(assetName, *this, stream);

                    asset = reader.ReadObject<T>();

                    reader.ReadSharedResources();

                    reader.Close();
                }
                catch (const std::exception& e)
                {
                    throw ContentLoadException(e.what());
                }

                return asset;
            };

        private:
            SceneR::Framework::RendererServiceContainer& serviceProvider;
            System::String                               rootDirectory;
        };
    }
}

#endif  /* CONTENTMANAGER_HPP */
