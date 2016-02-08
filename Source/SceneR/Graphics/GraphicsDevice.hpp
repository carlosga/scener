// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_GRAPHICSDEVICE_HPP
#define SCENER_GRAPHICS_GRAPHICSDEVICE_HPP

#include <cstddef>
#include <memory>

#include "SceneR/Graphics/BlendState.hpp"
#include "SceneR/Graphics/DepthStencilState.hpp"
#include "SceneR/Graphics/PresentationParameters.hpp"
#include "SceneR/Graphics/PrimitiveType.hpp"
#include "SceneR/Graphics/RasterizerState.hpp"
#include "SceneR/Graphics/Viewport.hpp"
#include "SceneR/Math/Color.hpp"

namespace SceneR { namespace Graphics {

class EffectTechnique;
class IndexBuffer;
class VertexBuffer;

/// Performs primitive-based rendering, creates resources, handles system-level variables, adjusts gamma ramp levels,
/// and creates shaders.
class GraphicsDevice final
{
private:
    static constexpr std::size_t get_element_count(PrimitiveType primitiveType, std::size_t primitiveCount) noexcept
    {
        switch (primitiveType)
        {
        case PrimitiveType::line_list:
            return primitiveCount * 2;

        case PrimitiveType::line_loop:
            return primitiveCount;

        case PrimitiveType::line_strip:
            return primitiveCount + 1;

        case PrimitiveType::point_list:
            return primitiveCount;

        case PrimitiveType::triangle_fan:
            return primitiveCount;

        case PrimitiveType::triangle_list:
            return primitiveCount * 3;

        case PrimitiveType::triangle_strip:
            return primitiveCount + 2;
        }
    }

public:
    /// Initializes a new instance of the GraphicsDevice class.
    GraphicsDevice() noexcept;

public:
    /// Clears the resouce buffer
    void clear(const SceneR::Math::Color& color) const noexcept;

    /// Renders the specified geometric primitive, based on indexing into an array of vertices.
    /// \param primitiveType The primitive type.
    /// \param baseVertex Offset to add to each vertex index in the index buffer.
    /// \param minVertexIndex Minimum vertex index for vertices used during the call.
    ///                       The minVertexIndex parameter and all of the indices in the
    ///                       index stream are relative to the baseVertex parameter.
    /// \param numVertices    Number of vertices used during the call. The first vertex is located at index:
    /// \                     baseVertex + minVertexIndex.
    /// \param startIndex     Location in the index array at which to start reading vertices.
    /// \param primitiveCount Number of primitives to render. The number of vertices used is a function of
    ///                       primitiveCount and primitiveType.
    void draw_indexed_primitives(PrimitiveType primitiveType
                               , std::size_t   baseVertex
                               , std::size_t   minVertexIndex
                               , std::size_t   numVertices
                               , std::size_t   startIndex
                               , std::size_t   primitiveCount) const noexcept;

    /// Renders a sequence of non-indexed geometric primitives of the specified type from the current set of data
    /// input streams.
    /// \param primitiveType The primitive type.
    /// \param startVertex Index of the first vertex to load. Beginning at startVertex, the correct number of
    ///                    vertices is read out of the vertex buffer.
    /// \param primitiveCount Number of primitives to render. The primitiveCount is the number of primitives as
    ///                       determined by the primitive type. If it is a line list, each primitive has two
    ///                       vertices. If it is a triangle list, each primitive has three vertices.
    void draw_primitives(PrimitiveType primitiveType, std::size_t startVertex, std::size_t primitiveCount) const noexcept;

    /// Presents the display with the contents of the next buffer in the sequence of back buffers owned by the
    /// GraphicsDevice.
    void present() noexcept;

    /// Gets or sets a system-defined instance of a blend state object initialized for alpha blending.
    /// The default value is BlendState.Opaque.
    BlendState& blend_state() noexcept;

    /// Gets the depth-stencil state.
    DepthStencilState& depth_stencil_state() noexcept;

    /// Gets the presentation parameters associated with this graphics device.
    PresentationParameters& presentation_parameters() noexcept;

    /// Gets rasterizer state.
    RasterizerState& rasterizer_state() noexcept;

    /// Gets the viewport identifying the portion of the render target to receive draw calls.
    Viewport& viewport() noexcept;

    /// Sets the viewport identifying the portion of the render target to receive draw calls.
    void viewport(const Viewport& viewport) noexcept;

public:
    /// Gets or sets the effect used before drawing.
    EffectTechnique* effect;

    /// Gets or sets the index buffer.
    IndexBuffer* index_buffer;

    /// Gets or sets the vertex buffer.
    VertexBuffer* vertex_buffer;

private:
    BlendState             _blend_state;
    DepthStencilState      _depth_stencil_state;
    PresentationParameters _presentation_parameters;
    RasterizerState        _rasterizer_state;
    Viewport               _viewport;
};

}}

#endif // SCENER_GRAPHICS_GRAPHICSDEVICE_HPP
