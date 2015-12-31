// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_IDISPOSABLE_HPP
#define SCENER_IDISPOSABLE_HPP

namespace SceneR {

/**
 * @brief Provides a mechanism for releasing resources.
 */
class IDisposable
{
public:
    /**
     * Destructor
     */
    virtual ~IDisposable() = default;

public:
    /**
     * @brief Performs application-defined tasks associated with freeing, releasing,
     *        or resetting resources.
     */
    virtual void dispose() = 0;
};

}

#endif // SCENER_IDISPOSABLE_HPP
