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

#include <cl/dotcpp/test/implement.hpp>
#include <cl/dotcpp/test/system/ReadOnlyPropertyTest.hpp>

namespace cl
{
    class ReadOnlyPropertySample
    {
        std::string value_ = "abc";
        static std::string getValue(ReadOnlyPropertySample& obj) { return obj.value_; }

    public:
        /// <summary>Test property</summary>
        ReadOnlyProperty<ReadOnlyPropertySample, std::string> Value = ReadOnlyProperty<ReadOnlyPropertySample, std::string>(*this, getValue);
    };

    /// <summary>Smoke test.</summary>
    void ReadOnlyPropertyTest::SmokeTest()
    {
    }

    /// <summary>Includes all test methods in this class.</summary>
    test_suite* ReadOnlyPropertyTest::GetTestSuite()
    {
        test_suite* suite = BOOST_TEST_SUITE("ReadOnlyPropertyTest");
        suite->add(BOOST_TEST_CASE(&ReadOnlyPropertyTest::SmokeTest));
        return suite;
    }
}
