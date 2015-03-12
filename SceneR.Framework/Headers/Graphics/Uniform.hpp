#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include <System/Core.hpp>
#include <Graphics/EffectParameterType.hpp>
#include <Graphics/EffectParameterClass.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class Uniform final
        {
        public:
            Uniform();

            Uniform(const System::String& name
                  , const System::UInt32& index
                  , const System::Int32&  offset
                  , const System::Int32&  type
                  , const System::Int32&  arraySize
                  , const System::Int32&  arrayStride
                  , const System::Int32&  matrixStride
                  , const System::Int32&  matrixIsRowMajor);

            ~Uniform();

        public:
            const System::String& Name() const;

            System::UInt32 Index() const;

            System::Int32 Offset() const;

            const EffectParameterClass& ParameterClass() const;

            const EffectParameterType& ParameterType() const;

            System::Int32 ArraySize() const;

            System::Int32 ArrayStride() const;

            System::Int32 MatrixStride() const;

            System::Int32 MatrixIsRowMajor() const;

        private:
            void Describe(const System::Int32& type);

        private:
            System::String       name;
            System::UInt32       index;
            System::Int32        offset;
            EffectParameterClass parameterClass;
            EffectParameterType  parameterType;
            System::Int32        arraySize;
            System::Int32        arrayStride;
            System::Int32        matrixStride;
            System::Int32        matrixIsRowMajor;
        };
    }
}

#endif /* UNIFORM_HPP */
