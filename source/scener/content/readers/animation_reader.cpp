// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/animation_reader.hpp"

#include "scener/timespan.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"
#include "scener/graphics/animation.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::timespan;
    using scener::graphics::keyframe;
    using scener::math::matrix4;
    using scener::math::quaternion;
    using scener::math::vector3;

    auto content_type_reader<graphics::animation>::read(content_reader* input, const std::string& key, const json& source) const noexcept
    {
        auto animation  = std::make_shared<graphics::animation>();
        auto parameters = std::map<std::string, std::shared_ptr<gltf::accessor>>();

        for (auto it = source["parameters"].begin(); it != source["parameters"].end(); ++it)
        {
            auto accessor = input->read_object<gltf::accessor>(it.value().get<std::string>());

            parameters[it.key()] = accessor;
        }

        Ensures(parameters.count("TIME") == 1);

        const auto& keyframes = parameters["TIME"];
        const auto  count     = keyframes->attribute_count();
        auto        target    = input->read_object<gltf::node>(source["channels"][0]["target"]["id"].get<std::string>());

        animation->_name = key;

        // Process only bone animations
        Ensures(target && target->joint);

        animation->_keyframes.reserve(count);

        for (std::size_t i = 0; i < count; ++i)
        {
            quaternion rotation    = quaternion::identity();
            vector3    scale       = vector3::one();
            vector3    translation = vector3::zero();

            for (const auto& channel : source["channels"].get<json::array_t>())
            {
                const auto& path     = channel["target"]["path"].get<std::string>();
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

            auto time      = timespan::from_seconds(keyframes->get_element<float>(i));
            auto transform = scener::math::matrix::create_scale(scale)
                           * scener::math::matrix::create_from_quaternion(rotation)
                           * scener::math::matrix::create_translation(translation);

            animation->_keyframes.push_back({ time, transform });
        }

        animation->_duration      = animation->_keyframes.crbegin()->time();
        target->joint->_animation = animation;

        return animation;
    }
}

