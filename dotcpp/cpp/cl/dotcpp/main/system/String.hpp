﻿/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, a native C++ implementation of
selected .NET class library APIs with built-in support for
algorithmic differentiation (AD), available from

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

#ifndef cl_dotcpp_main_String_hpp
#define cl_dotcpp_main_String_hpp

#include <cl/dotcpp/main/declare.hpp>
#include <cl/dotcpp/main/system/Object.hpp>
#include <cl/dotcpp/main/system/Ptr.hpp>
#include <xhash>

namespace cl
{
    class String; using tstring = String;

    template <class T> class IEnumerable;
    template <class T> class Array;
    enum class TCompareOptions;
    enum class StringSplitOptions;
    enum class StringComparison;
    class Char;
    class TCultureInfo;
    class Object;
    class ITFormatProvider;

    /// <summary>Immutable string type with Unicode support.</summary>
    class CL_DOTCPP_MAIN String
    {
        friend class StringBuilder;

        std::string value_;

    public: // CONSTANTS

        /// <summary>Empty string.</summary>
        static const String Empty;

    public: // CONSTRUCTORS

        /// <summary>Create from a single Unicode character.</summary>
        String() : value_() {}

        /// <summary>Create from a single Unicode character.</summary>
        String(const Char& value);

        /// <summary>Create from std::string.</summary>
        String(const std::string& value);

        /// <summary>Create from const char*, null pointer is converted to to empty value.</summary>
        String(const char* value);

        /// <summary>Create from a single 8-bit character.</summary>
        String(char value);

        /// <summary>Create a copy of String.</summary>
        String(const String& value);

    public: // METHODS

        ///<summary>Convert to std::string.</summary>
        std::string value() const { return value_; }

        /// <summary>Returns the number of 8-bit characters, not the number of Unicode characters.\\
        /// This number may be different from the number of Unicode characters because each
        /// Unicode character might be represented by more than one 8-bit character.</summary>
        int byteCount() const;

    public: // METHODS

        ///<summary>Hash code.</summary>
        int getHashCode() const
        {
            return std::hash<std::string>()(value_);
        }

        /// <summary>Determines whether the end of this
        /// string matches the specified string.</summary>
        bool EndsWith(String const& value)
        {
            int p = value_.length() - value.value_.length();
            if (p >= 0 && value_.substr(p, value.value_.length())
                == value.value_)
                return true;
            return false;
        }

        /// <summary>Determines whether the beginning of this
        /// string matches the specified string.</summary>
        bool StartsWith(String const& value)
        {
            int p = value_.length() - value.value_.length();
            if (p >= 0 && value_.substr(0, value.value_.length()) == value.value_)
                return true;
            return false;
        }

        /// <summary>Retrieves a substring which starts at the specified
        /// character position and has the specified length.</summary>
        String Substring(int startIndex, int length)
        {
            return value_.substr(startIndex, length);
        }

        /// <summary>Gets the number of characters in the current string.
        /// Note that for Unicode this is not the same as the number of bytes.</summary>
        int getLength()
        {
            return value_.length(); //!!! This has to be corrected for Unicode
        }

        /// <summary>Compares this instance with a specified Object and indicates whether
        /// this instance precedes, follows, or appears in the same position in the sort
        /// order as the specified Object.</summary>
        int compareTo(const Object& value) const;

        /// <summary>Compares this instance with a specified String object and indicates
        /// whether this instance precedes, follows, or appears in the same position
        /// in the sort order as the specified String.</summary>
        int compareTo(const String& strB) const;

        /// <summary>Returns a new string in which all occurrences of a specified string
        /// in the current instance are replaced with another specified string.</summary>
        String Replace(const String& oldValue, const String& newValue) const;

        /// <summary>Returns a string array that contains the substrings of the current string
        /// that are delimited by any of the specified 8-bit characters.</summary>
        Array<String> Split(char separator) const;

        /// <summary>Returns a string array that contains the substrings in
        /// this string that are delimited by any of the specified strings.\\
        /// A parameter specifies whether to return empty array elements.</summary>
        Array<String> Split(const Array<String>& separator, const StringSplitOptions& options) const;

        ///<summary>Indicates whether the argument occurs within this string.</summary>
        inline bool Contains(cl::String const& s) const
        {
            return value_.find(s.value_) != std::string::npos;
        }

        ///<summary>Returns a copy of this string converted to lowercase.</summary>
        String ToLower() const;

        ///<summary>Returns a copy of this System.String object converted to lowercase using the casing rules of the invariant culture.</summary>
        String ToLowerInvariant() const;

        ///<summary>Returns a copy of this string converted to uppercase.</summary>
        String ToUpper() const;

        ///<summary>Returns a copy of this System.String object converted to uppercase using the casing rules of the invariant culture.</summary>
        String ToUpperInvariant() const;

    public: // OPERATORS

        /// <summary>Assignment of std::string.</summary>
        String& operator=(const std::string& rhs);

        /// <summary>Assignment of const char*, null pointer is converted to to empty value.</summary>
        String& operator=(const char* rhs);

        /// <summary>Assignment of 8-bit character.</summary>
        String& operator=(char rhs);

        /// <summary>Equality operator.</summary>
        bool operator==(const String& rhs) const;

        /// <summary>Inequality operator.</summary>
        bool operator!=(const String& rhs) const;

        /// <summary>Gets the Char object at a specified position in the current String object.</summary>
        Char operator[](int index) const;

        /// <summary>Returns a string containing characters from lhs followed by the characters from rhs.</summary>
        friend String operator+(const String& lhs, const String& rhs);

        /// <summary>Returns a string containing characters from lhs followed by the characters from rhs.</summary>
        friend bool operator<(const String& lhs, const String& rhs);

    public: // STATIC

        /// <summary>Compares two specified String objects and returns an integer that
        /// indicates their relative position in the sort order.</summary>
        static int Compare(const String& strA, const String& strB);

        /// <summary>Compares two specified String objects, ignoring or honoring their
        /// case, and returns an integer that indicates their relative position in the
        /// sort order.</summary>
        static int Compare(const String& strA, const String& strB, bool ignoreCase);

        /// <summary>Compares two specified String objects using the specified rules, and
        /// returns an integer that indicates their relative position in the sort order.</summary>
        static int Compare(const String& strA, const String& strB, const StringComparison& comparisonType);

        /// <summary>Compares two specified String objects, ignoring or honoring their
        /// case, and using culture-specific information to influence the comparison,
        /// and returns an integer that indicates their relative position in the sort
        /// order.</summary>
        static int Compare(const String& strA, const String& strB, bool ignoreCase, const TCultureInfo& culture);

        /// <summary>Compares two specified String objects using the specified comparison
        /// options and culture-specific information to influence the comparison, and
        /// returns an integer that indicates the relationship of the two strings to
        /// each other in the sort order.</summary>
        static int Compare(const String& strA, const String& strB, const TCultureInfo& culture, TCompareOptions options);

        /// <summary>Compares substrings of two specified String objects and returns an
        /// integer that indicates their relative position in the sort order.</summary>
        static int Compare(const String& strA, int indexA, const String& strB, int indexB, int length);

        /// <summary>Compares substrings of two specified String objects, ignoring or honoring
        /// their case, and returns an integer that indicates their relative position
        /// in the sort order.</summary>
        static int Compare(const String& strA, int indexA, const String& strB, int indexB, int length, bool ignoreCase);

        /// <summary>Compares substrings of two specified String objects using the specified
        /// rules, and returns an integer that indicates their relative position in the
        /// sort order.</summary>
        static int Compare(const String& strA, int indexA, const String& strB, int indexB, int length, const StringComparison& comparisonType);

        /// <summary>Compares substrings of two specified String objects, ignoring or honoring
        /// their case and using culture-specific information to influence the comparison,
        /// and returns an integer that indicates their relative position in the sort
        /// order.</summary>
        static int Compare(const String& strA, int indexA, const String& strB, int indexB, int length, bool ignoreCase, const TCultureInfo& culture);

        /// <summary>Compares substrings of two specified String objects using the specified
        /// comparison options and culture-specific information to influence the comparison,
        /// and returns an integer that indicates the relationship of the two substrings
        /// to each other in the sort order.</summary>
        static int Compare(const String& strA, int indexA, const String& strB, int indexB, int length, const TCultureInfo& culture, const TCompareOptions& options);

        /// <summary>Compares two specified String objects by evaluating the numeric values
        /// of the corresponding Char objects in each string.</summary>
        static int CompareOrdinal(const String& strA, const String& strB);

        /// <summary>Compares substrings of two specified String objects by evaluating
        /// the numeric values of the corresponding Char objects in each substring.</summary>
        static int CompareOrdinal(const String& strA, int indexA, const String& strB, int indexB, int length);

        /// <summary>Concatenates the elements of a specified String array.</summary>
        static String Concat(const IEnumerable<String>& values);

        /// <summary>Concatenates the members of an IEnumerable<T> implementation.</summary>
        template <class T>
        static String Concat(const IEnumerable<T>& values);

        /// <summary>Creates the string representation of a specified object.</summary>
        static String Concat(const Object& arg0);

        /// <summary>Concatenates the string representations of the elements in a specified Object array.</summary>
        static String Concat(const Array<Object>& args);

        /// <summary>Concatenates the elements of a specified String array.</summary>
        static String Concat(const Array<String>& values);

        /// <summary>Concatenates the string representations of two specified objects.</summary>
        static String Concat(const Object& arg0, const Object& arg1);

        /// <summary>Concatenates two specified instances of String.</summary>
        static String Concat(const String& str0, const String& str1);

        /// <summary>Concatenates the string representations of three specified objects.</summary>
        static String Concat(const Object& arg0, const Object& arg1, const Object& arg2);

        /// <summary>Concatenates three specified instances of String.</summary>
        static String Concat(const String& str0, const String& str1, const String& str2);

        /// <summary>Concatenates the string representations of four specified objects and any
        /// objects specified in an optional variable length parameter list.</summary>
        static String Concat(const Object& arg0, const Object& arg1, const Object& arg2, const Object& arg3);

        /// <summary>Concatenates four specified instances of System.String.</summary>
        static String Concat(const String& str0, const String& str1, const String& str2, const String& str3);

        /// <summary>Creates a new instance of System.String with the same value as a specified String.</summary>
        static String copy(const String& str);

        /// <summary>Determines whether two specified System.String objects have the same value.</summary>
        static bool equals(const String& strA, const String& strB);

        /// <summary>Determines whether two specified System.String objects have the same value.
        /// A parameter specifies the culture, case, and sort rules used in the comparison.</summary>
        static bool equals(const String& strA, const String& strB, const StringComparison& comparisonType);

        /// <summary>Replaces one or more format items in a specified string with the string representation
        /// of a specified object.</summary>
        static String Format(const String& format, const Object& arg0);

        /// <summary>Replaces the format item (e.g. {0}, {1}, etc.) in a specified string
        /// with the string representation of a corresponding object in a specified array.</summary>
        static String Format(const String& format, const Array<Object>& args);

        /// <summary>Replaces the format item in a specified string with the string representation
        /// of a corresponding object in a specified array. A specified parameter supplies
        /// culture-specific formatting information.</summary>
        static String Format(const ITFormatProvider& provider, const String& format, const Array<Object>& args);

        /// <summary>Replaces the format items in a specified string with the string representation
        /// of two specified objects.</summary>
        static String Format(const String& format, const Object& arg0, const Object& arg1);

        /// <summary>Replaces the format items in a specified string with the string representation
        /// of three specified objects.</summary>
        static String Format(const String& format, const Object& arg0, const Object& arg1, const Object& arg2);

        /// <summary>Indicates whether the specified string is null or empty.
        /// Note that null string and empty string are not the same.</summary>
        static bool IsNullOrEmpty(const String& str);

        /// <summary>Indicates whether a specified string is null,
        /// empty, or consists only of white-space characters.
        /// Note that null string and empty string are not the same.</summary>
        static bool IsNullOrWhiteSpace(const String& str);

        /// <summary>Concatenates the members of a constructed IEnumerable<T>
        /// collection of type String, using the specified separator between each
        /// member.</summary>
        static String Join(const String& separator, const IEnumerable<String>& values);

        /// <summary>Concatenates the members of a collection, using the specified separator between
        /// each member.</summary>
        template<class T>
        static String Join(const String& separator, const IEnumerable<T>& values);

        /// <summary>Concatenates the elements of an object array, using the specified separator
        /// between each element.</summary>
        static String Join(const String& separator, const Array<Object>& values);

        /// <summary>Concatenates all the elements of a string array, using the specified separator
        /// between each element.</summary>
        static String Join(const String& separator, const Array<String>& value);

        /// <summary>Concatenates the specified elements of a string array, using the specified
        /// separator between each element.</summary>
        static String Join(const String& separator, const Array<String>& value, int startIndex, int count);
    };

    //!!!!!! typedef String string;

    /// <summary>Returns a string containing characters from lhs followed by the characters from rhs.</summary>
    inline String operator+(const String& lhs, const String& rhs) { return lhs.value_ + rhs.value_; }

    inline bool operator<(const String& lhs, const String& rhs) { return lhs.value_ < rhs.value_; }

    inline size_t hash_value(const cl::String& _Keyval) //!!!! Why do we need this?
    {
        return stdext::hash_value(_Keyval.value());
    }

}

namespace std
{
    // FIXME Provide detailed explanation of where this is needed and how it works
    template<>
    struct hash<cl::String> : public unary_function<cl::String, size_t>
    {
        size_t operator()(const cl::String value) const
        {
            return value.getHashCode();
        }
    };
}

#endif // cl_dotcpp_main_String_hpp