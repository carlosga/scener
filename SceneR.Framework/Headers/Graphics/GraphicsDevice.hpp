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

#include <memory>
#include "Core/Core.hpp"
#include "Core/Color.hpp"
#include "Graphics/DepthStencilState.hpp"
#include "Graphics/GraphicsProfile.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/PresentationParameters.hpp"
#include "Graphics/PrimitiveType.hpp"
#include "Graphics/RasterizerState.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/Viewport.hpp"

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDeviceManager;
        class Effect;

        /**
         * Performs primitive-based rendering, creates resources, handles system-level variables,
         * adjusts gamma ramp levels, and creates shaders.
         */
        class GraphicsDevice
        {
        public:
            /**
             * Initializes a new instance of the GraphicsDevice class.
             *
             * @param graphicsProfile the graphics profile.
             */
            GraphicsDevice(const GraphicsProfile& graphicsProfile);
            
            /**
             * Release all resources being used by the GraphicsDevice instance.
             */
            ~GraphicsDevice();
            
        public:
            /**
             * Clears the resouce buffer
             */
            void Clear(const SceneR::Core::Color& color) const;

            /**
             * Renders the specified geometric primitive, based on indexing into an array of vertices.
             * 
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
                                       const UInt32& baseVertex,
                                       const UInt32& minVertexIndex,
                                       const UInt32& numVertices,
                                       const UInt32& startIndex,
                                       const UInt32& primitiveCount) const;

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
                                         const UInt32& baseVertex,
                                         const UInt32& minVertexIndex,
                                         const UInt32& numVertices,
                                         const UInt32& startIndex,
                                         const UInt32& primitiveCount,
                                         const UInt32& instanceCount) const;
                
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
            void DrawPrimitives(const PrimitiveType& primitiveType,
                                const UInt32&        startVertex,
                                const UInt32&        primitiveCount) const;

            /**
             * Presents the display with the contents of the next buffer in the sequence of back buffers owned by the 
             * GraphicsDevice.
             */
            void Present();

            /**
             * Gets the effect used before drawing
             */
            std::shared_ptr<Effect> GetEffect();

            /**
             * Sets the effect used before drawing
             */
            void SetEffect(std::shared_ptr<Effect> effect);

            /**
             * Gets the graphics profile.
             * @return the graphics profile.
             */
            const GraphicsProfile& GetGraphicsProfile() const;

            /**
             * Gets the depth-stencil state.
             */
            DepthStencilState& GetDepthStencilState();

            /**
             * Gets the presentation parameters associated with this graphics device.
             */
            PresentationParameters& GetPresentationParameters();

            /**
             * Gets the index buffer.
             * @return the index data
             */
            std::shared_ptr<IndexBuffer> GetIndexBuffer();

            /**
             * Sets the index buffer.
             * @param indexBuffer the index data
             */
            void SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer);

            /**
             * Gets rasterizer state.
             */
            RasterizerState& GetRasterizerState();

            /**
             * Gets the current vertex buffer.
             */
            std::shared_ptr<VertexBuffer> GetVertexBuffer();

            /**
             * Sets or binds a vertex buffer to the device.
             */
            void SetVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer);

            /**
             * Gets the viewport identifying the portion of the render target to receive draw calls.
             */
            Viewport& GetViewport();

            /**
             * Sets the viewport identifying the portion of the render target to receive draw calls.
             */
            void SetViewport(Viewport& viewport);

        private:
            void ApplyChanges();

        private:
            DepthStencilState             depthStencilState;
            std::shared_ptr<Effect>       effect;
            GraphicsProfile               graphicsProfile;
            std::shared_ptr<IndexBuffer>  indexBuffer;
            PresentationParameters        presentationParameters;
            RasterizerState               rasterizerState;
            std::shared_ptr<VertexBuffer> vertexBuffer;
            Viewport                      viewport;

            friend class GraphicsDeviceManager;
        };
    }
}

#endif  /* GRAPHICSDEVICE_HPP */