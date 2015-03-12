﻿/*
Copyright (C) 2003-2015 CompatibL

This file is part of DotCpp project, an implementation of
selected .NET class libraries in native C++ available from

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

#ifndef __dot_system_DotStringSplitOptions_hpp__
#define __dot_system_DotStringSplitOptions_hpp__

#include <dot/system/declare.hpp>

namespace dot
{
    /// <summary>Specifies whether applicable DotString.split(...) method overloads
    /// include or omit empty substrings from the return value.</summary>
    enum class DOT_SYSTEM DotStringSplitOptions : int
    {
        /// <summary>The return value includes array elements that contain an empty string.</summary>
        None,

        /// <summary>The return value does not include array elements that contain an empty string.</summary>
        RemoveEmptyEntries
    };
}

#endif  // __dot_system_DotStringSplitOptions_hpp__
