//
// deskhare
// Copyright (C) 2017 Richard Liebscher
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#pragma once

#include "../iterator_range.h"

namespace cpp {
namespace range {

template<typename Range, typename T>
auto find(Range& range, const T& t)
{
  auto last = std::end(range);
  auto first = std::find(std::begin(range), last, t);
  return cpp::make_range(first, last);
}

template<typename Range, typename Func>
auto find_if(Range& range, Func func)
{
  auto last = std::end(range);
  auto first = std::find_if(std::begin(range), last, std::move(func));
  return cpp::make_range(first, last);
}

} // namespace range
} // namespace cpp


