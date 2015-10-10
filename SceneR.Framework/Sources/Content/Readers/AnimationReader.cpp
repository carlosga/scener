// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/AnimationReader.hpp>

#include <json11.hpp>
#include <Content/ContentReader.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/Accessor.hpp>
#include <Graphics/Keyframe.hpp>
#include <Graphics/Node.hpp>
#include <System/BitConverter.hpp>
#include <System/TimeSpan.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Quaternion;
        using SceneR::Framework::Vector3;
        using SceneR::Graphics::Accessor;
        using SceneR::Graphics::Animation;
        using SceneR::Graphics::Keyframe;
        using SceneR::Graphics::Node;
        using System::BitConverter;
        using System::TimeSpan;

        std::shared_ptr<Animation> ContentTypeReader<Animation>::read(gsl::not_null<ContentReader*>       input
                                                                    , const std::pair<std::string, Json>& source) const
        {
            auto        animation  = std::make_shared<Animation>();
            std::size_t count      = source.second["count"].int_value();
            auto        parameters = std::map<std::string, std::shared_ptr<Accessor>>();

            for (const auto& p : source.second["parameters"].object_items())
            {
                auto ref      = p.second.string_value();
                auto accessor = input->read_object<Accessor>("accessors", ref);

                parameters[p.first] = accessor;
            }

            auto times = parameters["TIME"];

            animation->_name = source.first;

            auto targetRef = source.second["channels"][0]["target"]["id"].string_value();
            auto target    = input->read_object<Node>("nodes", targetRef);

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
                        auto vector = accessor->get_data(i, 1);

                        scale = { BitConverter::to_single(vector, 0)
                                , BitConverter::to_single(vector, 4)
                                , BitConverter::to_single(vector, 8)};
                    }
                    else if (path == "translation")
                    {
                        auto vector = accessor->get_data(i, 1);

                        translation = { BitConverter::to_single(vector, 0)
                                      , BitConverter::to_single(vector, 4)
                                      , BitConverter::to_single(vector, 8)};
                    }
                    else if (path == "rotation")
                    {
                        auto vector = accessor->get_data(i, 1);
                        auto axis   = Vector3::normalize({ BitConverter::to_single(vector, 0)
                                                         , BitConverter::to_single(vector, 4)
                                                         , BitConverter::to_single(vector, 8) });

                        rotation = Quaternion::create_from_axis_angle(axis, BitConverter::to_single(vector, 12));
                    }
                }

                auto time      = TimeSpan::from_seconds(BitConverter::to_single(times->get_data(i, 1)));
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

