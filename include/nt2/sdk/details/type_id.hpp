/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DETAILS_TYPE_ID_HPP_INCLUDED
#define NT2_SDK_DETAILS_TYPE_ID_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Type name display
// Documentation: http://nt2.lri.fr/sdk/details/sdk/details/type_id.html
////////////////////////////////////////////////////////////////////////////////

#if (__GNUC__ && __cplusplus && __GNUC__ >= 3)
////////////////////////////////////////////////////////////////////////////////
// Includes abi::__cxa_demangle
////////////////////////////////////////////////////////////////////////////////
#include <cxxabi.h>
#endif

#include <cstdlib>
#include <typeinfo>
#include <nt2/sdk/sys/string.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // demangle a type name retrieved through typeid()
  //////////////////////////////////////////////////////////////////////////////
  inline sys::string demangle(const char* name)
  {
    ////////////////////////////////////////////////////////////////////////////
    // use g++ ABI interface to perform demangling
    ////////////////////////////////////////////////////////////////////////////
    #if(__GNUC__ && __cplusplus && __GNUC__ >= 3)
    std::size_t len;
    int         stat;

    char* realname = ::abi::__cxa_demangle(name,NULL,&len,&stat);

    if(realname != NULL)
    {
      sys::string out(realname);
      ::free(realname);
      return out;
    }
    else
    {
      return sys::string("?");
    }
    #else
    ////////////////////////////////////////////////////////////////////////////
    // Other compiler don't need or can't do that, so just return the type name
    ////////////////////////////////////////////////////////////////////////////
    sys::string out(name);
    return out;
    #endif
  }
} }

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // Return a string containing the demangled typename of a given variable
  //////////////////////////////////////////////////////////////////////////////
  template<class T> inline sys::string type_id(const T& )
  {
    sys::string const demangled = details::demangle(typeid(T).name());
    return demangled;
  }

  //////////////////////////////////////////////////////////////////////////////
  // Return a string containing the demangled typename of a given type
  //////////////////////////////////////////////////////////////////////////////
  template<class T> inline sys::string type_id()
  {
    sys::string const demangled = details::demangle(typeid(T).name());
    return demangled;
  }
}

#endif
