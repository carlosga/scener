// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_CONTENTLOADEXCEPTION_HPP
#define SCENER_CONTENT_CONTENTLOADEXCEPTION_HPP

#include <string>

namespace scener { namespace content {

/// Exception used to report errors from the ContentManager.Load method.
class ContentLoadException final : std::exception
{
public:
    /// Initializes a new instance of the ContentLoadException class with the given message.
    ///  \param message the exception message
    ContentLoadException(const std::string message = "content_manager Load Exception");

    /// Default destructor.
    ~ContentLoadException() noexcept override = default;

public:
    /// Gets the message that describes the error.
    /// \returns the message describing the error.
    const char* what() const noexcept override;

private:
    std::string msg;
};

}}

#endif  // SCENER_CONTENT_CONTENTLOADEXCEPTION_HPP
