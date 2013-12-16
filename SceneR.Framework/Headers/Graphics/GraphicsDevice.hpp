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

#ifndef GRAPHICSDEVICE_HPP
#define GRAPHICSDEVICE_HPP

#include <Graphics/DepthStencilState.hpp>
#include <Graphics/GraphicsAdapter.hpp>
#include <Graphics/GraphicsProfile.hpp>
#include <Graphics/PresentationParameters.hpp>
#include <Graphics/PrimitiveType.hpp>
#include <Graphics/RasterizerState.hpp>
#include <Graphics/Viewport.hpp>
#include <System/Core.hpp>
#include <memory>

namespace SceneR
{
    namespace Framework
    {
        struct Color;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class Effect;
        class IndexBuffer;
        class VertexBuffer;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Performs primitive-based rendering, creates resources, handles system-level variables,
         * adjusts gamma ramp levels, and creates shaders.
         */
        class GraphicsDevice
        {
        public:
            /**
             * Initializes a new instance of the GraphicsDevice class.
             * @param adapter the display adapter.
             * @param graphicsProfile the graphics profile.
             */
            GraphicsDevice(const GraphicsAdapter& adapter, const GraphicsProfile& graphicsProfile);

            /**
             * Release all resources being used by the GraphicsDevice instance.
             */
            ~GraphicsDevice();

        public:
            /**
             * Clears the resouce buffer
             */
            void Clear(const SceneR::Framework::Color& color) const;

            /**
             * Renders the specified geometric primitive, based on indexing into an array of vertices.
             * @param primitiveType The primitive type.
             * @param baseVertex Offset to add to each vertex index in the index buffer.
             * @param minVertexIndex Minimum vertex index for vertices used during the call.
             *                       The minVertexIndex parameter and all of the indices in the
             *                       index stream are relative to the baseVertex parameter.
             * @param numVertices    Number of vertices used during the call. The first vertex is located at index:
             *                       baseVertex + minVertexIndex.
             * @param startIndex     Location in the index array at which to start reading vertices.
             * @param primitiveCount Number of primitives to render. The number of vertices used is a function of
             *                       primitiveCount and primitiveType.
             */
            void DrawIndexedPrimitives(const PrimitiveType& primitiveType,
                                       const System::UInt32& baseVertex,
                                       const System::UInt32& minVertexIndex,
                                       const System::UInt32& numVertices,
                                       const System::UInt32& startIndex,
                                       const System::UInt32& primitiveCount) const;

            /**
             * Draws a series of instanced models.
             *
             * @param primitiveType The primitive type.
             * @param baseVertex Offset to add to each vertex index in the index buffer.
             * @param minVertexIndex Minimum vertex index for vertices used during the call.
             *                       The minVertexIndex parameter and all of the indices in the index stream are
             *                       relative to the baseVertex parameter.
             * @param numVertices Number of vertices used during the call. The first vertex is located at index:
             *                    baseVertex + minVertexIndex.
             * @param startIndex Location in the index array at which to start reading vertices.
             * @param primitiveCount Number of primitives to render. The number of vertices used is a function of
             *                       primitiveCount and primitiveType.
             * @param instanceCount Number of primitives to render.
             */
            void DrawInstancedPrimitives(const PrimitiveType& primitiveType,
                                         const System::UInt32& baseVertex,
                                         const System::UInt32& minVertexIndex,
                                         const System::UInt32& numVertices,
                                         const System::UInt32& startIndex,
                                         const System::UInt32& primitiveCount,
                                         const System::UInt32& instanceCount) const;

            /**
             * Renders a sequence of non-indexed geometric primitives of the specified type from the current set of data
             * input streams.
             *
             * @param primitiveType The primitive type.
             * @param startVertex Index of the first vertex to load. Beginning at startVertex, the correct number of
             *                    vertices is read out of the vertex buffer.
             * @param primitiveCount Number of primitives to render. The primitiveCount is the number of primitives as
             *                       determined by the primitive type. If it is a line list, each primitive has two
             *                       vertices. If it is a triangle list, each primitive has three vertices.
             */
            void DrawPrimitives(const PrimitiveType&  primitiveType,
                                const System::UInt32& startVertex,
                                const System::UInt32& primitiveCount) const;

            /**
             * Presents the display with the contents of the next buffer in the sequence of back buffers owned by the
             * GraphicsDevice.
             */
            void Present();

            /**
             * Gets the effect used before drawing
             */
            std::shared_ptr<SceneR::Graphics::Effect> Effect();

            /**
             * Sets the effect used before drawing
             */
            void Effect(std::shared_ptr<SceneR::Graphics::Effect> effect);

            /**
             * Gets the display adapter.
             */
            const GraphicsAdapter& Adapter() const;

            /**
             * Gets the graphics profile.
             * @return the graphics profile.
             */
            const GraphicsProfile& GetGraphicsProfile() const;

            /**
             * Gets the depth-stencil state.
             */
            SceneR::Graphics::DepthStencilState& DepthStencilState();

            /**
             * Gets the presentation parameters associated with this graphics device.
             */
            SceneR::Graphics::PresentationParameters& PresentationParameters();

            /**
             * Gets the index buffer.
             * @return the index data
             */
            std::shared_ptr<SceneR::Graphics::IndexBuffer> IndexBuffer();

            /**
             * Sets the index buffer.
             * @param indexBuffer the index data
             */
            void IndexBuffer(const std::shared_ptr<SceneR::Graphics::IndexBuffer>& indexBuffer);

            /**
             * Gets rasterizer state.
             */
            SceneR::Graphics::RasterizerState& RasterizerState();

            /**
             * Gets the current vertex buffer.
             */
            std::shared_ptr<SceneR::Graphics::VertexBuffer> VertexBuffer();

            /**
             * Sets or binds a vertex buffer to the device.
             */
            void VertexBuffer(const std::shared_ptr<SceneR::Graphics::VertexBuffer>& vertexBuffer);

            /**
             * Gets the viewport identifying the portion of the render target to receive draw calls.
             */
            SceneR::Graphics::Viewport& Viewport();

            /**
             * Sets the viewport identifying the portion of the render target to receive draw calls.
             */
            void Viewport(SceneR::Graphics::Viewport& viewport);

        private:
            SceneR::Graphics::DepthStencilState             depthStencilState;
            std::shared_ptr<SceneR::Graphics::Effect>       effect;
            GraphicsAdapter                                 graphicsAdapter;
            GraphicsProfile                                 graphicsProfile;
            std::shared_ptr<SceneR::Graphics::IndexBuffer>  indexBuffer;
            SceneR::Graphics::PresentationParameters        presentationParameters;
            SceneR::Graphics::RasterizerState               rasterizerState;
            std::shared_ptr<SceneR::Graphics::VertexBuffer> vertexBuffer;
            SceneR::Graphics::Viewport                      viewport;
        };
    }
}

#endif  /* GRAPHICSDEVICE_HPP */
