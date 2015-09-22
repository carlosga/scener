// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SYSTEM_IDISPOSABLE_HPP
#define SYSTEM_IDISPOSABLE_HPP

namespace System
{
    /**
     * @brief Provides a mechanism for releasing unmanaged resources.
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
         *        or resetting unmanaged resources.
         */
        virtual void dispose() = 0;
    };
}

#endif // SYSTEM_IDISPOSABLE_HPP
