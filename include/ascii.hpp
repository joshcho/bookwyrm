/*
 * Copyright (C) 2017 Tmplt <tmplt@dragons.rocks>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <type_traits>

enum class ascii : uint32_t {
    double_right_angle_bracket = 0xBB,      /* » */
    em_dash                    = 0x2014,    /* — */
    scrollbar_fg               = 0x2588,    /* █ */
    scrollbar_bg               = 0x2592     /* ▒ */
};

using ascii_t = std::underlying_type_t<ascii>;
