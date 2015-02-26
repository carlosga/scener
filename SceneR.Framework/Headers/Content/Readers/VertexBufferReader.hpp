// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VERTEXBUFFERREADER_HPP
#define VERTEXBUFFERREADER_HPP

#include <Graphics/VertexDeclaration.hpp>
#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Vertex buffer reader
         */
        class VertexBufferReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the VertexBufferReader class.
             */
            VertexBufferReader();

            /**
             * Destructor
             */
            ~VertexBufferReader() override;

        public:
            /**
             * Reads the vertex buffer contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;

        private:
            std::shared_ptr<SceneR::Graphics::VertexDeclaration> ReadVertexDeclaration(ContentReader& input);
        };
    }
}

#endif  /* VERTEXBUFFERREADER_HPP */
