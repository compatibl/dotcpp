﻿/*
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

#pragma once

#include <cl/dotcpp/main/system/Object.hpp>

namespace cl
{
    class TypeImpl; using Type = Ptr<TypeImpl>;
    class PropertyInfoImpl; using PropertyInfo = Ptr<PropertyInfoImpl>;
    class Array1DImpl; using Array1D = Ptr<Array1DImpl>;

    /// <summary>
    /// Provides reflection functionality.
    /// </summary>
    class CL_DOTCPP_MAIN TypeImpl : public virtual ObjectImpl
    {
    public: // METHODS

        /// <summary>Returns all the public properties of the current type.</summary>
        public Array1D<PropertyInfo> GetProperties();

        /// <summary>A string representing the name of the current type.</summary>
        virtual String ToString() const { return "Type"; } // TODO - return name

    protected:
        TypeImpl() = default;
    };
}
