//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_TWO_SPLIT_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_TWO_SPLIT_HPP_INCLUDED
#include <nt2/include/constants/properties.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::two_add_, tag::cpu_,
                             (A0)(A1),
                             (scalar_< real_<A0> >)(scalar_< real_<A1> >)
                            )
  {
    typedef typename meta::strip<A0>::type           stA0;
    typedef typename boost::fusion::tuple<stA0,stA0> result_type;

    NT2_FUNCTOR_CALL(1)
    {
      result_type res;
      eval(a0,boost::fusion::at_c<0>(res),boost::fusion::at_c<1>(res));
      return res;
    }
  private:
    template<class R0,class R1> inline void
    eval(A0 const& a,R0& r0, R1& r1)const
    {
      // TODO: make local constant ?
      static const int N = (Nbmantissabits<A0>()-(Nbmantissabits<A0>()>>1))+1;
      static const A0 fac = (1<<N)+1;
      A0 c = fac*a;
      r0 =  c-(c-a);
      r1 = a-r0;
    }
  };
} }

#endif
