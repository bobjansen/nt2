//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/predicates/include/functions/is_equal_with_equal_nans.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/mzero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/quarter.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL(is_equal_with_equal_nans_real, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::is_equal_with_equal_nans;
  using boost::simd::tag::is_equal_with_equal_nans_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<is_equal_with_equal_nans_(vT,vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::True<r_t>());
#endif
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Mzero<vT>(), boost::simd::Mzero<vT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Half<vT>(), boost::simd::Half<vT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Quarter<vT>(), boost::simd::Quarter<vT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Two<vT>(), boost::simd::Two<vT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::True<r_t>());
}

NT2_TEST_CASE_TPL(is_equal_with_equal_nans_ui, BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::is_equal_with_equal_nans;
  using boost::simd::tag::is_equal_with_equal_nans_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<is_equal_with_equal_nans_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Two<vT>(), boost::simd::Two<vT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::True<r_t>());
}

NT2_TEST_CASE_TPL(is_equal_with_equal_nans_si, BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::is_equal_with_equal_nans;
  using boost::simd::tag::is_equal_with_equal_nans_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<is_equal_with_equal_nans_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Two<vT>(), boost::simd::Two<vT>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_equal_with_equal_nans(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::True<r_t>());
}
