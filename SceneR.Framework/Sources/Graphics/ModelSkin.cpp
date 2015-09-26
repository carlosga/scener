// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/ModelSkin.hpp>

#include <algorithm>

#include <Framework/Matrix.hpp>
#include <Graphics/ModelBone.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Matrix;

        const Matrix& ModelSkin::bindShapeMatrix() const noexcept
        {
            return _bindShapeMatrix;
        }

        const std::vector<Matrix>& ModelSkin::inverseBindMatrices() const noexcept
        {
            return _inverseBindMatrices;
        }

        const std::vector<std::shared_ptr<ModelBone>>& ModelSkin::joints() const noexcept
        {
            return _joints;
        }

        const std::string& ModelSkin::name() const noexcept
        {
            return _name;
        }

        const std::vector<std::shared_ptr<ModelBone>> &ModelSkin::skeletons() const noexcept
        {
            return _skeletons;
        }
    }
}
