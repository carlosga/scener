// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_EFFECT_PASS_HPP
#define SCENER_GRAPHICS_EFFECT_PASS_HPP

#include <memory>
#include <string>
#include <vector>

#include <gsl/gsl>

namespace scener::content::readers { template <typename T> class content_type_reader; }
namespace scener::graphics::opengl { class program; }

namespace scener::graphics
{
    class effect_parameter;
    class graphics_device;

    /// Contains rendering state for drawing with an effect; an effect can contain one or more passes.
    class effect_pass final
    {
    public:
        /// Initializes a new instance of the EffectPass class.
        /// \param device The GraphicsDevice associated with this EffectPass.
        effect_pass(gsl::not_null<graphics_device*> device) noexcept;

    public:
        /// Gets the name of this pass.
        /// \returns The name of this pass.
        const std::string& name() const noexcept;

        /// Begins this pass.
        void begin() noexcept;

        /// Ends this pass.
        void end() noexcept;

    private:
        graphics_device*                               _graphics_device  { nullptr };
        std::vector<std::shared_ptr<effect_parameter>> _parameters       { };
        std::shared_ptr<opengl::program>               _program          { nullptr };
        std::string                                    _name             { };

        template <typename T> friend class scener::content::readers::content_type_reader;
    };
}

#endif // SCENER_GRAPHICS_EFFECT_PASS_HPP
