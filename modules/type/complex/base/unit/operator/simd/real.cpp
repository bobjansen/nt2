//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/real.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( abs_cplx,  NT2_SIMD_REAL_TYPES)
{
  using nt2::real;
  using nt2::tag::real_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::dry<T>             dT;
  typedef native<dT,ext_t>                vdT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(nt2::real(nt2::Inf<vcT>()), nt2::Inf<vcT>());
  NT2_TEST_EQUAL(nt2::real(nt2::Minf<vcT>()), nt2::Minf<vcT>());
  NT2_TEST_EQUAL(nt2::real(nt2::Nan<vcT>()), nt2::Nan<vcT>());
  NT2_TEST_EQUAL(nt2::real(nt2::Inf<vdT>()), nt2::Inf<vcT>());
  NT2_TEST_EQUAL(nt2::real(nt2::Minf<vdT>()),nt2::Minf<vcT>());
  NT2_TEST_EQUAL(nt2::real(nt2::Nan<vdT>()), nt2::Nan<vcT>());
#endif
  NT2_TEST_EQUAL(nt2::real(nt2::splat<vcT>(cT(-1.1, -1.6))),nt2::splat<vT>(-1.1));
  NT2_TEST_EQUAL(nt2::real(nt2::Mone<vcT>()), nt2::Mone<vcT>());
  NT2_TEST_EQUAL(nt2::real(nt2::One<vcT>()), nt2::One<vcT>());
  NT2_TEST_EQUAL(nt2::real(nt2::Zero<vcT>()), nt2::Zero<vcT>());
  NT2_TEST_EQUAL(nt2::real(nt2::splat<vdT>(dT(-1.1))), nt2::splat<vT>(-1.1));
  NT2_TEST_EQUAL(nt2::real(nt2::splat<vdT>(dT(1.1))), nt2::splat<vT>(1.1));
  NT2_TEST_EQUAL(nt2::real(nt2::Mone<vdT>()),nt2::Mone<vdT>());
  NT2_TEST_EQUAL(nt2::real(nt2::One<vdT>()), nt2::One<vdT>());
  NT2_TEST_EQUAL(nt2::real(nt2::Zero<vdT>()), nt2::Zero<vdT>());
}

