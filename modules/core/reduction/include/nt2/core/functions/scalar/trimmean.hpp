//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_TRIMMEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_TRIMMEAN_HPP_INCLUDED

#include <nt2/core/functions/trimmean.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_real.hpp>

//TODO include complex cases
namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( trimmean_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a) const
    {
      return a;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( trimmean_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> > )
                              (scalar_< integer_<A1>  > )
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const &) const
    {
      return a;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( trimmean_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< unspecified_<A0> > )
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const &
                                            , A2 const &) const
    {
      return a;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( trimmean_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_< unspecified_<A0> > )
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const &
                                            , A2 const &, A3 const &) const
    {
      return a;
    }
  };


} }

#endif