// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/AnimationReader.hpp"

#include <json11.hpp>

#include "scener/TimeSpan.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"
#include "scener/graphics/Animation.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;
using scener::time_span;
using scener::graphics::Animation;
using scener::graphics::Keyframe;
using scener::math::matrix4;
using scener::math::quaternion;
using scener::math::vector3;

auto ContentTypeReader<Animation>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto animation  = std::make_shared<Animation>();
    auto parameters = std::map<std::string, std::shared_ptr<gltf::accessor>>();

    for (const auto& p : source["parameters"].object_items())
    {
        auto accessor = input->read_object<gltf::accessor>(p.second.string_value());

        parameters[p.first] = accessor;
    }

    Ensures(parameters.count("TIME") == 1);

    const auto& keyframes = parameters["TIME"];
    const auto  count     = keyframes->attribute_count();
    auto        target    = input->read_object<gltf::node>(source["channels"][0]["target"]["id"].string_value());

    animation->_name = key;

    // Process only bone animations
    Ensures(target && target->joint);

    animation->_keyframes.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
    {
        quaternion rotation    = quaternion::identity();
        vector3    scale       = vector3::one();
        vector3    translation = vector3::zero();

        for (const auto& channel : source["channels"].array_items())
        {
            const auto& path     = channel["target"]["path"].string_value();
            const auto& accessor = parameters[path];

            if (path == "scale")
            {
                scale = accessor->get_element<vector3>(i);
            }
            else if (path == "translation")
            {
                translation = accessor->get_element<vector3>(i);
            }
            else if (path == "rotation")
            {
                rotation = accessor->get_element<quaternion>(i);
            }
        }

        auto time      = time_span::from_seconds(keyframes->get_element<float>(i));
        auto transform = scener::math::matrix::create_scale(scale)
                       * scener::math::matrix::create_from_quaternion(rotation)
                       * scener::math::matrix::create_translation(translation);

        animation->_keyframes.push_back({ time, transform });
    }

    animation->_duration = animation->_keyframes.crbegin()->time();

    target->joint->_animation = animation;

    return animation;
}

}}}

