//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 polynomials toolbox - legendre/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynomials components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/polynomials/include/functions/legendre.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>


NT2_TEST_CASE_TPL ( legendre_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::legendre;
  using nt2::tag::legendre_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<legendre_(iT,T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Half<T>()), nt2::Half<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Inf<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Minf<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Nan<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::One<T>()), nt2::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
} // end of test for floating_

NT2_TEST_CASE_TPL ( legendre_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::legendre;
  using nt2::tag::legendre_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<legendre_(iT,T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::One<T>()), nt2::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( legendre_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::legendre;
  using nt2::tag::legendre_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<legendre_(iT,T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::One<T>()), nt2::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(legendre(1,nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
} // end of test for signed_int_
