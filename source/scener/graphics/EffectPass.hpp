// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_EFFECTPASS_HPP
#define SCENER_GRAPHICS_EFFECTPASS_HPP

#include <memory>
#include <string>
#include <vector>

#include <gsl.h>

namespace scener { namespace content { namespace readers { template <typename T> class ContentTypeReader; } } }

namespace scener { namespace graphics { namespace opengl { class Program; } } }

namespace scener { namespace graphics {

class effect_parameter;
class graphics_device;

/// Contains rendering state for drawing with an effect; an effect can contain one or more passes.
class effect_pass final
{
public:
    /// Initializes a new instance of the EffectPass class.
    /// \param graphicsDevice The GraphicsDevice associated with this EffectPass.
    effect_pass(gsl::not_null<graphics_device*> graphicsDevice) noexcept;

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
    std::shared_ptr<opengl::Program>              _program          { nullptr };
    std::string                                   _name             { };

    template <typename T> friend class scener::content::readers::ContentTypeReader;
};

}}

#endif // SCENER_GRAPHICS_EFFECTPASS_HPP
