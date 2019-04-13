#pragma once
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

/// <summary>
/// Methods typeof() and GetType() are thread safe because the implementation uses lambda
/// </summary>

#define DOT_REFLECTION(nspace, name, ...)                                                         \
        static Type typeof()                                                                      \
        {                                                                                         \
            static Type type = []()-> Type                                                        \
            {                                                                                     \
                Type type = new_TypeData<self>                                                    \
                            (nspace, name)                                                        \
                    __VA_ARGS__                                                                   \
                    ->Build();                                                                    \
                return type;                                                                      \
            }();                                                                                  \
            return type;                                                                          \
        }                                                                                         \
                                                                                                  \
        virtual Type GetType() { return typeof(); }                                               \


#define WITH_PROPERTY(prop_name)             ->WithProperty(#prop_name, &self::prop_name)
#define WITH_METHOD(meth_name, ...)          ->WithMethod(#meth_name, &self::meth_name, { __VA_ARGS__ })
#define WITH_CONSTRUCTOR(ctor_name, ...)     ->WithConstructor(&ctor_name, { __VA_ARGS__ })
#define WITH_INTERFACE(interface)            ->WithInterface<interface>()
#define WITH_BASE(base)                      ->WithBase<base>()  
#define WITH_GENERIC_ARG(arg)                ->WithGenericArgument<arg>()
