//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Laprest�
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_BLAS2_TRSV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_BLAS2_TRSV_HPP_INCLUDED

#include <nt2/linalg/functions/blas_trsv.hpp>
#include <nt2/linalg/details/blas/blas2.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/sdk/memory/container.hpp>

namespace nt2 { namespace ext
{

// /---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_trsv_, tag::cpu_
                            , (UPLO)(TRANS)(DIAG)(A)(SA)(X)(SX)(INCX)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<int8_<DIAG>>)//diag
                              ((container_<nt2::tag::table_,  single_<A>, SA >)) //a
                              ((container_<nt2::tag::table_,  single_<X>, SX >)) //x
                              (scalar_<integer_<INCX>>)// incx
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const DIAG& diag
                                     , const A& a
                                     , X& x, const INCX & incx
                                     ) const
    {
      nt2_la_int n = height(a);
      nt2_la_int lda = n;
      nt2_la_int ix= incx;
      NT2_F77NAME(strsv)  (&uplo, &trans, &diag, &n, a.raw(), &lda, x.raw(), &ix);
    }
  };

// /---------------------------------------------Real-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( blas_trsv_, tag::cpu_
                            , (UPLO)(TRANS)(DIAG)(A)(SA)(X)(SX)(INCX)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<int8_<DIAG>>)//diag
                              ((container_<nt2::tag::table_,  double_<A>, SA >)) //a
                              ((container_<nt2::tag::table_,  double_<X>, SX >)) //y
                              (scalar_<integer_<INCX>>)// incx
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const DIAG& diag
                                     , const A& a
                                     , X& x, const INCX & incx
                                     ) const
    {
      nt2_la_int n = height(a);
      nt2_la_int lda = n;
      nt2_la_int ix= incx;
      NT2_F77NAME(dtrsv) (&uplo, &trans, &diag, &n, a.raw(), &lda, x.raw(), &ix);
    }
  };



// /---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( blas_trsv_, tag::cpu_
                            , (UPLO)(TRANS)(DIAG)(A)(SA)(X)(SX)(INCX)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<int8_<DIAG>>)//diag
                              ((container_<nt2::tag::table_,  complex_<single_<A>>, SA >)) //a
                              ((container_<nt2::tag::table_,  complex_<single_<X>>, SX >)) //y
                              (scalar_<integer_<INCX>>)// incx
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const DIAG& diag
                                     , const A& a
                                     , X& x, const INCX & incx
                                     ) const
    {
      nt2_la_int n = height(a);
      nt2_la_int lda = n;
      nt2_la_int ix= incx;
      NT2_F77NAME(ctrsv) (&uplo, &trans, &diag, &n, a.raw(), &lda, x.raw(), &ix);
    }
  };

// /---------------------------------------------Complex-double------------------------------------------------//
  BOOST_DISPATCH_IMPLEMENT  ( blas_trsv_, tag::cpu_
                            , (UPLO)(TRANS)(DIAG)(A)(SA)(X)(SX)(INCX)
                            , (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<TRANS>>)// trans
                              (scalar_<int8_<DIAG>>)//diag
                              ((container_<nt2::tag::table_,  complex_<double_<A>>, SA >)) //a
                              ((container_<nt2::tag::table_,  complex_<double_<X>>, SX >)) //y
                              (scalar_<integer_<INCX>>)// incx
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE void operator()( const UPLO& uplo
                                     , const TRANS& trans
                                     , const DIAG& diag
                                     , const A& a
                                     , X& x, const INCX & incx
                                     ) const
    {
      nt2_la_int n = height(a);
      nt2_la_int lda = n;
      nt2_la_int ix= incx;
      NT2_F77NAME(ztrsv) (&uplo, &trans, &diag, &n, a.raw(), &lda, x.raw(), &ix);
    }
  };


} }

#endif