//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_FDLIBM_FUNCTION_SCALAR_ILOGB_HPP_INCLUDED
#define NT2_TOOLBOX_FDLIBM_FUNCTION_SCALAR_ILOGB_HPP_INCLUDED

  extern "C"{
    extern int fd_ilogb ( double );
  }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(fdlibm::tag::ilogb_, tag::cpu_,
                       (A0),
                       (arithmetic_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<fdlibm::tag::ilogb_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  { typedef int type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type   base;
      typedef typename meta::upgrade<base>::type  type;
      return nt2::fdlibm::ilogb(type(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(fdlibm::tag::ilogb_, tag::cpu_,
                       (A0),
                       (double_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<fdlibm::tag::ilogb_(tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  { typedef int type; };

    NT2_FUNCTOR_CALL(1){ return ::fd_ilogb(a0); }
  };
} }

#endif
