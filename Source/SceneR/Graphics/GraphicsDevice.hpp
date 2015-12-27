// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_GRAPHICSDEVICE_HPP
#define SCENER_GRAPHICS_GRAPHICSDEVICE_HPP

#include <cstddef>
#include <memory>

#include "BlendState.hpp"
#include "DepthStencilState.hpp"
#include "PresentationParameters.hpp"
#include "PrimitiveType.hpp"
#include "RasterizerState.hpp"
#include "Viewport.hpp"
#include "../Core/IDisposable.hpp"
#include "../Math/Color.hpp"

namespace SceneR
{
    namespace Graphics
    {
        class EffectTechnique;
        class IndexBuffer;
        class VertexBuffer;

        /**
         * Performs primitive-based rendering, creates resources, handles system-level variables,
         * adjusts gamma ramp levels, and creates shaders.
         */
        class GraphicsDevice final : SceneR::IDisposable
        {
        private:
                static std::size_t get_element_count(const PrimitiveType& primitiveType
                                                   , const std::size_t&   primitiveCount) noexcept;

        public:
            /**
             * Initializes a new instance of the GraphicsDevice class.
             * @param adapter the display adapter.
             * @param graphicsProfile the graphics profile.
             */
            GraphicsDevice() noexcept;

            /**
             * @brief GraphicsDevice Initializes a new instance of the GraphicsDevice class. Copy constructor.
             * @param device the graphics device to copy from.
             */
            GraphicsDevice(const GraphicsDevice& device) = default;

            /**
             * Release all resources being used by the GraphicsDevice instance.
             */
            virtual ~GraphicsDevice() override = default;

        public:
            virtual void dispose() override;

        public:
            /**
             * Clears the resouce buffer
             */
            void clear(const SceneR::Math::Color& color) const;

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
             * Gets or sets a system-defined instance of a blend state object initialized for alpha blending.
             * The default value is BlendState.Opaque.
             */
            BlendState& blend_state() noexcept;

            /**
             * Gets the depth-stencil state.
             */
            DepthStencilState& depth_stencil_state() noexcept;

            /**
             * Gets the presentation parameters associated with this graphics device.
             */
            PresentationParameters& presentation_parameters() noexcept;

            /**
             * Gets rasterizer state.
             */
            RasterizerState& rasterizer_state() noexcept;

            /**
             * Gets the viewport identifying the portion of the render target to receive draw calls.
             */
            Viewport& viewport() noexcept;

            /**
             * Sets the viewport identifying the portion of the render target to receive draw calls.
             */
            void viewport(const Viewport& viewport) noexcept;

        public:
            GraphicsDevice& operator=(const GraphicsDevice& device) = default;

        public:
            /**
             * Gets or sets the effect used before drawing.
             */
            EffectTechnique* effect;

            /**
             * Gets or sets the index buffer.
             */
            IndexBuffer* index_buffer;

            /**
             * Sets or binds a vertex buffer to the device.
             */
            VertexBuffer* vertex_buffer;

        private:
            BlendState             _blend_state;
            DepthStencilState      _depth_stencil_state;
            PresentationParameters _presentation_parameters;
            RasterizerState        _rasterizer_state;
            Viewport               _viewport;
        };
    }
}

#endif // SCENER_GRAPHICS_GRAPHICSDEVICE_HPP
