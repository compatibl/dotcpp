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

#ifndef __cl_system_collections_generic_CppList_hpp__
#define __cl_system_collections_generic_CppList_hpp__

#include <cl/system/collections/generic/ICppCollection.hpp>
#include <cl/system/collections/generic/ICppEnumerable.hpp>
#include <cl/system/collections/generic/ICppEnumerator.hpp>
#include <deque>

namespace cl
{
    template <typename T> class CppArray;

    typedef std::runtime_error Exception;

    template <typename Type>
    struct CppReadOnlyCollection : detail::empty_type {};

    template <typename >
    struct ICppComparer : detail::empty_type {};

    template <typename, typename >
    struct CppConverter : detail::empty_type {};

    template <typename >
    struct CppAction : detail::empty_type {};

    template <typename>
    struct CppComparison : detail::empty_type {};

    /// Adapter class from STL deque to .NET List with access by index
    template <typename T>
    class CppList : public detail::std_accessor_<cl::ICppEnumerable<T>, std::deque<T> >
    {
    public:

        //!! Why in public scope
        typedef cl::ICppEnumerator<T> Enumerator;
        typedef detail::std_accessor_<cl::ICppEnumerable<T>, std::deque<T> > base;
        typedef cl::ICppEnumerable<T> cl_enumerator_type;
        typedef std::deque<T> std_base;
        typedef T& reference_type;

    public:

        /// <summary>Creates new empty instance of List.</summary>
        CppList() : base()
        {
        }

        //!! Why public?
        int Capacity;// { get; set; }

        /// <summary>Gets number of elements in List.</summary>
        inline int getCount() const
        {
            return this->get().size();
        }

        /// <summary>Gets element reference by index.</summary>
        inline reference_type
        operator[](unsigned int index) { return *(begin() + index); }

        /// <summary>Adds the new element to the end of List.</summary>
        inline void add(T item)
        {
            this->get().push_back(item);
        }

        /// <summary>Adds the elements from other collection to the end of List.</summary>
        inline void addRange(const ICppEnumerable<T>& collection);

        /// <summary>Returns a read-only collection wrapper around List.</summary>
        inline readOnlyCollection<T> asReadOnly();

        /// <summary>Searches element in sorted List using default comparer.</summary>
        inline int binarySearch(const T& item);

        /// <summary>Searches element in sorted List using specified comparer.</summary>
        inline int binarySearch(const T& item, ICppComparer<T> comparer);

        /// <summary>Searches element in sorted List in specifien range using
        /// specified comparer and returns index of that element.</summary>
        int binarySearch(int index, int count, const T& item, ICppComparer<T> comparer);

        /// <summary>Erase all elements from List.</summary>
        void clear();

        /// <summary>Searches element in List.</summary>
        bool contains(const T& item);

        /// <summary>Converts elemetn of List from type T to type TOutput
        /// using converter.</summary>
        template <typename TOutput, typename Coverter>
        inline CppList<TOutput> convertAll(CppConverter<T, TOutput> converter);

        /// <summary>Copies List elements to array starting at then begining of arrray.</summary>
        void copyTo(CppArray<T>& arr) const;

        /// <summary>Copies List elements to array starting at specified index.</summary>
        void copyTo(CppArray<T>& arr, int index) const;

        /// <summary>Copies range of List elements to array starting at specified index.</summary>
        void copyTo(int index, CppArray<T>& arr, int arrIndex, int count) const;

        /// <summary>Looks for elements in List that match predicate condition and returns bool.</summary>
        template <typename Predicate>
        inline bool exists(Predicate match) const
        {
            return std::find_if(begin(), end(), match) != end();
        }

        /// <summary>Looks for elements in List that match predicate condition and returns element.</summary>
        template <typename Predicate>
        inline reference_type find(Predicate match) const;

        /// <summary>Looks for elements in List that match predicate condition and returns it in new List.</summary>
        template <typename Predicate>
        inline CppList<T> findAll(Predicate match) const
        {
            CppList<T> result;
            std::for_each(begin(), end(), [&result, &match](T& v)
                {
                    if (match(v))
                        result.push_back(v);
                }
            );
            return result;
        }

        /// <summary>Looks for element in List that match predicate condition and returns it index in List.</summary>
        template <typename Predicate>
        int findIndex(Predicate match) const;

        /// <summary>Looks for element in List starting at specified index that match predicate condition and returns it index in List.</summary>
        template <typename Predicate>
        inline int findIndex(int startIndex, Predicate match) const
        {
            typename std_base::const_iterator where
                = std::find_if(begin() + startIndex, end(), match);
            return where != end() ? where - begin : -1;
        }

        /// <summary>Looks for element in ranghe of elements in List that match predicate condition and returns it index in List.</summary>
        template <typename Predicate>
        inline int findIndex(int startIndex, int count, Predicate match)
        {
            typename std_base::const_iterator start = begin() + startIndex;
            typename std_base::const_iterator end = start + count;
            assert(end <= end());
            typename std_base::const_iterator where
                = std::find_if(start, end , match);
            return where != end ? where - begin : -1;
        }

        /// <summary>Looks for element in List that match predicate condition and returns it index in List.</summary>
        template <typename Predicate>
        inline reference_type findLast(Predicate match)
        {
            std_base::reverse_iterator where
                = std::find_if(get().rbegin(), get().rend(), match);
            if (where == get().rend())
            {
                return std::reference_wrapper<T>(*(T*)0);
            }
            return (*where);
        }

        /// <summary>Looks for element in List that match predicate condition and returns it index in List.</summary>
        template<typename Predicate>
        inline int findLastIndex(Predicate match) const
        {
            std_base::const_reverse_iterator where
                = std::find_if(get().rbegin(), get().rend(), match);
            if (where == get().rend())
                return -1;
            return this->get_Count() - (get().rbegin() - where);
        }

        /// <summary>Looks for element in List starting at specified index that match predicate condition and returns it index in List.</summary>
        template <typename Predicate>
        inline int findLastIndex(int startIndex, Predicate match) const;

        /// <summary>Looks for element in ranghe of elements in List that match predicate condition and returns it index in List.</summary>
        template <typename Predicate>
        inline int findLastIndex(int startIndex, int count, Predicate match) const;

        /// <summary>Apples action to each element in List.</summary>
        template <typename CppAction>
        inline void forEach(CppAction action)
        {
            std::for_each(begin(), end(), action);
        }

        /// <summary>Returns a sublist.</summary>
        CppList<T> getRange(int index, int count) const;

        /// <summary>Searches for the specified object and returns the index of the first entire in List.</summary>
        int indexOf(const T& item) const;

        /// <summary>Searches for the specified object and returns index of the first occurrence in List.</summary>
        int indexOf(const T& item, int index) const;

        /// <summary>Searches for the specified object and returns index of the first occurrence in List.</summary>
        int indexOf(const T& item, int index, int count) const;

        /// <summary>Inserts an element into List<T> at the specified index.</summary>
        void insert(int index, T item);

        /// <summary>Inserts the elements of a collection into List at the specified index.</summary>
        void insertRange(int index, ICppEnumerable<T> const& collection);

        /// <summary>Searches for the specified object and returns the index of the last occurrence in List.</summary>
        int lastIndexOf(const T& item);

        /// <summary>Searches for the specified object and returns the index of the last occurrence in List.</summary>
        int lastIndexOf(const T& item, int index);

        /// <summary>Searches for the specified object and returns the index of the last occurrence in List.</summary>
        int lastIndexOf(const T& item, int index, int count);

        /// <summary>Removes the first occurrence of a specific object from the List.</summary>
        bool remove(const T& item);

        /// <summary>Removes all the elements that match the predicate conditions.</summary>
        template <typename Predicate>
        inline int removeAll(Predicate match)
        {
            unsigned int sizeold = this->get().size();
            std::remove_if(begin(), end(), match);
            return sizeold - this->get().size();
        }

        /// <summary>Removes the element at the specified index of the List.</summary>
        void removeAt(int index)
        {
            assert(this->get().size() > index);
            this->get().erase(begin() + index);
        }

        /// <summary>Removes a range of elements from the List.</summary>
        void removeRange(int index, int count);

        /// <summary>Reverses the order of the elements in the List.</summary>
        void reverse();

        /// <summary>Reverses the order of the elements in the specified range.</summary>
        void reverse(int index, int count);

        /// <summary>Sorts the elements in the List the default comparer.</summary>
        void sort();

        /// <summary>Sorts the elements in the List the specified comparsion.</summary>
        template <typename Comparer>
        void sort(CppComparison<T> comparison);

        /// <summary>Sorts the elements in the List the specified IComparer.</summary>
        template <typename Comparer>
        void sort(ICppComparer<T> comparer);

        /// <summary>Sorts the elements in a range of elements in List using the specified comparer.</summary>
        template <typename Comparer>
        void sort(int index, int count, Comparer comparer)
        {
            std::sort(begin() + index, begin() + index + count, comparer);
        }

        /// <summary>Copies the elements of the List to a new array.</summary>
        CppArray<T> toArray() const;

        /// <summary>Sets the capacity to the actual number of elements in the List,
        /// if that number is less than a threshold value.</summary>
        void trimExcess();

        /// <summary>Determines whether every element in the List matches
        /// the conditions defined by the specified predicate.</summary>
        template <typename Predicate>
        inline bool trueForAll(Predicate match);
    };
}

#endif // __cl_system_collections_generic_CppList_hpp__