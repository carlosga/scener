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
#include <Content/ContentTypeReaderManager.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <IO/Path.hpp>
#include <memory>
#include <string>

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
            ContentManager(SceneR::Graphics::GraphicsDevice& graphicsDevice,
                           const std::string&                rootDirectory);

            /**
             * Releases all resources being used by the ContentManager class.
             */
            ~ContentManager();

        public:
            /**
             * Gets the graphics device
             */
            SceneR::Graphics::GraphicsDevice& GetGraphicsDevice();

            /**
             * Loads a the given asset.
             */
            template <class T>
            std::shared_ptr<T> Load(const std::string& assetName) throw(ContentLoadException)
            {
                std::shared_ptr<T> asset = nullptr;

                try
                {
                    std::string filename = SceneR::IO::Path::ChangeExtension(assetName, "scr");
                    std::string path     = SceneR::IO::Path::Combine(this->rootDirectory, filename);

                    ContentReader reader(this->graphicsDevice, this->typeReaderManager, path);

                    asset = reader.ReadObject<T>();

                    reader.Close();
                }
                catch (const std::exception& e)
                {
                    throw ContentLoadException(e.what());
                }

                return asset;
            };

            /**
             * Disposes all data that was loaded by this ContentManager.
             */
            void Unload();

        private:
            SceneR::Graphics::GraphicsDevice& graphicsDevice;
            std::string                       rootDirectory;
            ContentTypeReaderManager          typeReaderManager;
        };
    }
}

#endif  /* CONTENTMANAGER_HPP */
