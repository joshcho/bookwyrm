/*
 * This header defines a few POD-types which we use to
 * store item data in.
 *
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

#include <array>

#include "common.hpp"
#include "components/command_line.hpp"

namespace bookwyrm {

using nonexact_dict_t = std::map<string, string>;
using exact_dict_t = std::map<string, int>;
using tuple_t = std::tuple<nonexact_dict_t, exact_dict_t>;

/* Default value: "this value is empty". */
enum { empty = -1 };

/*
 * For --year:
 *   -y 2157   : list items from 2157 (equal)
 *   -y =>2157 : list items from 2157 and later (eq_gt)
 *   -y =<2157 : list items from 2157 and earlier (eq_lt)
 *   -y >2157  : list items from later than 2157 (gt)
 *   -y <2157  : list items from earlier than 2157 (lt)
 */
enum class year_mod { equal, eq_gt, eq_lt, lt, gt };

struct exacts_t {
    /*
     * A POD with added index operator.
     * Useful in item::matches() where we want to
     * iterate over these values and check if they match.
     *
     * We can then get a field value by name, which we'll
     * want when printing the stuff out.
     *
     * Fields are set to "empty" (-1) during construction.
     * This makes us able to bool-check (since -1 is false)
     * whether or not a field is empty or not.
     */
    explicit exacts_t(const std::unique_ptr<cliparser> &cli);
    /* explicit exacts_t(const exact_dict_t &dict); */
    explicit exacts_t(const std::map<string, int> &dict);

    year_mod ymod;

    int year,
        edition,
        ext,   // unused for now
        volume,
        number,
        pages, // missing flag
        lang;  // unused for now

    constexpr static int size = 7;

    std::array<int, size> store = {
        year, edition, ext,
        volume, number, pages
    };

    int operator[](int i) const
    {
        return store[i];
    }
};

struct nonexacts_t {
    /*
     * As the typename suggests, this POD contains
     * data that we're not going to match exacly match
     * exactly with the wanted field. Instead, we use
     * fuzzy-matching.
     */
    explicit nonexacts_t(const std::unique_ptr<cliparser> &cli);
    explicit nonexacts_t(const std::map<string, string> &dict, const vector<string> &authors);

    vector<string> authors;
    string title;
    string serie;
    string publisher;
    string journal;
};

struct misc_t {
    /*
     * The POD for everything else and undecided
     * fields.
     */

    vector<string> isbns;
    vector<string> mirrors;
};

/* ns bookwyrm */
}
