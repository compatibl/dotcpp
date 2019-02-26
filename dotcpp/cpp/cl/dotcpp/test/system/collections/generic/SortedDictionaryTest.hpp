/*
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

#ifndef cl_dotcpp_test_SortedDictionaryTests_hpp
#define cl_dotcpp_test_SortedDictionaryTests_hpp

#include <cl/system/api/collections/generic/TSortedDictionary.hpp>

namespace cl {
    typedef std::string String;
}

BOOST_AUTO_TEST_SUITE(TSortedDictionaryTests)

BOOST_AUTO_TEST_CASE(iteration)
{
    cl::SortedDictionary<std::string, int> sortedDictionary;

}

BOOST_AUTO_TEST_SUITE_END()


#endif // cl_dotcpp_test_SortedDictionaryTests_hpp
