// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_MODEL_HPP
#define GRAPHICS_MODEL_HPP

#include <memory>
#include <string>
#include <vector>

#include <Framework/RenderTime.hpp>

#include <System/IDisposable.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;
    }

    namespace Framework
    {
        struct Matrix;
    }

    namespace Graphics
    {
        class ModelMesh;

        /**
         * Represents a 3D model composed of multiple ModelMesh objects which may be moved independently.
         */
        class Model final : System::IDisposable
        {
        public:
            /**
             * Initializes a new instance of the Model class.
             */
            Model() noexcept;

            /**
             * Releases all resources being used by this Model.
             */
            ~Model() = default;

        public:
            void dispose() override;

        public:
            /**
             * Gets the model name.
             * @return the model name.
             */
            const std::string name() const noexcept;

            /**
             * Gets a collection of ModelMesh objects which composes the current model.
             */
            const std::vector<std::shared_ptr<ModelMesh>>& meshes() const noexcept;

            /**
             * Advances the animation by given time and updates the model
             * skin accordingly.
             * @param renderTime elapsed time
             */
            void update(const SceneR::Framework::RenderTime& renderTime) noexcept;

            /**
             * Render a model after applying the given matrix transformations.
             *
             * @param world the world matrix
             * @param view the view matrix
             * @param projection the projection matrix
             */
            void draw(const SceneR::Framework::Matrix& world
                    , const SceneR::Framework::Matrix& view
                    , const SceneR::Framework::Matrix& projection) noexcept;

        private:
            std::string                             _name;
            std::vector<std::shared_ptr<ModelMesh>> _meshes;

            friend class SceneR::Content::ContentReader;
        };
    }
}

#endif  // GRAPHICS_MODEL_HPP
