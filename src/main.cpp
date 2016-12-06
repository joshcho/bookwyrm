/*
 * This file is part of bookwyrm.
 * Copyright 2016, Tmplt.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../3rdparty/cxxopts.hpp"
#include "printf.hpp"

void
validate_arguments(cxxopts::Options options)
{
    /* Is any of the required arguments passed? */
    if (options["author"].as<std::vector<std::string>>().size() == 0 &&
            options["title"].as<std::string>().empty()     &&
            options["serie"].as<std::string>().empty()     &&
            options["publisher"].as<std::string>().empty() &&
            options["ident"].as<std::string>().empty()) {
        throw std::invalid_argument("missing necessary inclusive argument.");
    }

    /* Is any required argument passed alongside --ident? */
    if ((options["author"].as<std::vector<std::string>>().size() != 0 ||
            !options["title"].as<std::string>().empty()      ||
            !options["serie"].as<std::string>().empty()      ||
            !options["publisher"].as<std::string>().empty()) &&
            !options["ident"].as<std::string>().empty()) {
        throw std::invalid_argument("ident flag is exclusive, and may not be passed with another flag.");
    }

    return;
}

cxxopts::Options
parse_command_line(int argc, char *argv[])
{
    cxxopts::Options options(argv[0], "- find books and papers online and download them.");

    options.add_options("Necessarily inclusive arguments; at least one is required")
        ("a,author", "Author", cxxopts::value<std::vector<std::string>>())
        ("t,title", "Title", cxxopts::value<std::string>())
        ("s,serie", "Serie", cxxopts::value<std::string>())
        ("p,publisher", "Publisher", cxxopts::value<std::string>())
        ("d,ident", "Unique identifier, such as an URL or DOI", cxxopts::value<std::string>())
    ;

    options.add_options("Exact arguments; optional")
        ("y,year", "Year", cxxopts::value<int>())
        ("l,language", "Language", cxxopts::value<std::string>())
        ("e,edition", "Edition", cxxopts::value<std::string>())
        ("E,extention", "File extension without period, e.g. 'pdf'.", cxxopts::value<std::string>())
        ("i,isbn", "ISBN string", cxxopts::value<std::string>())
    ;

    options.add_options()
        ("version", "Print program version")
    #ifdef DEBUG
        ("debug", "Debug")
    #endif
    ;

    options.parse(argc, argv);
    validate_arguments(options);

    return options;
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        fmt::fprintf(stderr, "Print usage here.\n");
        return 0;
    }

    try {
        cxxopts::Options options = parse_command_line(argc, argv);
    }
    catch (cxxopts::OptionException &oe) {
        fmt::printf("%s: %s\n", argv[0], oe.what());
        return 1;
    }
    catch (std::invalid_argument &ia) {
        fmt::printf("%s: %s\n", argv[0], ia.what());
        return 1;
    }

    return 0;
}

