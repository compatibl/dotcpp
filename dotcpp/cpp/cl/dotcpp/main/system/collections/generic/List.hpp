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

#include <cl/dotcpp/main/system/collections/generic/IList.hpp>

#include <deque>

namespace cl
{
    template <class T> class ListImpl; template <class T> using List = Ptr<ListImpl<T>>;

    /// <summary>
    /// Represents a strongly typed list of objects that can be accessed by index.
    /// Provides methods to search, sort, and manipulate lists.
    /// </summary>
    template <typename T>
    class ListImpl : public IListImpl<T>, public std::vector<T>
    {
        typedef std::vector<T> base;

        template <typename T>
        friend List<T> new_List();

    private: // CONSTRUCTORS

        /// <summary>
        /// Initializes a new instance of the list that is empty and has the default initial capacity.
        ///
        /// This constructor is private. Use new_List() function instead.
        /// </summary>
        ListImpl() {}

    public: // METHODS

        /// <summary>Returns an enumerator that iterates through the collection.</summary>
        virtual IEnumerator<T> GetEnumerator() { return nullptr; } // TODO - implement

        /// <summary>The number of items contained in the list.</summary>
        virtual int getCount() { return this->size(); }

        /// <summary>The total number of elements the internal data structure can hold without resizing.</summary>
        PROPERTY(ListImpl, int, Capacity, { return this->capacity(); }, { this->reserve(value); });

        /// <summary>Adds an object to the end of the list.</summary>
        virtual void Add(const T& item) { this->push_back(item); }

        /// <summary>Adds the elements of the specified collection to the end of the list.</summary>
        // TODO void AddRange(const IEnumerable<T>& collection);

        /// <summary>Removes all elements from the list.</summary>
        virtual void Clear() { this->clear(); }

        /// <summary>Determines whether an element is in the list.</summary>
        virtual bool Contains(const T& item) { return false; } // TODO - implement

    public: // OPERATORS

        /// <summary>Gets or sets the element at the specified index (const version).</summary>
        virtual const T& operator[](int i) const { return base::operator[](i); }

        /// <summary>Gets or sets the element at the specified index (non-const version).</summary>
        virtual T& operator[](int i) { return base::operator[](i); }

        /*

        /// <summary>Copies list elements to array starting at then begining of arrray.</summary>
        void copyTo(Array<T>& arr) const;

        /// <summary>Copies List elements to array starting at specified index.</summary>
        void copyTo(Array<T>& arr, int index) const;

        /// <summary>Copies range of List elements to array starting at specified index.</summary>
        void copyTo(int index, Array<T>& arr, int arrIndex, int count) const;

        /// <summary>Looks for element in List that matches predicate condition and returns its index.</summary>
        template <typename Predicate>
        inline int findLastIndex(Predicate match) const
        {
            return std::distance(this->begin(), std::find_if(this->rbegin(), this->rend(), match).base() - 1);
        }

        /// <summary>Looks for element in List starting at specified index that match predicate condition and returns it index in List.</summary>
        template <typename Predicate>
        inline int findLastIndex(int startIndex, Predicate match) const;

        /// <summary>Looks for element in ranghe of elements in List that match predicate condition and returns it index in List.</summary>
        template <typename Predicate>
        inline int findLastIndex(int startIndex, int count, Predicate match) const;

        /// <summary>Returns element in List that matches predicate condition.</summary>
        template <typename Predicate>
        inline T const & findLast(Predicate match) const
        {
            return *std::find_if(this->rbegin(), this->rend(), match);
        }

        /// <summary>Returns element in List that matches predicate condition.</summary>
        template <typename Predicate>
        inline T& findLast(Predicate match)
        {
            return *std::find_if(this->rbegin(), this->rend(), match);
        }

        /// <summary>Apples action to each element in List.</summary>
        template <typename TAction>
        inline void forEach(TAction action)
        {
            std::for_each(this->begin(), this->end(), action);
        }

        /// <summary>Returns a sublist.</summary>
        List<T> getRange(int index, int count) const;

        /// <summary>Searches for the specified object and returns the index of the first entire in List.</summary>
        int IndexOf(const T& item) const;

        /// <summary>Searches for the specified object and returns index of the first occurrence in List.</summary>
        int indexOf(const T& item, int index) const;

        /// <summary>Searches for the specified object and returns index of the first occurrence in List.</summary>
        int indexOf(const T& item, int index, int count) const;

        /// <summary>Inserts an element into List<T> at the specified index.</summary>
        void insert(int index, T item);

        /// <summary>Inserts the elements of a collection into List at the specified index.</summary>
        void insertRange(int index, IEnumerable<T> const& collection);

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
            std::remove_if(this->begin(), this->end(), match);
            return sizeold - this->get().size();
        }

        /// <summary>Removes the element at the specified index of the List.</summary>
        void removeAt(int index)
        {
            assert(this->get().size() > index);
            this->get().erase(this->begin() + index);
        }

        /// <summary>Removes a range of elements from the List.</summary>
        void removeRange(int index, int count);

        /// <summary>Reverses the order of the elements in the List.</summary>
        void reverse();

        /// <summary>Reverses the order of the elements in the specified range.</summary>
        void reverse(int index, int count);

        /// <summary>Sorts the elements in the list using the default comparer.</summary>
        void Sort();

        /// <summary>Sorts the elements in a range of elements in List using the specified comparer.</summary>
        template <typename Comparer>
        void sort(int index, int count, Comparer comparer)
        {
            std::sort(this->begin() + index, this->begin() + index + count, comparer);
        }

        /// <summary>Copies list elements to an array.</summary>
        Array<T> ToArray() const;

        */
    };

    /// <summary>
    /// Initializes a new instance of the list that is empty and has the default initial capacity.
    ///
    /// This constructor is private. Use new_List() function instead.
    /// </summary>
    template <typename T>
    List<T> new_List() { return new ListImpl<T>(); }

}

namespace std
{
    template <typename T>
    auto begin(cl::List<T> & list)
    {
        return list->begin();
    }

    template <typename T>
    auto end(cl::List<T> & list)
    {
        return list->end();
    }

}