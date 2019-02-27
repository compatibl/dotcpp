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

#include <cl/dotcpp/test/implement.hpp>
#include <cl/dotcpp/test/system/StringTest.hpp>
#include <cl/dotcpp/main/system/collections/generic/Dictionary.hpp>
#include <cl/dotcpp/main/system/Exception.hpp>

namespace cl
{
    void StringTest::Create()
    {
    }


    boost::unit_test::test_suite* StringTest::StringTestSuite()
    {
        boost::unit_test::test_suite* suite = BOOST_TEST_SUITE("TString test");
        suite->add(BOOST_TEST_CASE(&StringTest::Create));
        return suite;
    }

}

