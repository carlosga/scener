// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/animation_reader.hpp"

#include "scener/timespan.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"
#include "scener/content/gltf/constants.hpp"

#include "scener/graphics/animation.hpp"

namespace scener::content::readers
{
    using nlohmann::json;    
    using scener::timespan;
    using scener::graphics::animation;
    using scener::graphics::keyframe;
    using scener::math::matrix4;
    using scener::math::quaternion;
    using scener::math::vector3;

    using namespace scener::content::gltf;

    auto content_type_reader<animation>::read(content_reader* input, const std::string& key, const json& value) const noexcept
    {
        auto instance   = std::make_shared<animation>();
        auto parameters = std::map<std::string, std::shared_ptr<accessor>>();

        for (auto it = value[k_parameters].begin(); it != value[k_parameters].end(); ++it)
        {
            parameters[it.key()] = input->read_object<accessor>(it.value().get<std::string>());;
        }

        Ensures(parameters.count(k_time) == 1);

        const auto& keyframes = parameters[k_time];
        const auto  count     = keyframes->attribute_count();
        auto        target    = input->read_object<gltf::node>(value[k_channels][0][k_target][k_id].get<std::string>());

        instance->_name = key;

        // Process only bone animations
        Ensures(target && target->joint);

        instance->_keyframes.reserve(count);

        for (std::size_t i = 0; i < count; ++i)
        {
            quaternion rotation    = quaternion::identity();
            vector3    scale       = vector3::one();
            vector3    translation = vector3::zero();

            for (const auto& channel : value[k_channels].get<json::array_t>())
            {
                const auto& path     = channel[k_target][k_path].get<std::string>();
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

            instance->_keyframes.push_back({ time, transform });
        }

        instance->_duration       = instance->_keyframes.crbegin()->time();
        target->joint->_animation = instance;

        return instance;
    }
}

