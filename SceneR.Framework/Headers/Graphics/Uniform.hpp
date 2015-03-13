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
                  , const System::UInt32& offset
                  , const System::UInt32& type);

            Uniform(const Uniform& uniform);

            ~Uniform();

        public:
            const System::String& Name() const;

            System::UInt32 Index() const;

            System::Int32 Offset() const;

            const EffectParameterClass& ParameterClass() const;

            const EffectParameterType& ParameterType() const;

            System::UInt32 ColumnCount() const;

            System::UInt32 RowCount() const;

        public:
            Uniform& operator=(const Uniform& uniform);

        private:
            void Describe(const System::Int32& type);

        private:
            System::String       name;
            System::UInt32       index;
            System::UInt32       offset;
            System::UInt32       columnCount;
            System::UInt32       rowCount;
            EffectParameterClass parameterClass;
            EffectParameterType  parameterType;
        };
    }
}

#endif /* UNIFORM_HPP */
