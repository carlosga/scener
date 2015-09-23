// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/ModelBone.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Matrix;

        const std::vector<std::shared_ptr<ModelBone>>& ModelBone::children() const
        {
            return _children;
        }

        const std::string &ModelBone::name() const
        {
            return _name;
        }

        const std::shared_ptr<ModelBone>& ModelBone::parent() const
        {
            return _parent;
        }

        const Matrix& ModelBone::transform() const
        {
            return _transform;
        }

        void ModelBone::transform(const Matrix& transform)
        {
            _transform = transform;
        }
    }
}
