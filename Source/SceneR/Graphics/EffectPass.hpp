// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_EFFECTPASS_HPP
#define SCENER_GRAPHICS_EFFECTPASS_HPP

#include <memory>
#include <string>
#include <vector>

#include <gsl.h>

namespace SceneR { namespace Content { namespace Readers { template <typename T> class ContentTypeReader; } } }

namespace SceneR { namespace Graphics { namespace OpenGL { class Program; } } }

namespace SceneR { namespace Graphics {

class EffectParameter;
class GraphicsDevice;

/// Contains rendering state for drawing with an effect; an effect can contain one or more passes.
class EffectPass final
{
public:
    /// Initializes a new instance of the EffectPass class.
    /// \param graphicsDevice The GraphicsDevice associated with this EffectPass.
    EffectPass(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept;

public:
    /// Gets the name of this pass.
    /// \returns The name of this pass.
    const std::string& name() const noexcept;

    /// Begins this pass.
    void begin() noexcept;

    /// Ends this pass.
    void end() noexcept;

private:
    GraphicsDevice*                               _graphics_device  { nullptr };
    std::vector<std::shared_ptr<EffectParameter>> _parameters       { };
    std::shared_ptr<OpenGL::Program>              _program          { nullptr };
    std::string                                   _name             { };

    template <typename T> friend class SceneR::Content::Readers::ContentTypeReader;
};

}}

#endif // SCENER_GRAPHICS_EFFECTPASS_HPP
