//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE2_IS_LEZ_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE2_IS_LEZ_HPP_INCLUDED
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/is_eqz.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_lez_, tag::cpu_, (A0)
                            , ((simd_<arithmetic_<A0>,tag::sse_>))
                          )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1) { return le(a0,Zero<A0>()); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::is_lez_, tag::cpu_, (A0)
                            , ((simd_<unsigned_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1) { return is_eqz(a0); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::is_lez_, tag::cpu_, (A0)
                            , ((simd_<int64_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return is_less(a0, Zero<A0>()); //TO DO
//       typedef typename meta::int32_t_<A0>::type htype;
//       typedef simd::native<htype,tag::sse_> type;
//       const type tmp1 = is_lez(simd::native_cast<type>(a0));
//       const type tmp = { _mm_shuffle_epi32(tmp1, _MM_SHUFFLE(2, 2, 0, 0))};
//       return  simd::native_cast<A0>(tmp);
    }
  };
} }

#endif
