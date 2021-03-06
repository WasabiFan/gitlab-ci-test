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

#ifndef STRTOK_HPP_
#define STRTOK_HPP_

/**
 * Source code from glibc/string/strtok_r.c. arm-none-eabi-gcc does not have strtok_r,
 * so we implement it ourselves.
 */
char *strtokR(char *s, const char *delim, char **savePtr);

#endif  // STRTOK_HPP_
