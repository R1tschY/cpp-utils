//
// c++utils
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

namespace cpp {

template<typename T, typename Func>
bool between(
  const T& value, const T& min, const T& max, Func comp
)
{
  return comp(min, value) && comp(value, max);
}

template<typename T>
bool between(
  const T& value, const T& min, const T& max
)
{
  return between(value, min, max, std::less<>());
}

template<typename T, typename Func>
bool in_range(
  const T& value, const T& start, const T& end, Func comp
)
{
  return !comp(value, start) && comp(value, end);
}

template<typename T>
bool in_range(
  const T& value, const T& start, const T& end
)
{
  return in_range(value, start, end, std::less<>());
}

} // namespace cpp


