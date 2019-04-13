/*
Copyright (C) 2003-present CompatibL

This file is part of .C++, a native C++ implementation of
popular .NET class library APIs developed to facilitate
code reuse between C# and C++.

    http://github.com/dotcpp/dotcpp (source)
    http://dotcpp.org (documentation)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


#include <cl/dotcpp/main/implement.hpp>
#include <cl/dotcpp/main/system/Type.hpp>
#include <cl/dotcpp/main/system/ObjectImpl.hpp>
#include <cl/dotcpp/main/system/reflection/PropertyInfo.hpp>
#include <cl/dotcpp/main/system/reflection/MethodInfo.hpp>
#include <cl/dotcpp/main/system/reflection/ConstructorInfo.hpp>
#include <cl/dotcpp/main/system/Array1D.hpp>
#include <cl/dotcpp/main/system/collections/generic/List.hpp>
#include <cl/dotcpp/main/system/String.hpp>

namespace cl
{
    /// <summary>Built Type from the current object.</summary>
    Type TypeBuilderImpl::Build()
    {
        type_->Fill(this);
        return type_;
    }

    /// <summary>
    /// Fill data from builder.
    /// </summary>
    void TypeImpl::Fill(const TypeBuilder& data)
    {
        if (!data->properties_.IsEmpty())
        {
            this->properties_ = new_Array1D<PropertyInfo>(data->properties_->Count);
            int i = 0;
            for (PropertyInfo propInfoData : data->properties_)
            {
                this->properties_[i++] = propInfoData;
            }
        }

        if (!data->methods_.IsEmpty())
        {
            this->methods_ = new_Array1D<MethodInfo>(data->methods_->Count);
            int i = 0;
            for (MethodInfo methInfoData : data->methods_)
            {
                this->methods_[i++] = methInfoData;
            }
        }

        if (!data->ctors_.IsEmpty())
        {
            this->ctors_ = new_Array1D<ConstructorInfo>(data->ctors_->Count);
            int i = 0;
            for (ConstructorInfo ctorInfoData : data->ctors_)
            {
                this->ctors_[i++] = ctorInfoData;
            }
        }

        if (!data->interfaces_.IsEmpty())
        {
            this->interfaces_ = new_Array1D<Type>(data->interfaces_->Count);
            int i = 0;
            for (Type interface : data->interfaces_)
            {
                this->interfaces_[i++] = interface;
            }
        }

        if (!data->generic_args_.IsEmpty())
        {
            this->generic_args_ = new_Array1D<Type>(data->generic_args_->Count);
            int i = 0;
            for (Type arg : data->generic_args_)
            {
                this->generic_args_[i++] = arg;
            }
        }

        this->base_ = data->base_;
        this->IsClass.IsClass = data->is_class_;
    }

    /// <summary>
    /// Create from builder.
    ///
    /// This constructor is private. Use TypeBuilder->Build() method instead.
    /// </summary>
    TypeImpl::TypeImpl(String Name, String Namespace)
    {
        this->Name.Name = Name;
        this->Namespace.Namespace = Namespace;
    }


    TypeBuilderImpl::TypeBuilderImpl(String Name, String Namespace, String CppName)
        : fullName_(Name + Namespace)
    {
        type_ = new TypeImpl(Name, Namespace);
        TypeImpl::GetTypeMap()[fullName_] = type_;
        TypeImpl::GetTypeMap()[CppName] = type_;
    }

    PropertyInfo TypeImpl::GetProperty(String name)
    {
        if (properties_.IsEmpty()) return nullptr;

        for (auto prop : properties_)
        {
            if (prop->Name == name)
                return prop;
        }

        return nullptr;
    }

    MethodInfo TypeImpl::GetMethod(String name)
    {
        if (methods_.IsEmpty()) return nullptr;

        for (auto method : methods_)
        {
            if (method->Name == name)
                return method;
        }

        return nullptr;
    }

    Type TypeImpl::GetInterface(String name)
    {
        if (interfaces_.IsEmpty()) return nullptr;

        for (auto interface : interfaces_)
        {
            if (interface->Name == name)
                return interface;
        }

        return nullptr;
    }
}
