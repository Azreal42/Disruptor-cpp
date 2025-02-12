#pragma once

#include <string>
#include <typeinfo>


namespace Disruptor
{

    struct TypeInfo
    {
        explicit TypeInfo(const std::type_info& typeInfo);

        const std::type_info& intrinsicTypeInfo() const;

        const std::string& fullyQualifiedName() const;
        const std::string& name() const;

        bool operator==(const TypeInfo& rhs) const;

        static std::string dotNetify(std::string typeName);
        static std::string unqualifyName(std::string fullyQualifiedName);
        static std::string demangleTypeName(std::string typeName);

    private:
        const std::type_info* m_typeInfo;
        std::string m_fullyQualifiedName;
        std::string m_name;
    };

namespace Utils
{

    template <class T>
    const TypeInfo& getMetaTypeInfo()
    {
        static TypeInfo result(typeid(T));
        return result;
    }

} // namespace Utils
} // namespace Disruptor


#include <functional>
#include <typeindex>


namespace std
{

    template <>
    struct hash< Disruptor::TypeInfo >
    {
    public:
        typedef Disruptor::TypeInfo argument_type;
        typedef std::size_t result_type;

        size_t operator()(const Disruptor::TypeInfo& value) const
        {
            return hash< type_index >()(type_index(value.intrinsicTypeInfo()));
        }
    };

} // namespace std
