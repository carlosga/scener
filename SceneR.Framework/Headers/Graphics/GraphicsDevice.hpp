// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICSDEVICE_HPP
#define GRAPHICSDEVICE_HPP

#include <memory>
#include <vector>

#include <System/Core.hpp>
#include <System/IDisposable.hpp>
#include <Framework/Color.hpp>
#include <Graphics/BlendState.hpp>
#include <Graphics/DepthStencilState.hpp>
#include <Graphics/GraphicsProfile.hpp>
#include <Graphics/GraphicsAdapter.hpp>
#include <Graphics/PresentationParameters.hpp>
#include <Graphics/PrimitiveType.hpp>
#include <Graphics/RasterizerState.hpp>
#include <Graphics/SamplerState.hpp>
#include <Graphics/Viewport.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class Effect;
        class IndexBuffer;
        class VertexBuffer;

        /**
         * Performs primitive-based rendering, creates resources, handles system-level variables,
         * adjusts gamma ramp levels, and creates shaders.
         */
        class GraphicsDevice final : System::IDisposable
        {
        public:
            /**
             * Initializes a new instance of the GraphicsDevice class.
             * @param adapter the display adapter.
             * @param graphicsProfile the graphics profile.
             */
            GraphicsDevice(const GraphicsAdapter&                   adapter
                         , const SceneR::Graphics::GraphicsProfile& graphicsProfile);

            GraphicsDevice(const GraphicsDevice& device);

            /**
             * Release all resources being used by the GraphicsDevice instance.
             */
            ~GraphicsDevice() override;

        public:
            void Dispose() override;

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
            void DrawIndexedPrimitives(const PrimitiveType&  primitiveType
                                     , const System::UInt32& baseVertex
                                     , const System::UInt32& minVertexIndex
                                     , const System::UInt32& numVertices
                                     , const System::UInt32& startIndex
                                     , const System::UInt32& primitiveCount) const;

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
            void DrawPrimitives(const PrimitiveType&  primitiveType
                              , const System::UInt32& startVertex
                              , const System::UInt32& primitiveCount) const;

            /**
             * Presents the display with the contents of the next buffer in the sequence of back buffers owned by the
             * GraphicsDevice.
             */
            void Present();

            /**
             * Gets the effect used before drawing
             */
            const std::shared_ptr<SceneR::Graphics::Effect>& Effect();

            /**
             * Sets the effect used before drawing
             */
            void Effect(const std::shared_ptr<SceneR::Graphics::Effect>& effect);

            /**
             * Gets the display adapter.
             */
            const GraphicsAdapter& Adapter() const;

            /**
             * Gets the graphics profile.
             * @return the graphics profile.
             */
            const SceneR::Graphics::GraphicsProfile& GraphicsProfile() const;

            /**
             * Gets or sets a system-defined instance of a blend state object initialized for alpha blending.
             * The default value is BlendState.Opaque.
             */
            SceneR::Graphics::BlendState& BlendState();

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
             * Retrieves a collection of SamplerState objects for the current GraphicsDevice.
             */
            std::vector<SceneR::Graphics::SamplerState>& SamplerStates();

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

        public:
            GraphicsDevice& operator=(const GraphicsDevice& device);

        private:
            GraphicsDevice() = delete;

        private:
            SceneR::Graphics::BlendState                    blendState;
            SceneR::Graphics::DepthStencilState             depthStencilState;
            std::shared_ptr<SceneR::Graphics::Effect>       effect;
            GraphicsAdapter                                 graphicsAdapter;
            SceneR::Graphics::GraphicsProfile               graphicsProfile;
            std::shared_ptr<SceneR::Graphics::IndexBuffer>  indexBuffer;
            SceneR::Graphics::PresentationParameters        presentationParameters;
            SceneR::Graphics::RasterizerState               rasterizerState;
            std::vector<SceneR::Graphics::SamplerState>     samplerStates;
            std::shared_ptr<SceneR::Graphics::VertexBuffer> vertexBuffer;
            SceneR::Graphics::Viewport                      viewport;
        };
    }
}

#endif  /* GRAPHICSDEVICE_HPP */
