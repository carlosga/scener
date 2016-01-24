// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/AnimationReader.hpp"

#include <json11.hpp>

#include "SceneR/TimeSpan.hpp"
#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Content/GLTF/Accessor.hpp"
#include "SceneR/Graphics/Animation.hpp"

namespace SceneR { namespace Content { namespace Readers {

using json11::Json;
using SceneR::TimeSpan;
using SceneR::Content::GLTF::Accessor;
using SceneR::Content::GLTF::Node;
using SceneR::Graphics::Animation;
using SceneR::Graphics::Keyframe;
using SceneR::Math::Matrix;
using SceneR::Math::Quaternion;
using SceneR::Math::Vector3;

auto ContentTypeReader<Animation>::read(ContentReader* input, const std::string& key, const Json& source) const noexcept
{
    auto animation  = std::make_shared<Animation>();
    auto parameters = std::map<std::string, std::shared_ptr<Accessor>>();

    for (const auto& p : source["parameters"].object_items())
    {
        auto accessor = input->read_object<Accessor>(p.second.string_value());

        parameters[p.first] = accessor;
    }

    Ensures(parameters.count("TIME") == 1);

    const auto& keyframes = parameters["TIME"];
    const auto  count     = keyframes->attribute_count();
    auto        target    = input->read_object<Node>(source["channels"][0]["target"]["id"].string_value());

    animation->_name = key;

    // Process only bone animations
    Ensures(target && target->joint);

    animation->_keyframes.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
    {
        Quaternion rotation    = Quaternion::identity;
        Vector3    scale       = Vector3::one;
        Vector3    translation = Vector3::zero;

        for (const auto& channel : source["channels"].array_items())
        {
            const auto& path     = channel["target"]["path"].string_value();
            const auto& accessor = parameters[path];

            if (path == "scale")
            {
                scale = accessor->get_element<Vector3>(i);
            }
            else if (path == "translation")
            {
                translation = accessor->get_element<Vector3>(i);
            }
            else if (path == "rotation")
            {
                rotation = accessor->get_element<Quaternion>(i);
            }
        }

        auto time      = TimeSpan::from_seconds(keyframes->get_element<float>(i));
        auto transform = Matrix::create_scale(scale)
                       * Matrix::create_from_quaternion(rotation)
                       * Matrix::create_translation(translation);

        animation->_keyframes.push_back({ time, transform });
    }

    animation->_duration = animation->_keyframes.crbegin()->time();

    target->joint->_animation = animation;

    return animation;
}

}}}

