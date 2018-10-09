// Search algorithm.
//
// Copyright (C) 1989-1998, 2000, 2002-2003, 2009 Free Software Foundation, Inc.
// Written by Douglas C. Schmidt <schmidt@ics.uci.edu>
// and Bruno Haible <bruno@clisp.org>.
//
// Removed GPERF specific details and simplified implementation
// (C) Copyright 2018 Mustafa Serdar Sanli <mserdarsanli@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef SEARCH_H_
#define SEARCH_H_

#include <set>
#include <map>
#include <string>
#include <vector>

struct PerfectHash
{
    std::map< int, std::string > word_map;
    std::set< int > key_positions; // Computed key positions.
    std::vector< int > alpha_inc; // Adjustments to add to bytes add specific key positions.
    std::vector< int > asso_values; // Value associated with each character.
};

PerfectHash GeneratePerfectHash( std::vector< std::string > words );

#endif
