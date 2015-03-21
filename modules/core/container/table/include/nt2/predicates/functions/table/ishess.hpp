//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_TABLE_ISHESS_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_TABLE_ISHESS_HPP_INCLUDED

#include <nt2/predicates/functions/ishess.hpp>
#include <nt2/include/functions/last_index.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/is_nez.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( ishess_, tag::cpu_
                              , (A0)
                              , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0) const
    {
      for(std::ptrdiff_t j=first_index<2>(a0); j <= last_index<2>(a0) ; ++j)
      {
        for(std::ptrdiff_t i=j+2; i <= last_index<1>(a0) ; ++i)
        {
          if(is_nez(a0(i, j))) return false;
        }
      }
      return true;
    }
  };
} }

#endif
