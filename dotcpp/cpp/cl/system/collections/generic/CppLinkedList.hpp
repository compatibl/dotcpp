/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++ project, an open source implementation of
selected .NET class library APIs in native C++ with optional support
for adjoint algorithmic differentiation (AAD), available from

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

#ifndef __cl_system_collections_generic_LinkedList_hpp__
#define __cl_system_collections_generic_LinkedList_hpp__

#include <deque>

#include <cl/system/collections/generic/ICppCollection.hpp>
#include <cl/system/collections/generic/ICppEnumerable.hpp>
#include <cl/system/collections/generic/ICppEnumerator.hpp>

namespace cl
{
    ///!!! Not finished
    template <typename T>
    class CppLinkedListNode
    {
    private:

    public:
        CppLinkedListNode(T Value);
    };

    ///!!! Not finished
    template <typename T>
    class CppLinkedList : public detail::std_accessor_<cl::ICppEnumerable<T>
        , std::deque<T> >
    {
    public:
        typedef detail::std_accessor_<cl::ICppEnumerable<T>
            , std::deque<T> > base;
        typedef cl::ICppEnumerable<T> cl_enumerator_type;
        typedef std::deque<T> std_base;
        typedef T& reference_type;

        CppLinkedList() : base()
        {}

        inline int get_Count() const
        {
            return this->get().size();
        }
    };
}

#endif