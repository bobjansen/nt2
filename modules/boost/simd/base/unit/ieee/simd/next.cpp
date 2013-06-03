//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - next/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <boost/simd/ieee/include/functions/next.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/successor.hpp>
#include <boost/simd/include/constants/eps_related.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>


NT2_TEST_CASE_TPL ( next_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::next;
  using boost::simd::tag::next_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<next_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(next(boost::simd::Inf<vT>())[0], boost::simd::Inf<sr_t>());
  NT2_TEST_EQUAL(next(boost::simd::Minf<vT>())[0], boost::simd::Valmin<sr_t>());
  NT2_TEST_EQUAL(next(boost::simd::Mone<vT>())[0], boost::simd::Mone<sr_t>()+boost::simd::Eps<sr_t>()/2);
  NT2_TEST_EQUAL(next(boost::simd::Nan<vT>())[0], boost::simd::Nan<sr_t>());
  NT2_TEST_EQUAL(next(boost::simd::One<vT>())[0], boost::simd::One<sr_t>()+boost::simd::Eps<sr_t>());
  NT2_TEST_EQUAL(next(boost::simd::Valmax<vT>())[0], boost::simd::Inf<sr_t>());
  NT2_TEST_EQUAL(next(boost::simd::Zero<vT>())[0], boost::simd::Bitincrement<sr_t>());
} // end of test for real_

NT2_TEST_CASE_TPL ( next_unsigned_int__1_0,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::next;
  using boost::simd::tag::next_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<next_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;


  // specific values tests
  NT2_TEST_EQUAL(next(boost::simd::One<vT>())[0], boost::simd::Two<sr_t>());
  NT2_TEST_EQUAL(next(boost::simd::Valmax<vT>())[0], boost::simd::Valmax<sr_t>());
  NT2_TEST_EQUAL(next(boost::simd::Zero<vT>())[0], boost::simd::One<sr_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( next_signed_int__1_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::next;
  using boost::simd::tag::next_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<next_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(next(boost::simd::Mone<vT>())[0], boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(next(boost::simd::One<vT>())[0], boost::simd::Two<sr_t>());
  NT2_TEST_EQUAL(next(boost::simd::Valmax<vT>())[0], boost::simd::Valmax<sr_t>());
  NT2_TEST_EQUAL(next(boost::simd::Zero<vT>())[0], boost::simd::One<sr_t>());
} // end of test for signed_int_