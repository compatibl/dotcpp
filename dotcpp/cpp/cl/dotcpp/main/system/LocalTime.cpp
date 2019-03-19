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

#include <cl/dotcpp/main/implement.hpp>
#include <cl/dotcpp/main/system/LocalTime.hpp>
#include <cl/dotcpp/main/system/Period.hpp>
#include <cl/dotcpp/main/system/LocalDateTime.hpp>

namespace cl
{
    LocalTime::LocalTime(int hour, int minute)
        : ptime(boost::gregorian::date(1970, 1, 1), time_duration {hour, minute, 0})
    {}

    LocalTime::LocalTime(int hour, int minute, int second)
        : ptime(boost::gregorian::date(1970, 1, 1), time_duration {hour, minute, second})
    {}

    LocalTime::LocalTime(int hour, int minute, int second, int millisecond)
        : ptime(boost::gregorian::date(1970, 1, 1), time_duration {hour, minute, second, millisecond * 1000})
    {}

    LocalTime::LocalTime()
    {}

    LocalTime::LocalTime(const time_duration& time)
        : ptime(boost::gregorian::date(), time)
    {}

    LocalTime::LocalTime(const ptime& time)
        : ptime(time)
    {}

    LocalTime LocalTime::Add(const LocalTime& time, const Period& period)
    {
        return time + period;
    }

    int LocalTime::CompareTo(const LocalTime& other) const
    {
        if (*this == other)
            return 0;

        return *this > other ? 1 : -1;
    }

    bool LocalTime::Equals(const LocalTime& other) const
    {
        return *this == other;
    }

    inline Period LocalTime::Minus(const LocalTime& time) const {
        return *this - time;
    }

    inline LocalTime LocalTime::Minus(const Period& period) const {
        return *this - period;
    }

    LocalDateTime LocalTime::On(const LocalDate& date)
    {
        return {date, *this};
    }

    LocalTime LocalTime::Plus(const Period& period) const
    {
        return *this + period;
    }

    LocalTime LocalTime::PlusHours(int64_t hours) const
    {
        return *this + boost::posix_time::hours(hours);
    }

    LocalTime LocalTime::PlusMilliseconds(int64_t milliseconds) const
    {
        return *this + boost::posix_time::milliseconds(milliseconds);
    }

    LocalTime LocalTime::PlusMinutes(int64_t minutes) const
    {
        return *this + boost::posix_time::minutes(minutes);
    }

    LocalTime LocalTime::PlusSeconds(int64_t seconds) const
    {
        return *this + boost::posix_time::seconds(seconds);
    }

    Period LocalTime::Subtract(const LocalTime& lhs, const LocalTime& rhs)
    {
        return lhs - rhs;
    }

    LocalTime LocalTime::Subtract(const LocalTime& time, const Period& period)
    {
        return time - period;
    }

    LocalTime LocalTime::operator+(const Period& period) const
    {
        return static_cast<ptime>(*this) + static_cast<time_duration>(period);
    }

    bool LocalTime::operator==(const LocalTime& other) const
    {
        return static_cast<ptime>(*this) == static_cast<ptime>(other);
    }

    bool LocalTime::operator!=(const LocalTime& other) const
    {
        return static_cast<ptime>(*this) != static_cast<ptime>(other);
    }

    bool LocalTime::operator>(const LocalTime& other) const
    {
        return static_cast<ptime>(*this) > static_cast<ptime>(other);
    }

    bool LocalTime::operator>=(const LocalTime& other) const
    {
        return static_cast<ptime>(*this) >= static_cast<ptime>(other);
    }

    bool LocalTime::operator<(const LocalTime& other) const
    {
        return static_cast<ptime>(*this) < static_cast<ptime>(other);
    }

    bool LocalTime::operator<=(const LocalTime& other) const
    {
        return static_cast<ptime>(*this) <= static_cast<ptime>(other);
    }

    Period LocalTime::operator-(const LocalTime& other) const
    {
        return static_cast<ptime>(*this) - static_cast<ptime>(other);
    }

    LocalTime LocalTime::operator-(const Period& period) const
    {
        return static_cast<ptime>(*this) - static_cast<time_duration>(period);
    }

    LocalTime::operator time_duration() const
    {
        return time_of_day();
    }
}
