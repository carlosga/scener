// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICSDEVICE_HPP
#define GRAPHICSDEVICE_HPP

#include <cstddef>
#include <memory>
#include <vector>

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
        private:
                static std::size_t get_element_count(const PrimitiveType& primitiveType
                                                   , const std::size_t&   primitiveCount);

        public:
            /**
             * Initializes a new instance of the GraphicsDevice class.
             * @param adapter the display adapter.
             * @param graphicsProfile the graphics profile.
             */
            GraphicsDevice(const GraphicsAdapter&                   adapter
                         , const SceneR::Graphics::GraphicsProfile& graphicsProfile);

            /**
             * @brief GraphicsDevice Initializes a new instance of the GraphicsDevice class. Copy constructor.
             * @param device the graphics device to copy from.
             */
            GraphicsDevice(const GraphicsDevice& device);

            /**
             * Release all resources being used by the GraphicsDevice instance.
             */
            ~GraphicsDevice() override;

        public:
            void dispose() override;

        public:
            /**
             * Clears the resouce buffer
             */
            void clear(const SceneR::Framework::Color& color) const;

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
            void draw_indexed_primitives(const PrimitiveType& primitiveType
                                       , const std::size_t&   baseVertex
                                       , const std::size_t&   minVertexIndex
                                       , const std::size_t&   numVertices
                                       , const std::size_t&   startIndex
                                       , const std::size_t&   primitiveCount) const;

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
            void draw_primitives(const PrimitiveType& primitiveType
                               , const std::size_t&   startVertex
                               , const std::size_t&   primitiveCount) const;

            /**
             * Presents the display with the contents of the next buffer in the sequence of back buffers owned by the
             * GraphicsDevice.
             */
            void present();

            /**
             * Gets the display adapter.
             */
            const GraphicsAdapter& adapter() const;

            /**
             * Gets the graphics profile.
             * @return the graphics profile.
             */
            const SceneR::Graphics::GraphicsProfile& graphics_profile() const;

            /**
             * Gets or sets a system-defined instance of a blend state object initialized for alpha blending.
             * The default value is BlendState.Opaque.
             */
            SceneR::Graphics::BlendState& blend_state();

            /**
             * Gets the depth-stencil state.
             */
            SceneR::Graphics::DepthStencilState& depth_stencil_state();

            /**
             * Gets the presentation parameters associated with this graphics device.
             */
            SceneR::Graphics::PresentationParameters& presentation_parameters();

            /**
             * Gets rasterizer state.
             */
            SceneR::Graphics::RasterizerState& rasterizer_state();

            /**
             * Retrieves a collection of SamplerState objects for the current GraphicsDevice.
             */
            std::vector<SceneR::Graphics::SamplerState>& sampler_states();

            /**
             * Gets the viewport identifying the portion of the render target to receive draw calls.
             */
            Viewport& viewport();

            /**
             * Sets the viewport identifying the portion of the render target to receive draw calls.
             */
            void viewport(const Viewport& viewport);

        public:
            GraphicsDevice& operator=(const GraphicsDevice& device);

        private:
            GraphicsDevice() = delete;

        public:
            /**
             * Gets or sets the effect used before drawing.
             */
            std::shared_ptr<SceneR::Graphics::Effect> effect;

            /**
             * Gets or sets the index buffer.
             */
            SceneR::Graphics::IndexBuffer* index_buffer;

            /**
             * Sets or binds a vertex buffer to the device.
             */
            SceneR::Graphics::VertexBuffer* vertex_buffer;

        private:
            SceneR::Graphics::BlendState                _blend_state;
            SceneR::Graphics::DepthStencilState         _depth_stencil_state;
            GraphicsAdapter                             _graphics_adapter;
            SceneR::Graphics::GraphicsProfile           _graphics_profile;
            SceneR::Graphics::PresentationParameters    _presentation_parameters;
            SceneR::Graphics::RasterizerState           _rasterizer_state;
            std::vector<SceneR::Graphics::SamplerState> _sampler_states;
            SceneR::Graphics::Viewport                  _viewport;
        };
    }
}

#endif  /* GRAPHICSDEVICE_HPP */
