// Perfect hash function generator for switch statements
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

#include <fstream>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "search.hpp"

// Arguments passed in command line
std::string arg_namespace;
std::string arg_func_name;
bool arg_new_format;

struct EnumNameGen
{
    EnumNameGen()
    {
        m_used.insert( get_default_case_label() );
    }

    std::string get_default_case_label() const
    {
        return "default_";
    }

    std::string get_case_label( const std::string &s )
    {
        {
            auto it = m_names_map.find( s );
            if ( it != m_names_map.end() )
            {
                return it->second;
            }
        }

        std::string res = "c_";
        for ( char c : s )
        {
            res.push_back( isalnum( c ) ? c : '_' );
        }

        if ( m_used.count( res ) )
        {
            for ( int i = 0; ; ++i )
            {
                std::string new_res = res + "_" + std::to_string( i );
                if ( m_used.count( new_res ) == 0 )
                {
                    res = new_res;
                    break;
                }
            }
        }

        m_used.insert( res );
        m_names_map[ s ] = res;
        return res;
    }

    std::unordered_map< std::string, std::string > m_names_map;
    std::unordered_set< std::string > m_used;
};

char ToHex( int a )
{
    if ( a < 10 )
        return a + '0';
    return a + 'A' - 10;
}

static std::string StringEscape( const std::string &unescaped )
{
    std::string res;

    for ( char c : unescaped )
    {
        if ( isprint( c ) )
        {
            if ( c == '\'' || c == '"' || c == '\\' )
            {
                res.push_back( '\\' );
            }
            res.push_back( c );
        }
        else
        {
            res += "\\x";
            res.push_back( ToHex( static_cast< unsigned char >( c ) / 16 ) );
            res.push_back( ToHex( static_cast< unsigned char >( c ) % 16 ) );
        }
    }

    return res;
}

static void OutputCpp17Code( const PerfectHash &soln )
{
    EnumNameGen enum_names;

    int max_hash_value = soln.word_map.rbegin()->first;

    size_t max_word_len = soln.word_map.begin()->second.size();
    size_t min_word_len = soln.word_map.begin()->second.size();
    for ( const auto &it : soln.word_map )
    {
        max_word_len = std::max( max_word_len, it.second.size() );
        min_word_len = std::min( min_word_len, it.second.size() );
    }

    std::string guard_macro;
    for ( char c : arg_namespace )
    {
        guard_macro.push_back( c == ':' ? '_' : c );

    }
    guard_macro += "__" + arg_func_name + "_HPP_";
    for ( char &c : guard_macro )
    {
        c = toupper( c );
    }

    std::cout
        << "#ifndef " << guard_macro << "\n"
        << "#define " << guard_macro << "\n"
        << "\n"
        << "#include <array>\n"
        << "#include <string_view>\n"
        << "\n";

    if ( arg_namespace.size() )
    {
        std::cout << "namespace " << arg_namespace << " {\n";
    }

    std::cout
        << "\n"
        << "namespace internal_ {\n"
        << "\n"
        << "enum class " << arg_func_name << "_enum\n"
        << "{\n"
        << "    " << enum_names.get_default_case_label() << " = -1,\n";

    int idx = -1;
    for ( const auto &it : soln.word_map )
    {
        ++idx;
        std::cout
            << "    " << enum_names.get_case_label( it.second ) << " = " << idx << ",\n";
    }

    std::cout
        << "};\n"
        << "\n"
        << "} // namespace internal_\n"
        << "\n"
        << "constexpr internal_::" << arg_func_name << "_enum " << arg_func_name << "( std::string_view s );\n"
        << "\n"
        << "namespace internal_ {\n"
        << "\n";

    // TODO check on a flag to enable definitions for use from multiple translation units?

    std::cout << "constexpr std::array< int, " << soln.asso_values.size() << " > asso_values = {\n";

    for ( size_t i = 0; i < soln.asso_values.size(); ++i )
    {
        if ( i % 10 == 0 )
        {
            std::cout << "    ";
        }

        std::cout << std::setw( 6 ) << std::right << soln.asso_values[ i ] << ",";

        if ( i % 10 == 9 || i == soln.asso_values.size() - 1 )
        {
            std::cout << "\n";
        }
    }

    std::cout << "};\n\n";


    std::cout
        << "struct word_entry\n"
        << "{\n"
        << "    std::string_view word;\n"
        << "    " << arg_func_name << "_enum enum_val;\n"
        << "};\n"
        << "\n";

    std::cout << "constexpr std::array< word_entry, " << max_hash_value + 1 << " > wordlist = {{\n";
    {
        int index = 0;
        for ( const auto &it : soln.word_map )
        {
            int hash = it.first;
            const std::string &keyword = it.second;
            std::string case_label = enum_names.get_case_label( keyword );

            while (index < hash )
            {
                std::cout << "    { \"\", " << arg_func_name << "_enum::" << enum_names.get_default_case_label() << " },\n";
                ++index;
            }

            std::cout << "    { \"" << StringEscape( keyword ) << "\", " << arg_func_name << "_enum::" << case_label << " },\n";
            ++index;
        }
    }
    std::cout
        << "}};\n"
        << "\n"
        << "} // namespace internal_\n"
        << "\n";

    std::cout
        << "constexpr internal_::" << arg_func_name << "_enum " << arg_func_name << "( std::string_view s )\n"
        << "{\n"
        << "    constexpr size_t MinWordLength = " << min_word_len << ";\n"
        << "    constexpr size_t MaxWordLength = " << max_word_len << ";\n"
        << "    constexpr size_t MaxHashValue = " << max_hash_value << ";\n"
        << "\n"
        // TODO is this check really useful, considering the switch below?
        << "    if ( s.size() < MinWordLength || s.size() > MaxWordLength )\n"
        << "    {\n"
        << "        return internal_::" << arg_func_name << "_enum::" << enum_names.get_default_case_label() << ";\n"
        << "    }\n"
        << "\n"
        << "    size_t hash_val = s.size();\n";

    if ( soln.key_positions.count( -1 ) )
    {
        std::cout << "    hash_val += internal_::asso_values[ static_cast< unsigned char >( s[ s.size() - 1 ] ) ];\n";
    }

    std::cout
        << "    switch( s.size() )\n"
        << "    {\n";

    for ( int len = max_word_len; len > 0; --len )
    {
        int pos = len - 1;

        if ( len == (int)max_word_len )
        {
            std::cout << "                       case " << len << ":\n";
        }
        else
        {
            std::cout << "    [[ fallthrough ]]; case " << len << ":\n";
        }

        if ( soln.key_positions.count( pos ) )
        {
            std::cout << "        hash_val += internal_::asso_values[ static_cast< unsigned char >( s[ " << pos << "]";

            if ( soln.alpha_inc[ pos ] )
            {
                std::cout << " + " << soln.alpha_inc[ pos ];
            }

            std::cout << " ) ];\n";
        }
        else if ( len == 1 )
        {
            std::cout << "        ; // Prevent compiler error\n";
        }
    }

    std::cout
        << "    }\n"
        << "\n"
        << "    if ( hash_val <= MaxHashValue && internal_::wordlist[ hash_val ].word == s )\n"
        << "    {\n"
        << "        return internal_::wordlist[ hash_val ].enum_val;\n"
        << "    }\n"
        << "    return internal_::" << arg_func_name << "_enum::" << enum_names.get_default_case_label() << ";\n"
        << "}\n"
        << "\n";
    if ( arg_namespace.size() )
    {
        std::cout << "} // namespace " << arg_namespace << " {\n";
    }

    std::cout
        << "\n"
        << "// Extra check for safety\n";

    idx = -1;
    for ( const auto &it : soln.word_map )
    {
        ++idx;
        std::cout << "static_assert( " << arg_namespace << "::" << arg_func_name << "( \"" << StringEscape( it.second ) << "\" ) == " << arg_namespace << "::internal_::" << arg_func_name << "_enum::" << enum_names.get_case_label( it.second ) << " );\n";
    }


    std::cout
        << "\n"
        << "#endif // " << guard_macro << "\n";
}

int main( int argc, char* argv[] )
{
    using namespace std::literals;

    for ( int i = 1; i < argc; )
    {
        if ( argv[ i ] == "--help"sv )
        {
            std::cout << "Read the doc at http://example.com\n";
            return 0;
        }

        if ( argv[ i ] == "--namespace"sv )
        {
            // TODO check if namespace is valid
            arg_namespace = argv[ i + 1 ];
            i += 2;
            continue;
        }

        if ( argv[ i ] == "--func-name"sv )
        {
            arg_func_name = argv[ i + 1 ];
            i += 2;
            continue;
        }

        std::cerr << "Unknown argument: " << argv[ i ] << "\n";
        return 1;
    }

    if ( arg_func_name.size() == 0 )
    {
        std::cerr << "Need to specify --func-name\n";
        return 1;
    }

    std::vector< std::string > input_keywords;
    {
        std::string line;
        while ( std::getline( std::cin, line ) )
        {
            input_keywords.emplace_back( std::move( line ) );
        }
    }

    OutputCpp17Code( GeneratePerfectHash( input_keywords ) );

    std::cout.flush();
    if ( ! std::cout )
    {
        std::cerr << "Error while writing output\n";
        return 1;
    }

    return 0;
}
