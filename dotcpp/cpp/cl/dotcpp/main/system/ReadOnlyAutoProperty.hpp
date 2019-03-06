/*
Copyright (C) 2003-present CompatibL

This file is part of .C++, a native C++ implementation of
popular .NET class library APIs developed to faciliate
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

#pragma once

#include <cl/dotcpp/main/declare.hpp>

namespace cl
{
    /// <summary>Use this class to implement readonly auto property.</summary>
    template <typename T>
    class ReadOnlyAutoProperty
    {
        T& addr_;

    public: // CONSTRUCTORS

        /// <summary>Create from the local variable address.</summary>
        ReadOnlyAutoProperty(T& addr) : addr_(addr) {}

    public: // OPERATORS

        /// <summary>Provides property get behavior.</summary>
        operator T() const { return addr_; }

    private: // OPERATORS

        /// <summary>Private assignment operator prohibits property set behavior.</summary>
        void operator=(const ReadOnlyAutoProperty<T>&);
    };
}
