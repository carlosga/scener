// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VIEWPORT_HPP
#define SCENER_GRAPHICS_VIEWPORT_HPP

namespace SceneR { namespace Graphics {

/**
 * Represents the portion of the render target to receive draw calls.
 */
class Viewport
{
public:
    /**
     * Initializes a new instance of the ViewPort class
     */
    Viewport() noexcept;

    /**
     * Initializes a new instance of the ViewPort class
     */
    Viewport(float x, float y, float width, float height) noexcept;

    /**
     * Initializes a new instance of the ViewPort class
     */
    Viewport(float x, float y, float width, float height, float minDepth, float maxDepth) noexcept;

    /**
     * @brief Copy constructor
     * @param viewport the instance to copy from
     */
    Viewport(const Viewport& viewport) = default;

    /**
     * destructor
     */
    ~Viewport() = default;

public:
    float aspect_ratio() const noexcept;

    void update() const;

public:
    Viewport& operator=(const Viewport& viewport) = default;

public:
    float x;
    float y;
    float width;
    float height;
    float min_depth;
    float max_depth;
};

}}

#endif // SCENER_GRAPHICS_VIEWPORT_HPP
