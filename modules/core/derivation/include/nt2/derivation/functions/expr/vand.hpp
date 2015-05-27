//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_FUNCTIONS_EXPR_VAND_HPP_INCLUDED
#define NT2_DERIVATION_FUNCTIONS_EXPR_VAND_HPP_INCLUDED

#include <nt2/derivation/functions/vand.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/tocomplex.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/inveps.hpp>
#include <nt2/derivation/options.hpp>

namespace nt2 { namespace ext
{
 BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1, nt2::tag::vand_, N
                                      , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0&                                 result_type;
    typedef typename A0::value_type                  type_t;
    typedef typename meta::as_complex<type_t>::type ctype_t;
    typedef typename meta::as_real<type_t>::type    rtype_t;

    result_type operator()(A0& out, const A1& in ) const
    {
      auto x = boost::proto::child_c<1>(in);
      auto f =  boost::proto::value(boost::proto::child_c<0>(in));
      std::size_t nbcoefs = height(x); // number of coefficients in an input f vector
      std::size_t nbvec = width(x);    // number of f input vectors
      auto x1 = reshape(x, nbcoefs, 1, nbvec);
      auto e = nt2::Eps<rtype_t>()*nt2::eye(nbcoefs, nbcoefs, 1, nt2::meta::as_<rtype_t>());
      auto xc =  sx(nt2::tag::tocomplex_(),x1, e);
      out = reshape(imag(f(xc)*Inveps<rtype_t>()), _(), nbcoefs, nbvec);
      return out;
    }
  };

} }

#endif
