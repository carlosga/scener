// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/GraphicsDevice.hpp>

#include <cstdint>

#include <Graphics/VertexBuffer.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/EffectTechnique.hpp>
#include <Graphics/EffectTechnique.hpp>
#include <Graphics/VertexDeclaration.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Color;

        std::size_t GraphicsDevice::get_element_count(const PrimitiveType& primitiveType
                                                    , const std::size_t&   primitiveCount)
        {
            switch (primitiveType)
            {
            case PrimitiveType::LineList:
                return primitiveCount * 2;

            case PrimitiveType::LineLoop:
                return primitiveCount;

            case PrimitiveType::LineStrip:
                return primitiveCount + 1;

            case PrimitiveType::PointList:
                return primitiveCount;

            case PrimitiveType::TriangleFan:
                return primitiveCount;

            case PrimitiveType::TriangleList:
                return primitiveCount * 3;

            case PrimitiveType::TriangleStrip:
                return primitiveCount + 2;
            }
        }

        GraphicsDevice::GraphicsDevice(const GraphicsAdapter& adapter, const GraphicsProfile& graphicsProfile)
            : effect                   { nullptr }
            , index_buffer             { nullptr }
            , vertex_buffer            { nullptr }
            , _blend_state             { *this }
            , _depth_stencil_state     { *this }
            , _graphics_adapter        { adapter }
            , _graphics_profile        { graphicsProfile }
            , _presentation_parameters { }
            , _rasterizer_state        { *this }
            , _sampler_states          ( )
            , _viewport                { }
        {
            _sampler_states.push_back(SamplerState(*this));
        }

        GraphicsDevice::GraphicsDevice(const GraphicsDevice& device)
            : effect                   { device.effect }
            , index_buffer             { device.index_buffer }
            , vertex_buffer            { device.vertex_buffer }
            , _blend_state             { device._blend_state }
            , _depth_stencil_state     { device._depth_stencil_state }
            , _graphics_adapter        { device._graphics_adapter }
            , _graphics_profile        { device._graphics_profile }
            , _presentation_parameters { device._presentation_parameters }
            , _rasterizer_state        { device._rasterizer_state }
            , _sampler_states          { device._sampler_states }
            , _viewport                { device._viewport }
        {
        }

        GraphicsDevice::~GraphicsDevice()
        {
        }

        void GraphicsDevice::dispose()
        {
            _blend_state.dispose();
            _depth_stencil_state.dispose();
            _rasterizer_state.dispose();

            if (_sampler_states.size() > 0)
            {
                for (auto& sampler : _sampler_states)
                {
                    sampler.dispose();
                }

                _sampler_states.clear();
            }

            if (effect)
            {
                effect = nullptr;
            }
            if (index_buffer)
            {
                index_buffer = nullptr;
            }
            if (vertex_buffer)
            {
                vertex_buffer = nullptr;
            }
        }

        void GraphicsDevice::clear(const Color& color) const
        {
            std::uint32_t bufferBits = GL_COLOR_BUFFER_BIT;

            glClearColor(color.r, color.g, color.b, color.a);

            if (_depth_stencil_state.depth_buffer_enable)
            {
                bufferBits |= GL_DEPTH_BUFFER_BIT;
                glClearDepth(1.0f);
            }
            if (_depth_stencil_state.stencil_enable)
            {
                bufferBits |= GL_STENCIL_BUFFER_BIT;
                glClearStencil(1);
            }

            glClear(bufferBits);
        }

        void GraphicsDevice::draw_indexed_primitives(const PrimitiveType& primitiveType
                                                   , const std::size_t&   baseVertex
                                                   , const std::size_t&   minVertexIndex
                                                   , const std::size_t&   numVertices
                                                   , const std::size_t&   startIndex
                                                   , const std::size_t&   primitiveCount) const
        {
            if (index_buffer == nullptr)
            {
                throw std::runtime_error("Set the IndexBuffer before calling DrawIndexedPrimitives");
            }
            if (vertex_buffer == nullptr)
            {
                throw std::runtime_error("Set the VertexBuffer before calling DrawIndexedPrimitives");
            }
            if (effect.get() == nullptr)
            {
                throw std::runtime_error("Set the effect before calling DrawIndexedPrimitives");
            }

            auto offset = startIndex * index_buffer->element_size_in_bytes();

            effect->begin();
            vertex_buffer->activate();
            index_buffer->activate();

            glDrawElementsBaseVertex(static_cast<GLenum>(primitiveType)
                                   , static_cast<GLsizei>(get_element_count(primitiveType, primitiveCount))
                                   , static_cast<GLenum>(index_buffer->index_element_type())
                                   , reinterpret_cast<void*>(offset)
                                   , static_cast<GLint>(baseVertex));

            index_buffer->deactivate();
            vertex_buffer->deactivate();
            effect->end();
        }

        void GraphicsDevice::draw_primitives(const PrimitiveType& primitiveType
                                           , const std::size_t&   startVertex
                                           , const std::size_t&   primitiveCount) const
        {
            if (vertex_buffer == nullptr)
            {
                throw std::runtime_error("Set the VertexBuffer before calling DrawIndexedPrimitives");
            }
            if (effect.get() == nullptr)
            {
                throw std::runtime_error("Set the effect before calling DrawIndexedPrimitives");
            }

            effect->begin();
            vertex_buffer->activate();

            glDrawArrays(static_cast<GLenum>(primitiveType)
                       , static_cast<GLint>(startVertex)
                       , static_cast<GLsizei>(primitiveCount));

            vertex_buffer->deactivate();
            effect->end();
        }

        void GraphicsDevice::present()
        {
            glfwSwapBuffers(glfwGetCurrentContext());
        }

        const GraphicsAdapter& GraphicsDevice::adapter() const
        {
            return _graphics_adapter;
        }

        const GraphicsProfile& GraphicsDevice::graphics_profile() const
        {
            return _graphics_profile;
        }

        BlendState& GraphicsDevice::blend_state()
        {
            return _blend_state;
        }

        DepthStencilState& GraphicsDevice::depth_stencil_state()
        {
            return _depth_stencil_state;
        }

        PresentationParameters& GraphicsDevice::presentation_parameters()
        {
            return _presentation_parameters;
        }

        RasterizerState& GraphicsDevice::rasterizer_state()
        {
            return _rasterizer_state;
        }

        std::vector<SamplerState>& GraphicsDevice::sampler_states()
        {
            return _sampler_states;
        }

        Viewport& GraphicsDevice::viewport()
        {
           return _viewport;
        }

        void GraphicsDevice::viewport(const Viewport& viewport)
        {
            _viewport = viewport;
            _viewport.update();
        }

        GraphicsDevice& GraphicsDevice::operator=(const GraphicsDevice& device)
        {
            if (this != &device)
            {
                effect                   = std::move(device.effect);
                index_buffer             = std::move(device.index_buffer);
                vertex_buffer            = device.vertex_buffer;
                _blend_state             = device._blend_state;
                _depth_stencil_state     = device._depth_stencil_state;
                _graphics_adapter        = device._graphics_adapter;
                _graphics_profile        = device._graphics_profile;
                _presentation_parameters = device._presentation_parameters;
                _rasterizer_state        = device._rasterizer_state;
                _sampler_states          = device._sampler_states;
                _viewport                = device._viewport;
            }

            return *this;
        }
    }
}
