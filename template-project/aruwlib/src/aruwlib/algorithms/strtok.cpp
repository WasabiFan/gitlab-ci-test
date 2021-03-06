/*
 * Copyright (c) 2020-2021 Advanced Robotics at the University of Washington <robomstr@uw.edu>
 *
 * This file is part of aruwlib.
 *
 * aruwlib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * aruwlib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with aruwlib.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "strtok.hpp"

#include <cstring>

char *strtokR(char *s, const char *delim, char **savePtr)
{
    char *end;

    if (s == nullptr)
    {
        s = *savePtr;
    }

    if (*s == '\0')
    {
        *savePtr = s;
        return nullptr;
    }

    s += strspn(s, delim);
    if (*s == '\0')
    {
        *savePtr = s;
        return nullptr;
    }

    end = s + strcspn(s, delim);
    if (*end == '\0')
    {
        *savePtr = end;
        return s;
    }

    *end = '\0';
    *savePtr = end + 1;
    return s;
}
