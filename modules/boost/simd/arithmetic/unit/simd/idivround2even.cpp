//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - idivround2even/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
///
#include <boost/simd/arithmetic/include/functions/idivround2even.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/iround2even.hpp>
#include <boost/simd/include/functions/tofloat.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( idivround2even_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::idivround2even;
  using boost::simd::tag::idivround2even_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<idivround2even_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(idivround2even(boost::simd::Inf<vT>(), boost::simd::Inf<vT>())[0], boost::simd::Zero<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround2even(boost::simd::Minf<vT>(), boost::simd::Minf<vT>())[0], boost::simd::Zero<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround2even(boost::simd::Mone<vT>(), boost::simd::Mone<vT>())[0], boost::simd::One<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround2even(boost::simd::Nan<vT>(), boost::simd::Nan<vT>())[0], boost::simd::Zero<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround2even(boost::simd::One<vT>(), boost::simd::One<vT>())[0], boost::simd::One<sr_t>(), 0);
} // end of test for floating_


NT2_TEST_CASE_TPL ( idivround2even_unsigned_int__2_0,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::idivround2even;
  using boost::simd::tag::idivround2even_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<idivround2even_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef ivT wished_r_t;

  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );

  // specific values tests
  NT2_TEST_ULP_EQUAL(idivround2even(boost::simd::One<vT>(), boost::simd::One<vT>())[0], boost::simd::One<iT>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( idivround2even_signed_int__2_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::idivround2even;
  using boost::simd::tag::idivround2even_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<idivround2even_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef ivT wished_r_t;
  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );

  // specific values tests
  NT2_TEST_ULP_EQUAL(idivround2even(boost::simd::Mone<vT>(), boost::simd::Mone<vT>())[0], boost::simd::One<iT>(), 0);
  NT2_TEST_ULP_EQUAL(idivround2even(boost::simd::One<vT>(), boost::simd::One<vT>())[0], boost::simd::One<iT>(), 0);
} // end of test for signed_int_
