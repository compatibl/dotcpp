/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, an open source implementation of TapeScript
in native C++ using .NET class library conventions, available from

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

#ifndef __cl_system_collections_generic_SortedSet_hpp__
#define __cl_system_collections_generic_SortedSet_hpp__

#include <set>

#include <cl/system/collections/generic/ICppCollection.hpp>
#include <cl/system/collections/generic/ICppEnumerable.hpp>
#include <cl/system/collections/generic/ICppEnumerator.hpp>

namespace cl
{
    template <typename T> class Array;

    ///!!! Provide .NET description Adapter class from STL set to .NET SortedSet
    template <typename T>
    class CppSortedSet : public detail::std_accessor_<cl::ICppEnumerable<T>, std::set<T> >
    {
    public:

        typedef detail::std_accessor_<cl::ICppEnumerable<T>, std::set<T> > base;
        typedef cl::ICppEnumerable<T> cl_enumerator_type;
        typedef std::set<T> std_base;

    public:

        /// <summary>Creates new empty instance of SortedSet.</summary>
        CppSortedSet() : base() {  }

        /// <summary>Gets number of elements in SortedList.</summary>
        inline int count() const
        {
            return this->get().size();
        }

        /// <summary>Gets the maximum value in SortedSet.</summary>
        inline T getMax() const;

        /// <summary>Gets the minimum value in SortedSet.</summary>
        inline T getMin() const;

        /// <summary>Adds the specified key and value to the SortedSet.</summary>
        inline bool add(const T& item);

        /// <summary>Removes all keys and values from the SortedSet.</summary>
        inline void clear();

        /// <summary>Searches element in SortedSet.</summary>
        inline bool contains(const T& item);

        /// <summary>Copies SortedSet elements to array starting at then begining of array.</summary>
        void copyTo(Array<T>& arr);

        /// <summary>Copies SortedSet elements to array starting at specified index.</summary>
        void copyTo(Array<T>& arr, int index);

        /// <summary>Copies a specified number of SortedSet elements to array starting at specified index.</summary>
        void copyTo(Array<T>& arr, int index, int count);

        /// <summary>Removes all elements in the specified collection from the current SortedSet object.</summary>
        inline void exceptWith(const ICppEnumerable<T>& other);

        /// <summary>Modifies the current SortedSet to contain only elements that
        /// are present in that object and in the specified collection.</summary>
        inline void intersectWith(const ICppEnumerable<T>& other);

        /// <summary>Determines whether a SortedSet object is a proper subset of the specified collection.</summary>
        inline bool isProperSubsetOf(const ICppEnumerable<T>& other);

        /// <summary>Determines whether a SortedSet is a proper superset of the specified collection.</summary>
        inline bool isProperSupersetOf(const ICppEnumerable<T>& other);

        /// <summary>Determines whether a HashSet is a subset of the specified collection.</summary>
        inline bool isSubsetOf(const ICppEnumerable<T>& other);

        /// <summary>Determines whether a SortedSet is a superset of the specified collection.</summary>
        inline bool isSupersetOf(const ICppEnumerable<T>& other);

        /// <summary>Determines whether the current SortedSet and a specified collection share common elements.</summary>
        inline bool overlaps(const ICppEnumerable<T>& other);

        /// <summary>Removes the first occurrence of a specific object from the SortedSet.</summary>
        inline bool remove(const T& item);

        /// <summary>Removes all the elements that match the predicate conditions.</summary>
        template <typename Predicate>
        inline int removeWhere(Predicate match);

        /// <summary>Returns an ICppEnumerable that iterates over the SortedSet in reverse order.</summary>
        inline ICppEnumerable<T>& reverse();

        /// <summary>Determines whether a SortedSet object and the specified collection contain the same elements.</summary>
        inline bool setEquals(const ICppEnumerable<T>& other) const;

        /// <summary>Modifies the current SortedSet to contain only elements that are present
        /// either in that object or in the specified collection, but not both.</summary>
        inline void symmetricExceptWith(const ICppEnumerable<T>& other);

        /// <summary>Modifies the current SortedSet to contain all elements
        /// that are present in itself and the specified collection.</summary>
        inline void unionWith(const ICppEnumerable<T>& other);
    };
}

#endif