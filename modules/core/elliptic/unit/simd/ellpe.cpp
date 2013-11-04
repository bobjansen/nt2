//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/elliptic/include/functions/ellpe.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( ellpe_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::ellpe;
  using nt2::tag::ellpe_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename nt2::meta::call<ellpe_(vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(ellpe(nt2::Pio_2<vT>()), nt2::Nan<r_t>(), 0.5);
#endif
  NT2_TEST_TYPE_IS(r_t, wished_r_t);
  NT2_TEST_TYPE_IS(r_t, wished_r_t);
  NT2_TEST_ULP_EQUAL(ellpe(nt2::One<vT>()), nt2::Pio_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(ellpe(nt2::Zero<vT>()), nt2::One<r_t>(), 0.5);
}
