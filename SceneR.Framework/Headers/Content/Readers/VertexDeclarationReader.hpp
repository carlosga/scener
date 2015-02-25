// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VERTEXDECLARATIONREADER_HPP
#define VERTEXDECLARATIONREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Vertex declaration reader
         */
        class VertexDeclarationReader: public SceneR::Content::ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the VertexDeclarationReader class.
             */
            VertexDeclarationReader();

            /**
             * Releases all resources being used by this VertexDeclarationReader.
             */
            ~VertexDeclarationReader();

        public:
            /**
             * Reads the vertex declaration contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* VERTEXDECLARATIONREADER_HPP */
