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

#ifndef cl_dotcpp_main_Object_hpp
#define cl_dotcpp_main_Object_hpp

#include <cl/dotcpp/main/declare.hpp>
#include <cl/dotcpp/main/system/Ptr.hpp>
#include <cl/dotcpp/main/system/Exception.hpp>

namespace cl
{
    /// <summary>All classes with reference semantics should derive from this type.
    /// It works with Ptr to provide an emulation of reference semantics in C++.
    /// Classes with value semantics should not derive from this type.</summary>
    class CL_DOTCPP_MAIN Object
    {
    public:

        /// <summary>Virtual destructor to ensure that destructor
        /// of the derived type is called by Ptr.</summary>
        virtual ~Object() = default;

    public: // METHODS

        /// <summary>Returns a string that represents the current object.
        /// Default implementation uses full name of the class.</summary>
        virtual std::string ToString() const { return "Object"; }

    protected:
        Object() = default;
    };
}

#endif // cl_dotcpp_main_Object_hpp
