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

#ifndef __dot_system_DotNull_hpp__
#define __dot_system_DotNull_hpp__

#include <dot/system/declare.hpp>

namespace dot
{
    /// <summary>Helper type to enable comparison and assignment to null pointer.
    /// This object cannot be created, therefore any pointer to DotNull is null.</summary>
    class DotNull
    {
    private:
        DotNull();
    };
}

#endif  // __dot_system_DotNull_hpp__
