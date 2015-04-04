//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
#include <nt2/include/functions/dcsum.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/cast.hpp>

#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL( dcsum_scalar, NT2_REAL_TYPES )
{
  T x = nt2::dcsum(T(42));
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::dcsum(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::dcsum(T(42),0);
  NT2_TEST_EQUAL( x, T(42) );

}

NT2_TEST_CASE_TPL( dcsum, NT2_REAL_TYPES )
{
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy;
  nt2::table<T> sy2;

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = (6-i) + 10*(4-j);

  sy = nt2::sum(y);
  sy2 = nt2::dcsum(y);
  NT2_TEST_EQUAL(sy, sy2);

  sy = nt2::sum(y, 2);
  sy2 = nt2::dcsum(y, 2);
  NT2_TEST_EQUAL(sy, sy2);


}

NT2_TEST_CASE_TPL( dcsum2, (float) )
{
  nt2::table<T> y( nt2::of_size(500,300) );
  nt2::table<T> sy;
  nt2::table<T> sy2;
  nt2::table<T> sy1;

  for(int j=1;j<=300;j++)
    for(int i=1;i<=500;i++)
      y(i,j) = nt2::abs(nt2::cos(T(i + 10*j)));

  nt2::table<double> y1 = nt2::cast<double>(y);
  sy = nt2::sum(y);
  sy1= nt2::cast<T>(nt2::sum(y1));
  sy2 = nt2::dcsum(y);
  NT2_TEST_ULP_EQUAL(sy2, sy1, 0.5);

  sy = nt2::sum(y, 2);
  sy1= nt2::cast<T>(nt2::sum(y1, 2));
  sy2 = nt2::dcsum(y, 2);
  NT2_TEST_ULP_EQUAL(sy2, sy1, 0.5);
}

NT2_TEST_CASE_TPL( dcsum2s, (float) )
{
  nt2::table<T> y( nt2::of_size(500,300) );
  nt2::table<T> sy;
  nt2::table<T> sy2;
  nt2::table<T> sy1;

  for(int j=1;j<=300;j++)
    for(int i=1;i<=500;i++)
      y(i,j) = nt2::abs(nt2::cos(T(i + 10*j)));

  nt2::table<double> y1 = nt2::cast<double>(y);
  sy = nt2::sum(y);
  sy1= nt2::cast<T>(nt2::sum(y1));
  sy2 = nt2::dcsum(y, nt2::sort_);
  NT2_TEST_ULP_EQUAL(sy2, sy1, 0.5);

  sy = nt2::sum(y, 2);
  sy1= nt2::cast<T>(nt2::sum(y1, 2));
  sy2 = nt2::dcsum(y, nt2::sort_, 2);
  NT2_TEST_ULP_EQUAL(sy2, sy1, 0.5);
}

NT2_TEST_CASE_TPL( dcsumc, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> y( nt2::of_size(5,3) );
  nt2::table<cT> sy;
  nt2::table<cT> sy2;

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = cT(T((6-i) + 10*(4-j)), T(j-i));

  sy = nt2::sum(y);
  sy2 = nt2::dcsum(y);
  NT2_TEST_EQUAL(sy, sy2);

  sy = nt2::sum(y, 2);
  sy2 = nt2::dcsum(y, 2);
  NT2_TEST_EQUAL(sy, sy2);
}
