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

#ifndef CONTENTREADER_HPP
#define	CONTENTREADER_HPP

#include <fstream>
#include <string>
#include <vector>
#include "Core/Core.hpp"
#include "Core/Matrix.hpp"
#include "Core/Quaternion.hpp"
#include "Core/Vector2.hpp"
#include "Core/Vector3.hpp"
#include "Core/Vector4.hpp"
#include "Core/Color.hpp"
#include "Content/ContentType.hpp"
#include "Content/ContentTypeReader.hpp"
#include "Content/ContentTypeReaderManager.hpp"
#include "Graphics/GraphicsDevice.hpp"

namespace SceneR
{
    namespace Content
    {
        /**
         * Reads application content from disk
         */
        class ContentReader
        {
        public:
            /**
             * Initializes a new instance of the ContentReader.
             * @param graphicsDevice the graphics device.
             * @param typeReaderManager the type reader manager.
             * @param filePath the file path to read.
             */
            ContentReader(SceneR::Graphics::GraphicsDevice& graphicsDevice,
                          ContentTypeReaderManager&         typeReaderManager,
                          const std::string&                file);

            /**
             * Releases all resources used by the current instance of the ContentReader class.
             */
            ~ContentReader();

        public:
            /**
             * Closes the current reader and the underlying stream.
             */
            void Close();

            /**
             * Gets the graphics device.
             */
            SceneR::Graphics::GraphicsDevice& GetGraphicsDevice();

            /**
             * Reads a single object from the current stream.
             */
            template<class T>
            std::shared_ptr<T> ReadObject()
            {
                ContentType        contentType = static_cast<ContentType> (this->ReadInt32());
                ContentTypeReader* reader      = this->typeReaderManager.GetReaderForContentType(contentType);

                return this->ReadObject<T>(reader);
            }

            /**
             * Reads a single object from the current stream.
             */
            template<class T>
            std::shared_ptr<T> ReadObject(ContentTypeReader* typeReader)
            {
                return std::static_pointer_cast<T>(typeReader->Read(this));
            }

            /**
             * Reads the next character from the current stream.
             */
            wchar_t ReadChar();

            /**
             * Reads a string from the current stream. The string is prefixed with the length.
             */
            std::wstring ReadString();

            /**
             * Reads a 7-bit encoded int
             */
            UInt32 Read7BitEncodedInt();

            /**
             * Reads the next byte from the current stream.
             */
            UInt32 ReadByte();

            /**
             * Reads a 2-byte signed integer from the current stream.
             */
            Int16 ReadInt16();

            /**
             * Reads a 2-byte unsigned integer from the current stream.
             */
            UInt16 ReadUInt16();

            /**
             * Reads a 4-byte signed integer from the current stream.
             */
            Int32 ReadInt32();

            /**
             * Reads a 4-byte unsigned integer from the current stream.
             */
            UInt32 ReadUInt32();

            /**
             * Reads a float value from the currently open stream.
             */
            Single ReadSingle();

            /**
             * Reads a double value from the currently open stream.
             */
            Double ReadDouble();

            /**
             * Reads a Color value from the current stream.
             */
            SceneR::Core::Color ReadColor();

            /**
             * Reads a Matrix value from the current stream.
             */
            SceneR::Core::Matrix ReadMatrix();

            /**
             * Reads a Vector2 value from the current stream.
             */
            SceneR::Core::Vector2 ReadVector2();

            /**
             * Reads a Vector3 value from the current stream.
             */
            SceneR::Core::Vector3 ReadVector3();

            /**
             * Reads a Vector4 value from the current stream.
             */
            SceneR::Core::Vector4 ReadVector4();

            /**
             * Reads a Quaternion value from the current stream.
             */
            SceneR::Core::Quaternion ReadQuaternion();

            /**
             * Reads the specified number of bytes from the underliying stream
             */
            std::vector<Int16> ReadBytes(int count);

            const int Position();

        private:
            void ReadHeader();

        private:
            SceneR::Graphics::GraphicsDevice& graphicsDevice;
            std::ifstream                     stream;
            ContentTypeReaderManager&         typeReaderManager;
        };
    }
}

#endif	/* CONTENTREADER_HPP */
