//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_EVCDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_EVCDF_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/utility/max_extent.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief evcdf generic tag

     Represents the evcdf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct evcdf_ : ext::tieable_<evcdf_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<evcdf_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_evcdf_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
    struct evcdf0_ : ext::elementwise_<evcdf0_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<evcdf0_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_evcdf0_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::evcdf_, Site> dispatching_evcdf_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::evcdf_, Site>();
   }
   template<class... Args>
   struct impl_evcdf_;
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::evcdf0_, Site> dispatching_evcdf0_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::evcdf0_, Site>();
   }
   template<class... Args>
   struct impl_evcdf0_;
  }
  /*!
     extreme value  cumulative distribution of shape m and scale s

    @par Semantic:

    For every table expression
    deviation.

    @code
    auto r = evcdf(a0, m, s);
    @endcode


    @see @funcref{erfc}, @funcref{Sqrt_2o_2},
    @param a0
    @param a1 optional shape default to 0
    @param a2 optional scale default to 1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::evcdf0_, evcdf, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::evcdf0_, evcdf, 1)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::evcdf0_, evcdf, 2)
  /*!
        extreme value  cumulative distribution of shape m and scale s

    @par Semantic:

    For every table expression
    deviation.

    @code
    tie(r, rlo, rup) = evcdf(a0, m, s, cov, alpha);
    @endcode

    Returns r = evcdf(a0, m, s), but also produces confidence bounds
    for p when the input parameters m and s are estimates.  cov is a
    2-by-2 matrix containing the covariance matrix of the estimated parameters.
    alpha has a default value of 0.05, and specifies 100*(1-alpha)% confidence
    bounds.  rlo and rup are arrays of the same size as a0 containing the lower
    and upper confidence bounds.



    @param a0
    @param a1 shape estimate
    @param a2 scale estimate.
    @param a3 covariance matrix of the estimated a1 and a2
    @param a4 optional confidence bound (default to 0.05)

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::evcdf_,  evcdf, 5)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::evcdf_,  evcdf, 4)

}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<tag::evcdf_,Domain,N,Expr> // N =  4 or 5
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,0>
                      ::value_type::extent_type                     ext0_t;
    typedef typename  boost::proto::result_of::child_c<Expr&,1>
                      ::value_type::extent_type                     ext1_t;
    typedef typename  boost::proto::result_of::child_c<Expr&,2>
                      ::value_type::extent_type                     ext2_t;

   typedef typename utility::result_of::max_extent<ext2_t, ext1_t, ext0_t>::type     result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
     return utility::max_extent(nt2::extent(boost::proto::child_c<0>(e)),
                       nt2::extent(boost::proto::child_c<1>(e)),
                       nt2::extent(boost::proto::child_c<2>(e)));
    }
  };

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  size_of<tag::evcdf_,Domain,1,Expr>
        : meta::size_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<tag::evcdf_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
