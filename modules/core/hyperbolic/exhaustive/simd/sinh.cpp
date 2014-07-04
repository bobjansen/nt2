//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/constants/minlog.hpp>

#include <nt2/sdk/exhaustive/exhaustive.hpp>


#define NT2_ASSERTS_AS_TRAP
#include <nt2/sdk/error/assert_as_trap.hpp>
extern "C" { double cephes_sinh( double); }

#include <cmath>
#include <cstdlib>

struct raw_sinh
{
  float operator()(float x) const
  {
    return float(cephes_sinh(double(x)));
  }
};

int main(int argc, char* argv[])
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION             ext_t;
  typedef boost::simd::native<float,ext_t>           n_t;
  float mini = nt2::Minlog<float>();
  float maxi = nt2::Maxlog<float>();
  if(argc >= 2) mini = std::atof(argv[1]);
  if(argc >= 3) maxi = std::atof(argv[2]);

  nt2::exhaustive_test<n_t> ( mini
                            , maxi
                            , nt2::functor<nt2::tag::sinh_>()
                            , raw_sinh()
                            );

  return 0;
}
