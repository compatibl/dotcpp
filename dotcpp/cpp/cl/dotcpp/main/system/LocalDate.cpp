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
#include <cl/dotcpp/main/system/LocalDate.hpp>
#include <cl/dotcpp/main/system/Period.hpp>
#include <cl/dotcpp/main/system/LocalTime.hpp>
#include <cl/dotcpp/main/system/LocalDateTime.hpp>

namespace cl
{
    LocalDate::LocalDate(int year, int month, int day)
        : gdate(year, month, day)
    {}

    LocalDate::LocalDate()
    {}

    LocalDate::LocalDate(gdate date)
        : gdate(date)
    {}

    LocalDate LocalDate::Add(const LocalDate& date, const Period& period)
    {
        return date + period;
    }

    LocalDateTime LocalDate::At(const LocalTime& time) const
    {
        return *this + time;
    }

    LocalDateTime LocalDate::AtMidnight() const
    {
        return *this + LocalTime(0, 0);
    }

    int LocalDate::CompareTo(const LocalDate& other) const
    {
        if (*this == other)
            return 0;

        return *this > other ? 1 : -1;
    }

    bool LocalDate::Equals(const LocalDate& other) const
    {
        return *this == other;
    }

    Period LocalDate::Minus(const LocalDate& date) const
    {
        return *this - date;
    }

    LocalDate LocalDate::Minus(const Period& period) const
    {
        return *this - period;
    }

    LocalDate LocalDate::Next(int targetDayOfWeek) const
    {
        auto wd = boost::gregorian::greg_weekday(targetDayOfWeek);
        return boost::gregorian::next_weekday(date(), wd);
    }

    LocalDate LocalDate::Plus(const Period& period) const
    {
        return *this + period;
    }

    LocalDate LocalDate::PlusDays(int days) const
    {
        return *this + boost::gregorian::days(days);
    }

    LocalDate LocalDate::PlusMonths(int months) const
    {
        return *this + boost::gregorian::months(months);
    }

    LocalDate LocalDate::PlusWeeks(int weeks) const
    {
        return *this + boost::gregorian::weeks(weeks);
    }

    LocalDate LocalDate::PlusYears(int years) const
    {
        return *this + boost::gregorian::years(years);
    }

    LocalDate LocalDate::Previous(int targetDayOfWeek) const
    {
        auto wd = boost::gregorian::greg_weekday(targetDayOfWeek);
        return boost::gregorian::previous_weekday(date(), wd);
    }

    Period LocalDate::Subtract(const LocalDate& lhs, const LocalDate& rhs)
    {
        return lhs - rhs;
    }

    LocalDate LocalDate::Subtract(const LocalDate& date, const Period& period)
    {
        return date + period;
    }

    LocalDateTime LocalDate::operator+(const LocalTime& time) const
    {
        return {*this, time};
    }

    LocalDate LocalDate::operator+(const Period& period) const
    {
        return static_cast<gdate>(*this) + static_cast<date_duration>(period);
    }

    bool LocalDate::operator==(const LocalDate& other) const
    {
        return static_cast<gdate>(*this) == static_cast<gdate>(other);
    }

    bool LocalDate::operator!=(const LocalDate& other) const
    {
        return static_cast<gdate>(*this) != static_cast<gdate>(other);
    }

    bool LocalDate::operator>(const LocalDate& other) const
    {
        return static_cast<gdate>(*this) > static_cast<gdate>(other);
    }

    bool LocalDate::operator>=(const LocalDate& other) const
    {
        return static_cast<gdate>(*this) >= static_cast<gdate>(other);
    }

    bool LocalDate::operator<(const LocalDate& other) const
    {
        return static_cast<gdate>(*this) < static_cast<gdate>(other);
    }

    bool LocalDate::operator<=(const LocalDate& other) const
    {
        return static_cast<gdate>(*this) <= static_cast<gdate>(other);
    }

    Period LocalDate::operator-(const LocalDate& other) const
    {
        return static_cast<gdate>(*this) - static_cast<gdate>(other);
    }

    LocalDate LocalDate::operator-(const Period& period) const
    {
        return static_cast<gdate>(*this) - static_cast<date_duration>(period);
    }
}
