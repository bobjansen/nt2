//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_UTILITY_ASSERT_HPP_INCLUDED
#define NT2_LINALG_DETAILS_UTILITY_ASSERT_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>

namespace nt2
{
  /**
    @brief Low level LAPACK assert
  **/

  BOOST_FORCEINLINE void lapack_assert(const nt2_la_int & info)
  {
    boost::dispatch::ignore_unused(info);
    BOOST_ASSERT_MSG(info == 0, "Assert lapack info is not zero");
  }

  template < class T >
  BOOST_FORCEINLINE void lapack_assert(const nt2_la_int & info, const T&)
  {
    boost::dispatch::ignore_unused(info);
    BOOST_ASSERT_MSG(info == 0, "lapack info is not zero");
  }
    /**/
}

#endif