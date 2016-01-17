// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_CONTENTLOADEXCEPTION_HPP
#define SCENER_CONTENT_CONTENTLOADEXCEPTION_HPP

#include <string>

namespace SceneR { namespace Content {

/**
 * Exception used to report errors from the ContentManager.Load method.
 */
class ContentLoadException final : std::exception
{
public:
    /**
     * Initializes a new instance of the ContentLoadException class with the given message
     * @param m the exception message
     */
    ContentLoadException(const std::string m = "content_manager Load Exception");

    /**
     * @brief Copy constructor.
     * @param exception the exception to copy from.
     */
    ContentLoadException(const ContentLoadException& exception);

    /**
     * Destructor
     */
    ~ContentLoadException() noexcept override;

public:
    /**
     * Gets the message that describes the error.
     * @return  the message describing the error.
     */
    const char* what() const noexcept override;

public:
    ContentLoadException& operator=(const ContentLoadException& exception);

private:
    std::string msg;
};

}}

#endif  // SCENER_CONTENT_CONTENTLOADEXCEPTION_HPP
