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

#pragma once

#include <cl/dotcpp/test/declare.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/test_tools.hpp>
#include <cl/dotcpp/main/system/collections/generic/List.hpp>
#include <cl/dotcpp/main/system/String.hpp>

namespace cl
{
    class CL_DOTCPP_TEST ListTest
    {
    public:

        static void iteration()
        {
            List<String> stringList = new_List<String>();
            stringList->Add("111");
            stringList->Add("222");
            stringList->Add("333");
            BOOST_CHECK(stringList->Count() == 3);

            for (String str : stringList)
            {
                std::cout << str << " ";
            }
            std::cout << std::endl;

            stringList[1] = "555";

            BOOST_CHECK(stringList[1] == "555");
        }

        static void findLast()
        {
            cl::List<String> stringList = new_List<String>();
            stringList->Add("000");
            stringList->Add("111");
            stringList->Add("222");
            stringList->Add("333");
            stringList->Add("444");
            BOOST_CHECK(stringList->Count() == 5);

            // TODO stringList.findLast([](std::string const& s) { return s == "222"; }) = "57";

            BOOST_CHECK(stringList[3] == "333");
        }

        static void findLastIndex()
        {
            List<String> stringList = new_List<String>();
            stringList->Add("111");
            stringList->Add("222");
            stringList->Add("222");
            stringList->Add("333");
            BOOST_CHECK(stringList->Count() == 4);

            // TODO BOOST_CHECK(stringList.findLastIndex([](std::string const& s) { return s == "111"; }) == 0);
        }

        static boost::unit_test::test_suite* ListTestSuite()
        {
            boost::unit_test::test_suite* suite = BOOST_TEST_SUITE("ListTest");
            suite->add(BOOST_TEST_CASE(&ListTest::iteration));
            suite->add(BOOST_TEST_CASE(&ListTest::findLast));
            suite->add(BOOST_TEST_CASE(&ListTest::findLastIndex));
            return suite;
        }
    };
}
