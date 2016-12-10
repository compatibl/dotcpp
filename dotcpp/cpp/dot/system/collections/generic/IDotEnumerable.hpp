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

#ifndef __dot_system_collections_generic_IDotEnumerable_hpp__
#define __dot_system_collections_generic_IDotEnumerable_hpp__

#include <vector>
#include <list>

#include <dot/system/declare.hpp>
#include <dot/system/collections/generic/IDotEnumerator.hpp>

namespace dot
{
    namespace detail 
    {
        struct empty_type{};
        struct null_type;

        /// We should get value type from collection type 
        template <typename Collection>
        struct is_collection {
            typedef null_type type;
            typedef null_type allocator_type;
        };

        template <typename ValueType, typename Allocator>
        struct is_collection <std::vector<ValueType, Allocator> > 
        {
            typedef ValueType type;
            typedef Allocator allocator_type;
        };

        template <typename ValueType, typename Allocator>
        struct is_collection <std::deque<ValueType, Allocator> >
        {
            typedef ValueType type;
            typedef Allocator allocator_type;
        };

        template <typename ValueType, typename Allocator>
        struct is_collection <std::list<ValueType, typename Allocator> >
        {
            typedef ValueType type;
            typedef Allocator allocator_type;
        };

        template <typename Key, typename ValueType, typename Pred, typename Allocator>
        struct is_collection <std::map<Key, ValueType, Pred, Allocator> >
        {
            typedef std::pair<Key, ValueType> type;
            typedef Allocator allocator_type;
        };

        // The holder remover 
        template <typename Type>
        struct remove_holder 
        {
            typedef Type type;
            enum { value = 0 };
        };

        template <template <typename > class Holder, typename Type>
        struct remove_holder <Holder<Type> > 
        {
            typedef Type type;
            enum { value = 1 };
        };
    }


    template <class T> class IDotEnumerator;

    template <typename Collection>
    struct std_accessor;

    template <typename T>
    struct std_accessor_base 
    {
        /*virtual IDotEnumerator<T> begin() = 0;
        virtual IDotEnumerator<T> end() = 0;*/

        template <typename CollectionType>
        inline std_accessor<CollectionType >& cast();
    };

    template <typename Collection>
    struct std_accessor : std_accessor_base <typename detail::is_collection<Collection>::type>
    {
        typedef typename
        detail::is_collection<Collection>::type value_type;

        std_accessor(std::reference_wrapper<Collection > const& c) 
                //: c_(c)
        {   }

        //std::reference_wrapper<Collection > c_;
    };

    template <typename T>
    template <typename CollectionType>
    inline std_accessor<CollectionType >& std_accessor_base<T>::cast()  
    {
        typedef typename 
            detail::is_collection<CollectionType>::type request_value_type;

        static_assert(std::is_same<request_value_type, T>::value, "This is not converted collections type");
    }


    /// <summary>Exposes the enumerator, which supports a simple
    /// iteration over a collection of a specified type.</summary>
    template <class T>
    class IDotEnumerable
    {
    public: // METHODS
        template <typename Collection>
        explicit IDotEnumerable(std::reference_wrapper<Collection > coll)
            : accessor_(new std_accessor<Collection>(coll))
        {  }

        /// <summary>(IDotEnumerable) Returns an enumerator that iterates through the collection.</summary>
        virtual dot::IDotEnumerator<T> GetEnumerator() = 0;

    protected:
        IDotEnumerable() = default;
    public:
        // static DotPtr<IDotEnumerable<T>> create() { throw ClEx("Attempting to create an instance of abstract type."); }
    protected:
        std::unique_ptr<std_accessor_base<T > > accessor_;
    };

    //! The key value type 
    // Currenlty we use type to rforward to std::pair 
    // in next step we'll use our type friendly and convertible to pair 
    template <typename Key, typename Value>
    class KeyValuePair : public std::pair<Key, Value>
    {
    public:
        typedef std::pair<Key, Value> base;
        KeyValuePair() : base()
        {   }

        typedef std::pair<Key, Value> type;
    };

    namespace detail
    {
        template <typename Enumerable, typename Iterable >
        class std_accessor_ : public Enumerable
        {
        public:
            typedef typename
                detail::is_collection<Iterable>::type value_type;

            typedef Iterable std_base;

            std_accessor_() : Enumerable(std::ref(c_))
            {

            }

            //! begin std iterator method 
            //! should return the start pointer to begin collection 
            inline typename Iterable::iterator
            begin()
            {
                return c_.begin();
            }

            // Last iterator 
            inline typename Iterable::iterator
            end()
            {
                return c_.end();
            }

            //! begin std iterator method 
            //! should return the start pointer to begin collection 
            inline typename Iterable::const_iterator
            begin() const
            {
                return c_.begin();
            }

            // Last iterator 
            inline typename Iterable::const_iterator
            end() const
            {
                return c_.end();
            }


            //! Method returns Enumerator contains start iterator 
            //! for std collection 
            inline dot::IDotEnumerator<value_type >
            GetEnumerator()
            {
                return dot::IDotEnumerator<value_type>(c_.begin());
            }

            //  Should return the instance of std type 
            // as an constant reference 
            inline std_base const& get() const
            {
                return this->c_;
            }

            //  Should return the instance of std type 
            // as an not constant reference 
            inline std_base& get()
            {
                return this->c_;
            }

            Iterable c_;
        };

        template <typename Enumerable, typename Type, typename Key, typename Pred, typename Allocator>
        class std_accessor_<Enumerable, std::map<Type, Key, Pred, Allocator> > 
                : public Enumerable
        {
        public:
            typedef Type        value_type;
            typedef Key         key_type;
            typedef Pred        pred_type;
            typedef Allocator   allocator;

            typedef std::map<Type, Key, Pred, Allocator> Iterable;
            typedef Iterable std_base;

            // I'll try to return it 
            // typedef decltype(*((Enumerable*)0).GetEnumerator()) enumerator_value_type;

            // Enumerator type 
            // should be returned by remove holder 
            typedef dot::IDotEnumerator<typename
                detail::remove_holder<Enumerable>::type > EnumeratorType;

            static_assert (detail::remove_holder<Enumerable>::value
                , "This type should contains value base for enumerator");

            std_accessor_() : Enumerable(std::ref(c_))
            {

            }

            //! begin std iterator method 
            //! should return the start pointer to begin collection 
            inline typename Iterable::iterator
            begin()
            {
                return c_.begin();
            }

            // Last iterator 
            inline typename Iterable::iterator
            end()
            {
                return c_.end();
            }

            //! begin std iterator method 
            //! should return the start pointer to begin collection
            inline typename Iterable::const_iterator
            begin() const
            {
                return c_.begin();
            }

            // Last iterator 
            inline typename Iterable::const_iterator
            end() const
            {
                return c_.end();
            }

            //! Method returns Enumerator contains start iterator 
            //! for std collection 
            inline EnumeratorType
            GetEnumerator()
            {
                //  typename std::remove_reference<decltype(Iterator(). operator*()) >::type
                return EnumeratorType(c_.begin());
            }

            //  Should return the instance of std type 
            // as an constant reference 
            inline std_base const& get() const
            {
                return this->c_;
            }

            //  Should return the instance of std type 
            // as an not constant reference 
            inline std_base& get()
            {
                return this->c_;
            }

            Iterable c_;
        };
    }
}

#endif  // __dot_system_collections_generic_IDotEnumerable_hpp__
