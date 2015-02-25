#ifndef IDISPOSABLE_HPP
#define IDISPOSABLE_HPP

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
        virtual ~IDisposable();

    public:
        /**
         * @brief Performs application-defined tasks associated with freeing, releasing,
         *        or resetting unmanaged resources.
         */
        virtual void Dispose() = 0;
    };
}

#endif // IDISPOSABLE_HPP
