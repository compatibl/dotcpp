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

#pragma once

#include <cl/dotcpp/main/system/Ptr.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerator.hpp>

#include <deque>

namespace cl
{
    template <class T> class IEnumerableImpl; template <class T> using IEnumerable = Ptr<IEnumerableImpl<T>>;
    template <class T> class IEnumeratorImpl; template <class T> using IEnumerator = Ptr<IEnumeratorImpl<T>>;

    /// <summary>
    /// Exposes the enumerator, which supports a simple iteration over a collection of a specified type.
    /// </summary>
    template <typename T>
    class IEnumerableImpl : public virtual ObjectImpl
    {
    public: // METHODS

        /// <summary>Returns an enumerator that iterates through the collection.</summary>
        virtual IEnumerator<T> GetEnumerator() = 0;
    };
}
