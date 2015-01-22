// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

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
            VertexDeclarationReader() = default;

            /**
             * Releases all resources being used by this VertexDeclarationReader.
             */
            virtual ~VertexDeclarationReader() = default;

        public:
            /**
             * Reads the string contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* VERTEXDECLARATIONREADER_HPP */
