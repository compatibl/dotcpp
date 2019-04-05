﻿/*
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
#include <approvals/ApprovalTests.hpp>
#include <approvals/Catch.hpp>
#include <cl/dotcpp/main/system/Object.hpp>
#include <cl/dotcpp/main/system/String.hpp>
#include <cl/dotcpp/main/system/NullableBool.hpp>
#include <cl/dotcpp/main/system/NullableDouble.hpp>
#include <cl/dotcpp/main/system/NullableInt.hpp>
#include <cl/dotcpp/main/system/collections/generic/List.hpp>
#include <cl/dotcpp/main/system/NullableLong.hpp>
#include <cl/dotcpp/main/system/Type.hpp>

namespace cl
{
    TEST_CASE("Smoke")
    {
        {
            //Boxing Enumerable
            List<double> obj = new_List<double>();
            obj->Add(1.);
            obj->Add(2.);
            obj->Add(3.);

            Object boxed = obj;
            IObjectEnumerable list = IObjectEnumerable(boxed);
            int i = 0;
            for (Object item : list)
            {
                REQUIRE((double)item == ++i);
            }
        }

        {
            // Boxing bool
            bool x = false;
            Object boxed = x;
            REQUIRE((bool)boxed == false);
            boxed = true;
            REQUIRE((bool)boxed == true);
        }

        {
            // Boxing NullableBool
            NullableBool x;
            Object boxed = x;
            REQUIRE(((NullableBool)boxed).IsEmpty());
            NullableBool y = true;
            boxed = y;
            REQUIRE((bool)boxed == true);
        }

        {
            // Boxing double
            double x = 1.0;
            Object boxed = x;
            REQUIRE((double)boxed == 1.0);
            boxed = 2.0;
            REQUIRE((double)boxed == 2.0);
        }

        {
            // Boxing NullableDouble
            NullableDouble x;
            Object boxed = x;
            REQUIRE(((NullableDouble)boxed).IsEmpty());
            NullableDouble y = 2.0;
            boxed = y;
            REQUIRE((double)boxed == 2.0);
        }

        {
            // Boxing int
            int x = 1;
            Object boxed = x;
            REQUIRE((int)boxed == 1);
            boxed = 2;
            REQUIRE((int)boxed == 2);
        }

        {
            // Boxing NullableInt
            NullableInt x;
            Object boxed = x;
            REQUIRE(((NullableInt)boxed).IsEmpty());
            NullableInt y = 2;
            boxed = y;
            REQUIRE((int)boxed == 2);
        }

        {
            // Boxing int64_t
            int64_t x = 1;
            Object boxed = x;
            REQUIRE((int64_t)boxed == 1);
            boxed = (int64_t)2;
            REQUIRE((int64_t)boxed == 2);
        }

        {
            // Boxing NullableLong
            NullableLong x;
            Object boxed = x;
            REQUIRE(((NullableLong)boxed).IsEmpty());
            NullableLong y = (int64_t)2;
            boxed = y;
            REQUIRE((int64_t)boxed == 2);
        }
    }
}