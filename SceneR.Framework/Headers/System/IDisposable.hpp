#ifndef IDISPOSABLE_HPP
#define IDISPOSABLE_HPP

namespace System
{
    /**
     * @brief Provides a mechanism for releasing unmanaged resources.
     */
    class IDisposable
    {
    protected:
        /**
         * Releases all resources being used by this IDisposable.
         */
        virtual ~IDisposable() = default;

    public:
        /**
         * @brief Performs application-defined tasks associated with freeing, releasing,
         *        or resetting unmanaged resources.
         */
        virtual void Dispose() = 0;
    };
}

#endif // IDISPOSABLE_HPP
