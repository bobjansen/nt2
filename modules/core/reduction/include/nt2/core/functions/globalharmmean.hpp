//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALHARMMEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALHARMMEAN_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/harmmean.hpp>
#include <nt2/include/functions/global.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the globalharmmean functor
    **/
    struct globalharmmean_ : ext::abstract_<globalharmmean_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<globalharmmean_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_globalharmmean_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::globalharmmean_, Site> dispatching_globalharmmean_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::globalharmmean_, Site>();
    }
    template<class... Args>
    struct impl_globalharmmean_;
  }

  /*!
    @brief Harmmean of all the elements of an expression

    Computes the harmonic mean of all the elements of a table expression

    @par Semantic

    For any table expression :

    @code
    T r = globalharmmean(t);
    @endcode

    is equivalent to:

    @code
    T r = harmmean(t(_))(1);
    @endcode

    @see @funcref{colon}, @funcref{harmmean}
    @param a0 Table to process

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalharmmean_, globalharmmean, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalharmmean_, g_harmmean, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( globalharmmean_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename meta::call<tag::global_( nt2::functor<tag::harmmean_>
                                            , const A0&
                                            )>::type                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
       return global(nt2::functor<tag::harmmean_>(), a0);
    }
  };
} }

#endif