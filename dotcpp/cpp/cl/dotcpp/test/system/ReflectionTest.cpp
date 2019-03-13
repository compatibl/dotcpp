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
#include <cl/dotcpp/main/system/Exception.hpp>
#include <cl/dotcpp/main/system/reflection/PropertyInfo.hpp>
#include <cl/dotcpp/main/system/Type.hpp>
#include <cl/dotcpp/main/system/Array1D.hpp>
#include <cl/dotcpp/main/system/collections/generic/List.hpp>

namespace cl
{
    static std::stringstream received;

    class ReflectionBaseSampleImpl : public ObjectImpl
    {
    public:
        int IntFld;
        double DblFld;
        List<double> DblListFld;

        DOT_PROP(ReflectionBaseSampleImpl, int, Count,
            {
                received << "ReflectionBaseSample.getCount" << std::endl;
                return Count;
            },
            {
                received << "ReflectionBaseSample.setCount" << std::endl;
                Count = value;
            }
        )

    private:
        int PrivateIntFld = 42;

    public:

        virtual Type GetType()
        {
            static Type type = []()->Type
            {
                received << "Creating Type (this should run only once)." << std::endl;

                Type type = new_Type();

                type->Name = "ReflectionBaseSample";
                type->FullName = "DotCpp.System.Test.ReflectionBaseSample";

                Array1D<PropertyInfo> props = new_Array1D<PropertyInfo>(3);
                props[0] = new_PropertyInfo("IntFld", type, nullptr, &ReflectionBaseSampleImpl::IntFld);
                props[1] = new_PropertyInfo("PrivateIntFld", type, nullptr, &ReflectionBaseSampleImpl::PrivateIntFld);
                props[2] = new_PropertyInfo("Count", type, nullptr, &ReflectionBaseSampleImpl::Count);

                type->Properties = props;

                return type;
            }();

            return type;
        }
    };

    class ReflectionDerivedSampleImpl : public ReflectionBaseSampleImpl
    {
    public:

        DOT_IMPL_PROP(ReflectionDerivedSampleImpl, int, Count,
            {
                received << "ReflectionDerivedSample.getCount" << std::endl;
                return Count;
            },
            {
                received << "ReflectionDerivedSample.setCount" << std::endl;
                Count = value;
            }
        )
    };

    using ReflectionBaseSample = Ptr<ReflectionBaseSampleImpl>;
    ReflectionBaseSample new_ReflectionBaseSample() { return new ReflectionBaseSampleImpl; }

    using ReflectionDerivedSample = Ptr<ReflectionDerivedSampleImpl>;
    ReflectionDerivedSample new_ReflectionDerivedSample() { return new ReflectionDerivedSampleImpl; }

    TEST_CASE("PropertyInfo")
    {
        ReflectionBaseSample obj = new_ReflectionBaseSample();
        obj->IntFld = 15;

        Type type = obj->GetType();
        Array1D<PropertyInfo> props = type->GetProperties();
        PropertyInfo int_prop = props[0];
        REQUIRE(int_prop->Name == "IntFld");
        REQUIRE(int(int_prop->GetValue(obj)) == 15);

        int_prop->SetValue(obj, 19);
        REQUIRE(obj->IntFld == 19);
        REQUIRE(int(int_prop->GetValue(obj)) == 19);

        PropertyInfo private_int_prop = props[1];
        REQUIRE(private_int_prop->Name == "PrivateIntFld");
        REQUIRE(int(private_int_prop->GetValue(obj)) == 42);

        props[2]->SetValue(obj, 2384);
        REQUIRE(obj->Count == 2384);
        REQUIRE(int(props[2]->GetValue(obj)) == 2384);

        ReflectionDerivedSample obj2 = new_ReflectionDerivedSample();

        props[2]->SetValue(obj2, -15);
        REQUIRE(obj2->Count == -15);
        REQUIRE(int(props[2]->GetValue(obj2)) == -15);

        Approvals::verify(received.str());
        received.clear();
    }
}
