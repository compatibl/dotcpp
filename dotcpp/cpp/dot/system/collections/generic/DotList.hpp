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

#ifndef __dot_DotList_hpp__
#define __dot_DotList_hpp__

#include <dot/system/collections/generic/IDotCollection.hpp>
#include <dot/system/collections/generic/IDotEnumerable.hpp>
#include <dot/system/collections/generic/IDotEnumerator.hpp>

namespace dot
{
    namespace detail { struct empty_type{}; }

    template <typename Type>
    struct ReadOnlyCollection : detail::empty_type {};

    template <typename >
    struct IComparer : detail::empty_type {};

    template <typename, typename >
    struct Converter : detail::empty_type {};

    template <typename >
    struct Predicate : detail::empty_type {};

    template <typename >
    struct Action : detail::empty_type { };

    template <typename>
    struct Comparison : detail::empty_type  {};

    template <typename T>
    class List : public dot::IDotEnumerable<T>
    {
    private:
        inline std::list<T>& get_()
        {
            //!! Avoid using ASSERT directly
#if defined DEBUG && defined ASSERT
            ASSERT(dynamic_cast<std_accessor<std::list<T> >*>(accessor_.get()));
#endif
            return static_cast<std_accessor<std::list<T> >*>(accessor_.get())->c_;
        }
    public:
        typedef dot::IDotEnumerable<T> base;

        List() : base(std::list<T>())
        {}

        int Capacity; // { get; set; }

        int get_Count()
        {
            return this->get_().size();
        }

        T& operator[](unsigned int) {}

        void Add(T const& item)
        {
            this->get_().push_back(item);
        }

        void AddRange(IDotEnumerable<T> const& collection);
        ReadOnlyCollection<T> AsReadOnly();
        int BinarySearch(T item);
        int BinarySearch(T item, IComparer<T> comparer);
        int BinarySearch(int index, int count, T item, IComparer<T> comparer);
        void Clear();
        bool Contains(T item);

        template <typename TOutput>
        inline List<TOutput> ConvertAll(Converter<T, TOutput> converter);

        template <int I>
        void CopyTo(T(&a)[I]);
        void CopyTo(T*& array, int arrayIndex);

        void CopyTo(int index, T*& array, int arrayIndex, int count);

        bool Exists(Predicate<T> match);

        List<T> FindAll(Predicate<T> match);

        int FindIndex(int startIndex, Predicate<T> match);

        int FindIndex(int startIndex, int count, Predicate<T> match);

        T FindLast(Predicate<T> match);

        int FindLastIndex(Predicate<T> match);

        int FindLastIndex(int startIndex, Predicate<T> match);

        int FindLastIndex(int startIndex, int count, Predicate<T> match);

        void ForEach(Action<T> action);

        typedef dot::IDotEnumerator<T> Enumerator;

        List<T> GetRange(int index, int count);

        int IndexOf(T item);

        int IndexOf(T item, int index);

        int IndexOf(T item, int index, int count);

        void Insert(int index, T item);

        void InsertRange(int index, IDotEnumerable<T> const& collection);

        int LastIndexOf(T item);

        int LastIndexOf(T item, int index);

        int LastIndexOf(T item, int index, int count);

        bool Remove(T item);

        int RemoveAll(Predicate<T> match);

        void RemoveAt(int index);

        void RemoveRange(int index, int count);

        void Reverse();

        //     System.Collections.Generic.List<T>.
        void Reverse(int index, int count);

        void Sort();

        void Sort(Comparison<T> comparison);

        void Sort(IComparer<T> comparer);

        void Sort(int index, int count, IComparer<T> comparer);

        //!! Should be dot::Array<T>
        std::vector<T> ToArray();

        void TrimExcess();

        bool TrueForAll(Predicate<T> match);
    };

    template <typename T>
    class Array : public dot::IDotEnumerable<T>
    {
    public:
        typedef dot::IDotEnumerable<T> base;
        Array() : base(std::vector<T>())
        {}
    };
}

#endif // __dot_DotList_hpp__