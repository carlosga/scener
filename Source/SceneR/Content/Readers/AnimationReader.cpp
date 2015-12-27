// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "AnimationReader.hpp"

#include <json11.hpp>

#include "Accessor.hpp"
#include "Node.hpp"
#include "../ContentReader.hpp"
#include "../../Core/TimeSpan.hpp"
#include "../../Math/Matrix.hpp"
#include "../../Math/Quaternion.hpp"
#include "../../Math/Vector3.hpp"
#include "../../Math/Vector4.hpp"
#include "../../Graphics/Keyframe.hpp"

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::TimeSpan;
        using SceneR::Math::Matrix;
        using SceneR::Math::Quaternion;
        using SceneR::Math::Vector3;
        using SceneR::Math::Vector4;
        using SceneR::Content::Accessor;
        using SceneR::Content::Node;
        using SceneR::Graphics::Animation;
        using SceneR::Graphics::Keyframe;

        std::shared_ptr<Animation> ContentTypeReader<Animation>::read(gsl::not_null<ContentReader*>       input
                                                                    , const std::pair<std::string, Json>& source) const
        {
            auto animation  = std::make_shared<Animation>();
            auto parameters = std::map<std::string, std::shared_ptr<Accessor>>();

            for (const auto& p : source.second["parameters"].object_items())
            {
                auto ref      = p.second.string_value();
                auto accessor = input->read_object<Accessor>(ref);

                parameters[p.first] = accessor;
            }

            Ensures(parameters.count("TIME") == 1);

            auto keyframes = parameters["TIME"];
            auto targetRef = source.second["channels"][0]["target"]["id"].string_value();
            auto target    = input->read_object<Node>(targetRef);
            auto count     = keyframes->attribute_count();

            animation->_name = source.first;

            // Process only bone animations
            Ensures(target && target->joint);

            for (std::size_t i = 0; i < count; i++)
            {
                Quaternion rotation    = Quaternion::identity;
                Vector3    scale       = Vector3::one;
                Vector3    translation = Vector3::zero;

                for (const auto& channel : source.second["channels"].array_items())
                {
                    auto path     = channel["target"]["path"].string_value();
                    auto accessor = parameters[path];

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

            target->joint->_animation = animation;

            return animation;
        }
    }
}

