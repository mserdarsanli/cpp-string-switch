// Search algorithm.
//
// Copyright (C) 1989-1998, 2000, 2002-2003, 2009, 2016 Free Software Foundation, Inc.
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

#include "search.hpp"

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <set>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct Keywords
{
public:
    Keywords( Keywords && ) = default;
    Keywords( const Keywords & ) = default;
    Keywords& operator=( const Keywords & ) = default;

    Keywords( std::vector< std::string > &&words )
        : m_keywords( std::move( words ) )
    {
        auto size_less = []( const auto &k1, const auto &k2 ) -> bool
        {
            return k1.size() < k2.size();
        };

        m_min_size = std::min_element( m_keywords.begin(), m_keywords.end(), size_less )->size();
        m_max_size = std::max_element( m_keywords.begin(), m_keywords.end(), size_less )->size();

        if ( m_min_size == 0 )
        {
            throw std::runtime_error( "Empty input keyword is not allowed." );
        }
    }

    auto begin() const { return m_keywords.begin(); };
    auto end()   const { return m_keywords.end();   };
    auto size()  const { return m_keywords.size();   };
    const auto& operator[]( size_t idx ) const { return m_keywords[ idx ]; }

    size_t max_size() const { return m_max_size; }
    size_t min_size() const { return m_min_size; }

private:
    size_t m_max_size;
    size_t m_min_size;
    std::vector< std::string > m_keywords;
};

struct Search
{
    Search( Keywords &&keywords )
        : m_keywords( std::move( keywords ) )
    {
    }

    PerfectHash get_solution()
    {
        PerfectHash res;
        res.word_map = word_map;
        res.key_positions = _key_positions;
        res.alpha_inc = _alpha_inc;
        res.asso_values = _asso_values;
        return res;
    }

  void                  optimize ();
private:

  /* Finds good _asso_values[].  */
  void                  find_good_asso_values ();

public:

    Keywords m_keywords; // TODO??

private:

  std::map< int, std::string > word_map; // Output param


  /* User-specified or computed key positions.  */
  std::set< int >             _key_positions;

  /* Adjustments to add to bytes add specific key positions.  */
  std::vector< int >        _alpha_inc;

  /* Value associated with each character. */
  std::vector< int >    _asso_values;
};



struct Chars
{
    Chars() = default;
    Chars( size_t keyword_size, std::vector< int > &&data )
        : m_keyword_size( keyword_size )
        , m_data( std::move( data ) )
    {
    }

    size_t count( int ch )
    {
        return std::count( m_data.begin(), m_data.end(), ch );
    }

    std::vector< int >::const_iterator begin() const { return m_data.begin(); }
    std::vector< int >::const_iterator end()   const { return m_data.end();   }

    size_t m_keyword_size;
    std::vector< int > m_data;
};

inline
bool operator==( const Chars &v1, const Chars &v2 )
{
    return v1.m_keyword_size == v2.m_keyword_size && v1.m_data == v2.m_data;
}

namespace std {

template<> struct hash< Chars >
{
    size_t operator()( const Chars &s ) const noexcept
    {
        size_t res = s.m_keyword_size;
        for ( int ch : s.m_data )
        {
            res ^= ch + 0x9e3779b9 + (res << 6) + (res >> 2);
        }
        return res;
    }
};

} // namespace std

static inline
size_t next_power_of_2( size_t a )
{
    size_t res = 2;
    while ( res <= a )
        res *= 2;
    return res;
}

/* Initializes selchars and selchars_length.

   General idea:
     The hash function will be computed as
         asso_values[allchars[key_pos[0]]] +
         asso_values[allchars[key_pos[1]]] + ...
     We compute selchars as the multiset
         { allchars[key_pos[0]], allchars[key_pos[1]], ... }
     so that the hash function becomes
         asso_values[selchars[0]] + asso_values[selchars[1]] + ...
   Furthermore we sort the selchars array, to ease detection of duplicates
   later.

   More in detail: The arguments alpha_inc (used to disambiguate permutations)
   apply slight modifications. The hash function will be computed as
       sum (j=0,1,...: k = key_pos[j]:
            asso_values[allchars[k]+alpha_inc[k]])
       + (allchars_length).
   We compute selchars as the multiset
       { allchars[k]+alpha_inc[k] : j=0,1,..., k = key_pos[j] }
   so that the hash function becomes
       asso_values[selchars[0]] + asso_values[selchars[1]] + ...
       + allchars_length.
 */

static
Chars selchars( const std::string &allchars,
                const std::set< int >& positions,
                const std::vector< int > &alpha_inc )
{
  std::vector< int > key_set;

  // Iterate through the list of positions, initializing selchars
  for ( auto it = positions.rbegin(); it != positions.rend(); ++it )
    {
      int i = *it;
      if ( i >= (int)allchars.size() )
        continue;

      int c;
      if (i == -1)
        /* Special notation for last KEY position, i.e. '$'.  */
        c = static_cast<unsigned char>( allchars[ allchars.size() - 1]);
      else
        {
          /* Within range of KEY length, so we'll keep it.  */
          c = static_cast<unsigned char>(allchars[i]);
          if (alpha_inc.size())
            c += alpha_inc[i];
        }

      key_set.push_back( c );
    }

  if ( alpha_inc.size() )
    std::sort( key_set.begin(), key_set.end() );

  return Chars( allchars.size(), std::move( key_set ) );
}


/* ================================ Theory ================================= */

/* The general form of the hash function is

      hash (keyword) = sum (asso_values[keyword[i] + alpha_inc[i]] : i in Pos)
                       + len (keyword)

   where Pos is a set of byte positions,
   each alpha_inc[i] is a nonnegative integer,
   each asso_values[c] is a nonnegative integer,
   len (keyword) is the keyword's length if _hash_includes_len, or 0 otherwise.

   Theorem 1: If all keywords are different, there is a set Pos such that
   all tuples (keyword[i] : i in Pos) are different.

   Theorem 2: If all tuples (keyword[i] : i in Pos) are different, there
   are nonnegative integers alpha_inc[i] such that all multisets
   {keyword[i] + alpha_inc[i] : i in Pos} are different.

   Define selchars[keyword] := {keyword[i] + alpha_inc[i] : i in Pos}.

   Theorem 3: If all multisets selchars[keyword] are different, there are
   nonnegative integers asso_values[c] such that all hash values
   sum (asso_values[c] : c in selchars[keyword]) are different.

   Based on these three facts, we find the hash function in three steps:

   Step 1 (Finding good byte positions):
   Find a set Pos, as small as possible, such that all tuples
   (keyword[i] : i in Pos) are different.

   Step 2 (Finding good alpha increments):
   Find nonnegative integers alpha_inc[i], as many of them as possible being
   zero, and the others being as small as possible, such that all multisets
   {keyword[i] + alpha_inc[i] : i in Pos} are different.

   Step 3 (Finding good asso_values):
   Find asso_values[c] such that all hash (keyword) are different.

   In other words, each step finds a projection that is injective on the
   given finite set:
     proj1 : String --> Map (Pos --> N)
     proj2 : Map (Pos --> N) --> Map (Pos --> N) / S(Pos)
     proj3 : Map (Pos --> N) / S(Pos) --> N
   where
     N denotes the set of nonnegative integers,
     Map (A --> B) := Hom_Set (A, B) is the set of maps from A to B, and
     S(Pos) is the symmetric group over Pos.

   This was the theory for !_hash_includes_len; if _hash_includes_len, slight
   modifications apply:
     proj1 : String --> Map (Pos --> N) x N
     proj2 : Map (Pos --> N) x N --> Map (Pos --> N) / S(Pos) x N
     proj3 : Map (Pos --> N) / S(Pos) x N --> N

   For a case-insensitive hash function, the general form is

      hash (keyword) =
        sum (asso_values[keyword[i] + alpha_inc[i]] : i in Pos)
        + len (keyword)
 */

/* Count the duplicate keywords that occur with the found set of positions.
   In other words, it returns the difference
     # K - # proj1 (K)
   where K is the multiset of given keywords.  */
static
size_t count_duplicates( const Keywords &keywords,
                         const std::set< int > &positions )
{
  /* Run through the keyword list and count the duplicates incrementally.
     The result does not depend on the order of the keyword list, thanks to
     the formula above.  */

  std::unordered_set< Chars > representatives;

  for ( const std::string &kw : keywords )
  {
     representatives.emplace( selchars( kw, positions, {} ) );
  }

  return keywords.size() - representatives.size();
}

/* ====================== Finding good byte positions ====================== */

// Return idx ( >= 0 if that is the only differentiating position )
// Otherwise return -1
static
int only_diff_idx( const std::string &word1, const std::string &word2 )
{
    if ( word1.size() != word2.size() ) return -1;

    int res = -1;

    for ( size_t i = 0; i < word1.size(); ++i )
    {
        if ( word1[ i ] == word2[ i ] )
            continue;
        if ( res != -1 )
            return -1;
        res = i;
    }

    return res;
}

/* Find good key positions.  */
static
std::set< int > find_positions ( const Keywords &keywords )
{
  /* 1. Find positions that must occur in order to distinguish duplicates.  */
  std::set< int > mandatory;

  for ( size_t i = 0; i < keywords.size(); ++i )
  {
    for ( size_t j = i + 1; j < keywords.size(); ++j )
    {
      int idx = only_diff_idx( keywords[ i ], keywords[ j ] );

      if ( idx != -1 && (size_t)idx != keywords[ i ].size() - 1 )
      {
        mandatory.insert( idx );
      }
    }
  }

  /* 2. Add positions, as long as this decreases the duplicates count.  */
  int imax = std::min( keywords.max_size() - 1, size_t( 254 ) );
  std::set< int > current = mandatory;
  unsigned int current_duplicates_count = count_duplicates ( keywords, current );
  for (;;)
    {
      std::set< int > best;
      unsigned int best_duplicates_count = UINT_MAX;

      for (int i = imax; i >= -1; i--)
        if (!current.count (i))
          {
            std::set< int > tryal = current;
            tryal.insert (i);
            unsigned int try_duplicates_count = count_duplicates ( keywords, tryal);

            /* We prefer 'try' to 'best' if it produces less duplicates,
               or if it produces the same number of duplicates but with
               a more efficient hash function.  */
            if (try_duplicates_count < best_duplicates_count
                || (try_duplicates_count == best_duplicates_count && i >= 0))
              {
                best = tryal;
                best_duplicates_count = try_duplicates_count;
              }
          }

      /* Stop adding positions when it gives no improvement.  */
      if (best_duplicates_count >= current_duplicates_count)
        break;

      current = best;
      current_duplicates_count = best_duplicates_count;
    }

  /* 3. Remove positions, as long as this doesn't increase the duplicates
     count.  */
  for (;;)
    {
      std::set< int > best;
      unsigned int best_duplicates_count = UINT_MAX;

      for (int i = imax; i >= -1; i--)
        if (current.count (i) && !mandatory.count (i))
          {
            std::set< int > tryal = current;
            tryal.erase (i);
            unsigned int try_duplicates_count = count_duplicates ( keywords, tryal);

            /* We prefer 'try' to 'best' if it produces less duplicates,
               or if it produces the same number of duplicates but with
               a more efficient hash function.  */
            if (try_duplicates_count < best_duplicates_count
                || (try_duplicates_count == best_duplicates_count && i == -1))
              {
                best = tryal;
                best_duplicates_count = try_duplicates_count;
              }
          }

      /* Stop removing positions when it gives no improvement.  */
      if (best_duplicates_count > current_duplicates_count)
        break;

      current = best;
      current_duplicates_count = best_duplicates_count;
    }

  /* 4. Replace two positions by one, as long as this doesn't increase the
     duplicates count.  */
  for (;;)
    {
      std::set< int > best;
      unsigned int best_duplicates_count = UINT_MAX;

      for (int i1 = imax; i1 >= -1; i1--)
        if (current.count (i1) && !mandatory.count (i1))
          {
            for (int i2 = imax; i2 >= -1; i2--)
              if (current.count (i2) && !mandatory.count (i2) && i2 != i1)
                {
                  for (int i3 = imax; i3 >= 0; i3--)
                    if (!current.count (i3))
                      {
                        std::set< int > tryal = current;
                        tryal.erase (i1);
                        tryal.erase (i2);
                        tryal.insert (i3);
                        unsigned int try_duplicates_count = count_duplicates (keywords, tryal);

                        /* We prefer 'try' to 'best' if it produces less
                           duplicates, or if it produces the same number
                           of duplicates but with a more efficient hash
                           function.  */
                        if (try_duplicates_count < best_duplicates_count
                            || (try_duplicates_count == best_duplicates_count
                                && (i1 == -1 || i2 == -1 || i3 >= 0)))
                          {
                            best = tryal;
                            best_duplicates_count = try_duplicates_count;
                          }
                      }
                }
          }

      /* Stop removing positions when it gives no improvement.  */
      if (best_duplicates_count > current_duplicates_count)
        break;

      current = best;
      current_duplicates_count = best_duplicates_count;
    }

  /* That's it.  Hope it's good enough.  */
  return current;
}

/* ===================== Finding good alpha increments ===================== */

/* Count the duplicate keywords that occur with the given set of positions
   and a given alpha_inc[] array.
   In other words, it returns the difference
     # K - # proj2 (proj1 (K))
   where K is the multiset of given keywords.  */
static
size_t count_duplicates_multiset( const Keywords &keywords,
                                  const std::set< int > &key_positions,
                                  const std::vector< int > &alpha_inc )
{
  /* Run through the keyword list and count the duplicates incrementally.
     The result does not depend on the order of the keyword list, thanks to
     the formula above.  */

  std::unordered_set< Chars > representatives;

  for ( const std::string &kw : keywords )
  {
     representatives.emplace( selchars( kw, key_positions, alpha_inc ) );
  }

  return keywords.size() - representatives.size();
}

static
std::vector< int > find_alpha_inc( const Keywords &keywords,
                                   const std::set< int > &key_positions )
{
  /* The goal is to choose _alpha_inc[] such that it doesn't introduce
     artificial duplicates.
     In other words, the goal is  # proj2 (proj1 (K)) = # proj1 (K).  */
  size_t duplicates_goal = count_duplicates ( keywords, key_positions);

  /* Start with zero increments.  This is sufficient in most cases.  */
  std::vector< int > current( keywords.max_size(), 0 );

  size_t current_duplicates_count = count_duplicates_multiset ( keywords, key_positions, current);

  if (current_duplicates_count > duplicates_goal)
    {
      /* Look which _alpha_inc[i] we are free to increment.  */
      std::vector< int > indices( key_positions.rbegin(), key_positions.rend() );
      if ( indices.back() == -1 )
      {
        indices.pop_back();
      }

      /* Perform several rounds of searching for a good alpha increment.
         Each round reduces the number of artificial collisions by adding
         an increment in a single key position.  */
      while (current_duplicates_count > duplicates_goal)
        {
          /* An increment of 1 is not always enough.  Try higher increments
             also.  */
          for ( size_t inc = 1; ; inc++)
            {
              std::vector< int > best( keywords.max_size() );
              size_t best_duplicates_count = UINT_MAX;

              for ( int idx : indices )
                {
                  std::vector< int > tryal( current );
                  tryal[ idx ] += inc;

                  size_t try_duplicates_count = count_duplicates_multiset( keywords, key_positions, tryal );

                  /* We prefer 'try' to 'best' if it produces less
                     duplicates.  */
                  if (try_duplicates_count < best_duplicates_count)
                    {
                      best = tryal;
                      best_duplicates_count = try_duplicates_count;
                    }
                }

              /* Stop this round when we got an improvement.  */
              if (best_duplicates_count < current_duplicates_count)
                {
                  current = best;
                  current_duplicates_count = best_duplicates_count;
                  break;
                }
            }
        }
    }

  return current;
}

/* Finds some _asso_values[] that fit.  */

/* The idea is to choose the _asso_values[] one by one, in a way that
   a choice that has been made never needs to be undone later.  This
   means that we split the work into several steps.  Each step chooses
   one or more _asso_values[c].  The result of choosing one or more
   _asso_values[c] is that the partitioning of the keyword set gets
   broader.
   Look at this partitioning:  After every step, the _asso_values[] of a
   certain set C of characters are undetermined.  (At the beginning, C
   is the set of characters c with occurrences[c] > 0.  At the end, C
   is empty.)  To each keyword K, we associate the multiset of _selchars
   for which the _asso_values[] are undetermined:
                    K  -->  K->_selchars intersect C.
   Consider two keywords equivalent if their value under this mapping is
   the same.  This introduces an equivalence relation on the set of
   keywords.  The equivalence classes partition the keyword set.  (At the
   beginning, the partition is the finest possible: each K is an equivalence
   class by itself, because all K have a different _selchars.  At the end,
   all K have been merged into a single equivalence class.)
   The partition before a step is always a refinement of the partition
   after the step.
   We choose the steps in such a way that the partition really becomes
   broader at each step.  (A step that only chooses an _asso_values[c]
   without changing the partition is better merged with the previous step,
   to avoid useless backtracking.)  */

struct EquivalenceClass
{
  EquivalenceClass() = default;
  EquivalenceClass( EquivalenceClass&& ) = default;
  EquivalenceClass& operator=( EquivalenceClass&& ) = default;

  // Map from undetermined chars to keyword set
  std::unordered_map< Chars, std::vector< std::string > > m_map;
};

struct Step
{
  /* The characters whose values are being determined in this step.  */
  std::vector< unsigned int > _changing;
  /* Exclusive upper bound for the _asso_values[c] of this step.
     A power of 2.  */
  unsigned int          _asso_value_max;
  /* The characters whose values will be determined after this step.  */
  std::vector< bool >   _undetermined;
  /* The keyword set partition after this step.  */
  EquivalenceClass    _partition;
  /* The expected number of iterations in this step.  */
  double                _expected_lower;
  double                _expected_upper;
};

static
EquivalenceClass compute_partition ( const Keywords &keywords, std::vector< bool > &undetermined,
                                     const std::set< int > &positions, const std::vector< int > &alpha_inc )
{
  EquivalenceClass partition;

  for ( const std::string &keyword : keywords )
    {
      /* Compute the undetermined characters for this keyword.  */
      std::vector< int > undetermined_chars;

      for ( int ch : selchars( keyword, positions, alpha_inc ) )
        if ( undetermined[ ch ] )
          undetermined_chars.push_back( ch );

      partition.m_map[ Chars( 0, std::move( undetermined_chars ) ) ].push_back( keyword );
    }

  return partition;
}

/* Compute the possible number of collisions when _asso_values[c] is
   chosen, leading to the given partition.  */
static
size_t count_possible_collisions( const std::set< int > &key_positions,
                                  const std::vector< int > &alpha_inc,
                                  const EquivalenceClass &partition,
                                  unsigned int c )
{
  /* Every equivalence class p is split according to the frequency of
     occurrence of c, leading to equivalence classes p1, p2, ...
     This leads to   (|p|^2 - |p1|^2 - |p2|^2 - ...)/2  possible collisions.
     Return the sum of this expression over all equivalence classes.  */
  unsigned int sum = 0;
  unsigned int m = key_positions.size();

  for ( const auto &it : partition.m_map )
    {
      std::vector< unsigned int > split_cardinalities( m + 1, 0 );

      for ( const std::string &keyword : it.second )
        split_cardinalities[ selchars( keyword, key_positions, alpha_inc ).count( c ) ]++;

      sum += it.second.size() * it.second.size();
      for (unsigned int i = 0; i <= m; i++)
        sum -= split_cardinalities[i] * split_cardinalities[i];
    }

  return sum;
}

/* Test whether adding c to the undetermined characters changes the given
   partition.  */
static
bool unchanged_partition( const std::set< int > &key_positions,
                          const std::vector< int > &alpha_inc,
                          const EquivalenceClass &partition,
                          unsigned int c )
{
  for ( const auto &it : partition.m_map )
    {
      unsigned int first_count = UINT_MAX;

      for ( const std::string &keyword : it.second )
        {
          unsigned int count = selchars( keyword, key_positions, alpha_inc ).count( c );

          if (first_count == UINT_MAX )
            first_count = count;
          else if (count != first_count)
            /* c would split this equivalence class.  */
            return false;
        }
    }
  return true;
}

static
std::tuple< std::vector< int >, unsigned int, int >
find_asso_values( const Keywords &keywords,
                  size_t alpha_size,
                  const std::set< int > &key_positions,
                  const std::vector< int > &alpha_inc,
                  int jump,
                  const std::vector< int > &occurrences,
                  unsigned int asso_value_max,
                  int initial_asso_value,
                  int max_hash_value )
{
  // The value given here matters only for those c which occur in all keywords with equal multiplicity.
  std::vector< int > asso_values( alpha_size, 0 );

  std::list< Step > steps;

  /* Determine the steps, starting with the last one.  */
  {
    std::vector< bool > undetermined( alpha_size, false );
    std::vector< bool > determined( alpha_size, true );

    for (;;)
      {
        /* Compute the partition that needs to be refined.  */
        EquivalenceClass partition = compute_partition ( keywords, undetermined, key_positions, alpha_inc );

        /* Determine the main character to be chosen in this step.
           Choosing such a character c has the effect of splitting every
           equivalence class (according the the frequency of occurrence of c).
           We choose the c with the minimum number of possible collisions,
           so that characters which lead to a large number of collisions get
           handled early during the search.  */
        unsigned int chosen_c;
        double chosen_possible_collisions;
        {
          unsigned int best_c = 0;
          unsigned int best_possible_collisions = UINT_MAX;
          for (unsigned int c = 0; c < alpha_size; c++)
            if (occurrences[c] > 0 && determined[c])
              {
                unsigned int possible_collisions = count_possible_collisions ( key_positions, alpha_inc, partition, c );
                if (possible_collisions < best_possible_collisions)
                  {
                    best_c = c;
                    best_possible_collisions = possible_collisions;
                  }
              }
          if (best_possible_collisions == UINT_MAX)
            {
              /* All c with occurrences[c] > 0 are undetermined.  We are
                 are the starting situation and don't need any more step.  */
              break;
            }
          chosen_c = best_c;
          chosen_possible_collisions = best_possible_collisions;
        }

        /* We need one more step.  */
        Step &step = steps.emplace_front();
        step._undetermined = undetermined;
        step._partition = std::move( partition );

        /* Now determine how the equivalence classes will be before this
           step.  */
        undetermined[chosen_c] = true;
        partition = compute_partition ( keywords, undetermined, key_positions, alpha_inc );

        /* Now determine which other characters should be determined in this
           step, because they will not change the equivalence classes at
           this point.  It is the set of all c which, for all equivalence
           classes, have the same frequency of occurrence in every keyword
           of the equivalence class.  */
        for (unsigned int c = 0; c < alpha_size; c++)
          if (occurrences[c] > 0 && determined[c]
              && unchanged_partition ( key_positions, alpha_inc, partition, c))
            {
              undetermined[c] = true;
              determined[c] = false;
            }

        /* main_c must be one of these.  */
        if (determined[chosen_c])
          abort ();

        /* Now the set of changing characters of this step.  */
        unsigned int changing_count;

        changing_count = 0;
        for (unsigned int c = 0; c < alpha_size; c++)
          if (undetermined[c] && !step._undetermined[c])
            changing_count++;

        std::vector< unsigned int > changing( changing_count );
        changing_count = 0;
        for (unsigned int c = 0; c < alpha_size; c++)
          if (undetermined[c] && !step._undetermined[c])
            changing[changing_count++] = c;

        step._changing = changing;
        step._asso_value_max = asso_value_max;
        step._expected_lower = exp( chosen_possible_collisions / max_hash_value );
        step._expected_upper = exp( chosen_possible_collisions / asso_value_max );
      }
  }

  unsigned int stepno = 0;
  for ( Step &step : steps )
    {
      stepno++;

      /* Initialize the asso_values[].  */
      unsigned int k = step._changing.size();
      for (unsigned int i = 0; i < k; i++)
        {
          unsigned int c = step._changing[i];
          asso_values[c] =
            (initial_asso_value < 0 ? rand () : initial_asso_value)
            & (step._asso_value_max - 1);
        }

      unsigned int iterations = 0;
      std::vector< unsigned int > iter( k );
      for (unsigned int i = 0; i < k; i++)
        iter[i] = 0;
      unsigned int ii = (jump != 0 ? k - 1 : 0);

      for (;;)
        {
          /* Test whether these asso_values[] lead to collisions among
             the equivalence classes that should be collision-free.  */
          bool has_collision = false;
          for ( const auto &it : step._partition.m_map )
            {
              std::vector< bool > collision_detector( max_hash_value + 1, false );

              for ( const std::string &keyword : it.second )
                {
                  /* Compute the new hash code for the keyword, leaving apart
                     the yet undetermined asso_values[].  */
                  int hashcode;
                  {
                    hashcode = keyword.size();

                    for ( int ch : selchars( keyword, key_positions, alpha_inc ) )
                      if (!step._undetermined[ch])
                        hashcode += asso_values[ch];
                  }

                  /* See whether it collides with another keyword's hash code,
                     from the same equivalence class.  */
                  if ( collision_detector[ hashcode ] )
                    {
                      has_collision = true;
                      break;
                    }
                  else
                    collision_detector[ hashcode ] = true;
                }

              /* Don't need to continue looking at the other equivalence
                 classes if we already have found a collision.  */
              if (has_collision)
                break;
            }

          iterations++;
          if (!has_collision)
            break;

          /* Try other asso_values[].  */
          if (jump != 0)
            {
              /* The way we try various values for
                   asso_values[step._changing[0],...step._changing[k-1]]
                 is like this:
                 for (bound = 0,1,...)
                   for (ii = 0,...,k-1)
                     iter[ii] := bound
                     iter[0..ii-1] := values <= bound
                     iter[ii+1..k-1] := values < bound
                 and
                   asso_values[step._changing[i]] =
                     initial_asso_value + iter[i] * jump.
                 This makes it more likely to find small asso_values[].
               */
              unsigned int bound = iter[ii];
              unsigned int i = 0;
              while (i < ii)
                {
                  unsigned int c = step._changing[i];
                  iter[i]++;
                  asso_values[c] =
                    (asso_values[c] + jump) & (step._asso_value_max - 1);
                  if (iter[i] <= bound)
                    goto found_next;
                  asso_values[c] =
                    (asso_values[c] - iter[i] * jump)
                    & (step._asso_value_max - 1);
                  iter[i] = 0;
                  i++;
                }
              i = ii + 1;
              while (i < k)
                {
                  unsigned int c = step._changing[i];
                  iter[i]++;
                  asso_values[c] =
                    (asso_values[c] + jump) & (step._asso_value_max - 1);
                  if (iter[i] < bound)
                    goto found_next;
                  asso_values[c] =
                    (asso_values[c] - iter[i] * jump)
                    & (step._asso_value_max - 1);
                  iter[i] = 0;
                  i++;
                }
              /* Switch from one ii to the next.  */
              {
                unsigned int c = step._changing[ii];
                asso_values[c] =
                  (asso_values[c] - bound * jump)
                  & (step._asso_value_max - 1);
                iter[ii] = 0;
              }
              /* Here all iter[i] == 0.  */
              ii++;
              if (ii == k)
                {
                  ii = 0;
                  bound++;
                  if (bound == step._asso_value_max)
                    {
                      /* Out of search space!  We can either backtrack, or
                         increase the available search space of this step.
                         It seems simpler to choose the latter solution.  */
                      step._asso_value_max = 2 * step._asso_value_max;
                      if (step._asso_value_max > asso_value_max)
                        {
                          asso_value_max = step._asso_value_max;
                          /* Reinitialize max_hash_value.  */
                          max_hash_value =
                            keywords.max_size()
                            + (asso_value_max - 1) * key_positions.size();
                        }
                    }
                }
              {
                unsigned int c = step._changing[ii];
                iter[ii] = bound;
                asso_values[c] =
                  (asso_values[c] + bound * jump)
                  & (step._asso_value_max - 1);
              }
             found_next: ;
            }
          else
            {
              /* Random.  */
              unsigned int c = step._changing[ii];
              asso_values[c] =
                (asso_values[c] + rand ()) & (step._asso_value_max - 1);
              /* Next time, change the next c.  */
              ii++;
              if (ii == k)
                ii = 0;
            }
        }
    }

  return std::make_tuple( std::move( asso_values ), asso_value_max, max_hash_value );
}

void
Search::find_good_asso_values ()
{
    // Computes a keyword's hash value, relative to the current _asso_values[],
    auto compute_hash = [ this ]( const std::string &keyword ) -> int
    {
        int sum = keyword.size();

        for ( int ch : selchars( keyword, _key_positions, _alpha_inc ) )
            sum += _asso_values[ch];

        return sum;
    };

  // Check for duplicates, i.e. keywords with the same _selchars array
  //  (and - if _hash_includes_len - also the same length).
  {
    std::unordered_set< Chars > representatives;

    for ( const std::string &keyword : m_keywords )
      {
        auto [ it, inserted ] = representatives.emplace ( selchars( keyword, _key_positions, _alpha_inc ) );
        (void)it;

        if ( !inserted )
        {
          std::cerr << "Duplicate Keyword found: " << keyword << "\n";
          std::exit( 1 ) ;
        }
      }
  }

  /* Compute the occurrences of each character in the alphabet.  */
  std::vector< int > occurrences( _asso_values.size(), 0 );
  for ( const std::string &keyword : m_keywords )
    {
      for ( int ch : selchars( keyword, _key_positions, _alpha_inc ) )
        occurrences[ch]++;
    }

  /* Round up to the next power of two.  This makes it easy to ensure
     an _asso_value[c] is >= 0 and < asso_value_max.  Also, the jump value
     being odd, it guarantees that Search::try_asso_value() will iterate
     through different values for _asso_value[c].  */
  unsigned int asso_value_max = next_power_of_2( m_keywords.size() );

  /* Given the bound for _asso_values[c], we have a bound for the possible
     hash values, as computed in compute_hash().  */
  int _max_hash_value = m_keywords.max_size()
                    + (asso_value_max - 1) * _key_positions.size();




  /* Search for good _asso_values[].  */
  int asso_iteration = 1; // TODO this can be increased to find possibly better asso_values

  /* Try different pairs of initial_asso_value and jump, in th const;
     following order:
       (0, 1)
       (1, 1)
       (2, 1) (0, 3)
       (3, 1) (1, 3)
       (4, 1) (2, 3) (0, 5)
       (5, 1) (3, 3) (1, 5)
       ..... */
  auto saved_keywords = m_keywords;
  int best_initial_asso_value = 0;
  int best_jump = 1;
  std::vector< int > best_asso_values( _asso_values.size() );
  int best_collisions = INT_MAX;
  int best_max_hash_value = INT_MAX;

  int initial_asso_value = 0;
  int jump = 1;
  for (;;)
    {
      /* Restore the keyword list in its original order.  */
      m_keywords = saved_keywords;

      std::tie( _asso_values, asso_value_max, _max_hash_value ) = find_asso_values(
          m_keywords, _asso_values.size(), _key_positions, _alpha_inc, jump, occurrences, asso_value_max, initial_asso_value, _max_hash_value );

      /* Test whether it is the best solution so far.  */
      int collisions = 0;
      int max_hash_value = INT_MIN;
      std::vector< bool > collision_detector( _max_hash_value + 1, false );

      for ( const std::string &keyword : m_keywords )
        {
          int hashcode = compute_hash (keyword);
          if (max_hash_value < hashcode)
            max_hash_value = hashcode;
          if (collision_detector[hashcode])
            collisions++;
          collision_detector[ hashcode ] = true;
        }
      if (collisions < best_collisions
          || (collisions == best_collisions
              && max_hash_value < best_max_hash_value))
        {
          best_asso_values = _asso_values;
          best_collisions = collisions;
          best_max_hash_value = max_hash_value;
        }

      if (--asso_iteration == 0)
        break;
      /* Prepare for next iteration.  */
      if (initial_asso_value >= 2)
      {
        initial_asso_value -= 2;
         jump += 2;
      }
      else
      {
        initial_asso_value += jump;
         jump = 1;
        }
    }
  m_keywords = saved_keywords;
  /* Install the best found asso_values.  */
  initial_asso_value = best_initial_asso_value;
  jump = best_jump;
  _asso_values = best_asso_values;

  // finalize
  {
  for ( const std::string &word : m_keywords )
    word_map[ compute_hash( word ) ] = word;

  /* Set unused asso_values[c] to max_hash_value + 1.  This is not absolutely
     necessary, but speeds up the lookup function in many cases of lookup
     failure: no string comparison is needed once the hash value of a string
     is larger than the hash value of any keyword.  */
  int max_hash_value = word_map.rbegin()->first;

  for (unsigned int c = 0; c < _asso_values.size(); c++)
    if (occurrences[c] == 0)
      _asso_values[c] = max_hash_value + 1;
  }
}

/* ========================================================================= */

void
Search::optimize ()
{
  /* Step 1: Finding good byte positions.  */
  _key_positions = find_positions ( m_keywords );

  /* Step 2: Finding good alpha increments.  */
  _alpha_inc = find_alpha_inc( m_keywords, _key_positions );
  _asso_values.resize( 256 + *std::max_element( _alpha_inc.begin(), _alpha_inc.end() ) );

  /* Step 3: Finding good asso_values.  */
  find_good_asso_values ();
}

PerfectHash GeneratePerfectHash( std::vector< std::string > words )
{
    Search searcher ( Keywords( std::move( words ) ) );
    searcher.optimize ();
    return searcher.get_solution();
}
