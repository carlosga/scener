// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TECHNIQUESREADER_HPP
#define TECHNIQUESREADER_HPP

#include <memory>

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class Technique;
        class TechniquePass;
    }
}

namespace SceneR
{
    namespace Content
    {
        /**
         * Techniques reader
         */
        class TechniquesReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the TechniquesReader class.
             */
            TechniquesReader();

            /**
             * Destructor
             */
            ~TechniquesReader();

        public:
            /**
             * Reads the buffers contents from the given ContentReader.
             */
            void Read(const json11::Json& value, SceneR::GLTF::Model* root) override;

        private:
            void ReadTechniqueParameters(const json11::Json& value, std::shared_ptr<SceneR::GLTF::Technique> technique);

            void ReadTechniquePasses(const json11::Json& value, std::shared_ptr<SceneR::GLTF::Technique> technique);

            void ReadTechniquePassStates(const json11::Json& value, std::shared_ptr<SceneR::GLTF::TechniquePass> pass);
        };
    }
}

#endif //TECHNIQUESREADER_HPP
