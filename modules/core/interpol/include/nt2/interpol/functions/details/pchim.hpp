//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_DETAILS_PCHIM_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_DETAILS_PCHIM_HPP_INCLUDED

#include <nt2/include/functions/dec.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/sign.hpp>

#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/three.hpp>

namespace nt2 { namespace details
{
  template < class X,  class F, class D>
  BOOST_FORCEINLINE
  void pchim(const X& x, const F & f, D& d)
  {
    size_t n =  numel(x);
    using vtype_t = typename D::value_type;
    using xtype_t = typename X::value_type;
    size_t nm1 = dec(n);
    xtype_t h1 = x(2)-x(1);
    vtype_t del1 = (f(2) - f(1))/h1;
    vtype_t dsave = del1;
    if (nm1 < 2u) // n == 2 linear interpol
    {
      d(1) =  d(n) = del1;
    }
    else
    {
      xtype_t h2 = x(3) - x(2);
      vtype_t del2 = (f(3) - f(2))/h1;
      //
      //  set d(1) via non-centered three-point formula, adjusted to be
      //     shape-preserving.
      //
      xtype_t hsum = h1 + h2;
      xtype_t w1 = (h1 + hsum)/hsum;
      xtype_t w2 = -h1/hsum;
      d(1) = fma(w1, del1,  w2*del2);
      if ( is_lez(sign(d(1)*del1)))
      {
        d(1) = Zero<vtype_t>();
      }
      else if ( is_ltz(sign(del1*del2)))
      {
        //        need do this check only if monotonicity switches.
        d(1) = nt2::min(d(1), Three<vtype_t>()*del1);
      }

//
//   loop through interior points.
//
      for(size_t i = 2; i <= nm1; ++i)
      {
        if (i > 2)
        {
          h1 = h2;
          h2 = x(i+1) - x(i);
          hsum = h1 + h2;
          del1 = del2;
          del2 = (f(i) - f(i-1))/h2;
        }
//
//         set d(i)=0 unless data are strictly monotonic.
//
        if (is_lez(sign(del1*del2)))
        {
          d(i) = Zero<vtype_t>();
          dsave =  del2;
        }
        else
        {
//         use brodlie modification of butland formula.
          xtype_t hsumt3 = Three<xtype_t>()*hsum;
          w1 = (hsum + h1)/hsumt3;
          w2 = (hsum + h2)/hsumt3;
          vtype_t dmax = max( abs(del1), abs(del2) );
          vtype_t dmin = min( abs(del1), abs(del2) );
          vtype_t drat1 = del1/dmax;
          vtype_t drat2 = del2/dmax;
          d(i) = dmin/fma(w1, drat1, w2*drat2) ;
        }
//
//   set d(n) via non-centered three-point formula, adjusted to be
//      shape-preserving.
//
        w1 = -h2/hsum;
        w2 = (h2 + hsum)/hsum;
        d(n) = w1*del1 + w2*del2;
        if ( is_lez(sign(d(n)*del2)))
        {
          d(n) = Zero<vtype_t>();
        }
        else if ( is_ltz(sign(del1*del2)))
        {
          //         need do this check only if monotonicity switches.
          d(n) = nt2::min(d(1), Three<vtype_t>()*del1);
        }
      }
    }
  }


  template <class X,  class Z, class S>
  BOOST_FORCEINLINE
  void slopes(const X& x, const Z & z, S& slp, const boost::mpl::long_<1>&)
  {
    using vtype_t =  typename S::value_type;
    table<vtype_t> tmp(of_size(1, width(z)));
    for(size_t r=1; r <= size(z, 1); ++r)
    {
      pchim(x, z(r, _),tmp);
      slp(r, _) = tmp;
    }

  }

  template <class X,  class Z, class S>
  BOOST_FORCEINLINE
  void slopes(const X& x, const Z & z, S& slp, const boost::mpl::long_<2> &)
  {
    using vtype_t =  typename S::value_type;
    table<vtype_t> tmp(of_size(height(z), 1));
    for(size_t r=1; r <= size(z, 2); ++r)
    {
      pchim(x, z(_, r),tmp);
      slp(_, r) = tmp;
    }

  }

  template < long N, class X,  class Z>
  BOOST_FORCEINLINE
  table <  typename Z::value_type>
  slopes(const X& x, const Z & z)
  {
    table<typename Z::value_type> slp(z.extent());
    slopes(x, z, slp, boost::mpl::long_<N>());
    return slp;
  }


} }

#endif
// *DECK DPCHIM
//       SUBROUTINE DPCHIM (N, X, F, D, INCFD, IERR)
// C***BEGIN PROLOGUE  DPCHIM
// C***PURPOSE  Set derivatives needed to determine a monotone piecewise
// C            cubic Hermite interpolant to given data.  Boundary values
// C            are provided which are compatible with monotonicity.  The
// C            interpolant will have an extremum at each point where mono-
// C            tonicity switches direction.  (See DPCHIC if user control
// C            is desired over boundary or switch conditions.)
// C***LIBRARY   SLATEC (PCHIP)
// C***CATEGORY  E1A
// C***TYPE      DOUBLE PRECISION (PCHIM-S, DPCHIM-D)
// C***KEYWORDS  CUBIC HERMITE INTERPOLATION, MONOTONE INTERPOLATION,
// C             PCHIP, PIECEWISE CUBIC INTERPOLATION
// C***AUTHOR  Fritsch, F. N., (LLNL)
// C             Lawrence Livermore National Laboratory
// C             P.O. Box 808  (L-316)
// C             Livermore, CA  94550
// C             FTS 532-4275, (510) 422-4275
// C***DESCRIPTION
// C
// C          DPCHIM:  Piecewise Cubic Hermite Interpolation to
// C                  Monotone data.
// C
// C     Sets derivatives needed to determine a monotone piecewise cubic
// C     Hermite interpolant to the data given in X and F.
// C
// C     Default boundary conditions are provided which are compatible
// C     with monotonicity.  (See DPCHIC if user control of boundary con-
// C     ditions is desired.)
// C
// C     If the data are only piecewise monotonic, the interpolant will
// C     have an extremum at each point where monotonicity switches direc-
// C     tion.  (See DPCHIC if user control is desired in such cases.)
// C
// C     To facilitate two-dimensional applications, includes an increment
// C     between successive values of the F- and D-arrays.
// C
// C     The resulting piecewise cubic Hermite function may be evaluated
// C     by DPCHFE or DPCHFD.
// C
// C ----------------------------------------------------------------------
// C
// C  Calling sequence:
// C
// C        PARAMETER  (INCFD = ...)
// C        INTEGER  N, IERR
// C        DOUBLE PRECISION  X(N), F(INCFD,N), D(INCFD,N)
// C
// C        CALL  DPCHIM (N, X, F, D, INCFD, IERR)
// C
// C   Parameters:
// C
// C     N -- (input) number of data points.  (Error return if N.LT.2 .)
// C           If N=2, simply does linear interpolation.
// C
// C     X -- (input) real*8 array of independent variable values.  The
// C           elements of X must be strictly increasing:
// C                X(I-1) .LT. X(I),  I = 2(1)N.
// C           (Error return if not.)
// C
// C     F -- (input) real*8 array of dependent variable values to be
// C           interpolated.  F(1+(I-1)*INCFD) is value corresponding to
// C           X(I).  DPCHIM is designed for monotonic data, but it will
// C           work for any F-array.  It will force extrema at points where
// C           monotonicity switches direction.  If some other treatment of
// C           switch points is desired, DPCHIC should be used instead.
// C                                     -----
// C     D -- (output) real*8 array of derivative values at the data
// C           points.  If the data are monotonic, these values will
// C           determine a monotone cubic Hermite function.
// C           The value corresponding to X(I) is stored in
// C                D(1+(I-1)*INCFD),  I=1(1)N.
// C           No other entries in D are changed.
// C
// C     INCFD -- (input) increment between successive values in F and D.
// C           This argument is provided primarily for 2-D applications.
// C           (Error return if  INCFD.LT.1 .)
// C
// C     IERR -- (output) error flag.
// C           Normal return:
// C              IERR = 0  (no errors).
// C           Warning error:
// C              IERR.GT.0  means that IERR switches in the direction
// C                 of monotonicity were detected.
// C           "Recoverable" errors:
// C              IERR = -1  if N.LT.2 .
// C              IERR = -2  if INCFD.LT.1 .
// C              IERR = -3  if the X-array is not strictly increasing.
// C             (The D-array has not been changed in any of these cases.)
// C               NOTE:  The above errors are checked in the order listed,
// C                   and following arguments have **NOT** been validated.
// C
// C***REFERENCES  1. F. N. Fritsch and J. Butland, A method for construc-
// C                 ting local monotone piecewise cubic interpolants, SIAM
// C                 Journal on Scientific and Statistical Computing 5, 2
// C                 (June 1984), pp. 300-304.
// C               2. F. N. Fritsch and R. E. Carlson, Monotone piecewise
// C                 cubic interpolation, SIAM Journal on Numerical Ana-
// C                 lysis 17, 2 (April 1980), pp. 238-246.
// C***ROUTINES CALLED  SIGN, XERMSG
// C***REVISION HISTORY  (YYMMDD)
// C   811103  DATE WRITTEN
// C   820201  1. Introduced  SIGN  to reduce possible over/under-
// C             flow problems.
// C           2. Rearranged derivative formula for same reason.
// C   820602  1. Modified end conditions to be continuous functions
// C             of data when monotonicity switches in next interval.
// C           2. Modified formulas so end conditions are less prone
// C             of over/underflow problems.
// C   820803  Minor cosmetic changes for release 1.
// C   870707  Corrected XERROR calls for d.p. name(s).
// C   870813  Updated Reference 1.
// C   890206  Corrected XERROR calls.
// C   890411  Added SAVE statements (Vers. 3.2).
// C   890531  Changed all specific intrinsics to generic.  (WRB)
// C   890703  Corrected category record.  (WRB)
// C   890831  Modified array declarations.  (WRB)
// C   891006  Cosmetic changes to prologue.  (WRB)
// C   891006  REVISION DATE from Version 3.2
// C   891214  Prologue converted to Version 4.0 format.  (BAB)
// C   900315  CALLs to XERROR changed to CALLs to XERMSG.  (THJ)
// C   920429  Revised format and order of references.  (WRB,FNF)
// C***END PROLOGUE  DPCHIM
// C  Programming notes:
// C
// C     1. The function  SIGN(ARG1,ARG2)  is assumed to return zero if
// C        either argument is zero, +1 if they are of the same sign, and
// C        -1 if they are of opposite sign.
// C     2. To produce a single precision version, simply:
// C        a. Change DPCHIM to PCHIM wherever it occurs,
// C        b. Change SIGN to PCHST wherever it occurs,
// C        c. Change all references to the Fortran intrinsics to their
// C           single precision equivalents,
// C        d. Change the double precision declarations to real, and
// C        e. Change the constants ZERO and THREE to single precision.
// C
// C  DECLARE ARGUMENTS.
// C
//       INTEGER  N, INCFD, IERR
//       DOUBLE PRECISION  X(*), F(INCFD,*), D(INCFD,*)
// C
// C  DECLARE LOCAL VARIABLES.
// C
//       INTEGER  I, NLESS1
//       DOUBLE PRECISION  DEL1, DEL2, DMAX, DMIN, DRAT1, DRAT2, DSAVE,
//      *      H1, H2, HSUM, HSUMT3, THREE, W1, W2, ZERO
//       SAVE ZERO, THREE
//       DOUBLE PRECISION  SIGN
//       DATA  ZERO /0.D0/, THREE/3.D0/
// C
// C  VALIDITY-CHECK ARGUMENTS.
// C
// C***FIRST EXECUTABLE STATEMENT  DPCHIM
//       IF ( N.LT.2 )  GO TO 5001
//       IF ( INCFD.LT.1 )  GO TO 5002
//       DO 1  I = 2, N
//          IF ( X(I).LE.X(I-1) )  GO TO 5003
//     1 CONTINUE
// C
// C  FUNCTION DEFINITION IS OK, GO ON.
// C
//       IERR = 0
//       NLESS1 = N - 1
//       H1 = X(2) - X(1)
//       DEL1 = (F(1,2) - F(1,1))/H1
//       DSAVE = DEL1
// C
// C  SPECIAL CASE N=2 -- USE LINEAR INTERPOLATION.
// C
//       IF (NLESS1 .GT. 1)  GO TO 10
//       D(1,1) = DEL1
//       D(1,N) = DEL1
//       GO TO 5000
// C
// C  NORMAL CASE  (N .GE. 3).
// C
//    10 CONTINUE
//       H2 = X(3) - X(2)
//       DEL2 = (F(1,3) - F(1,2))/H2
// C
// C  SET D(1) VIA NON-CENTERED THREE-POINT FORMULA, ADJUSTED TO BE
// C     SHAPE-PRESERVING.
// C
//       HSUM = H1 + H2
//       W1 = (H1 + HSUM)/HSUM
//       W2 = -H1/HSUM
//       D(1,1) = W1*DEL1 + W2*DEL2
//       IF ( SIGN(D(1,1),DEL1) .LE. ZERO)  THEN
//          D(1,1) = ZERO
//       ELSE IF ( SIGN(DEL1,DEL2) .LT. ZERO)  THEN
// C        NEED DO THIS CHECK ONLY IF MONOTONICITY SWITCHES.
//          DMAX = THREE*DEL1
//          IF (ABS(D(1,1)) .GT. ABS(DMAX))  D(1,1) = DMAX
//       ENDIF
// C
// C  LOOP THROUGH INTERIOR POINTS.
// C
//       DO 50  I = 2, NLESS1
//          IF (I .EQ. 2)  GO TO 40
// C
//          H1 = H2
//          H2 = X(I+1) - X(I)
//          HSUM = H1 + H2
//          DEL1 = DEL2
//          DEL2 = (F(1,I+1) - F(1,I))/H2
//    40    CONTINUE
// C
// C        SET D(I)=0 UNLESS DATA ARE STRICTLY MONOTONIC.
// C
//          D(1,I) = ZERO
//          IF ( SIGN(DEL1,DEL2) .LT. 0.)  GO TO 42
//          IF ( SIGN(DEL1,DEL2) .EQ. 0.)  GO TO 41
//          GO TO 45
// C
// C        COUNT NUMBER OF CHANGES IN DIRECTION OF MONOTONICITY.
// C
//    41    CONTINUE
//          IF (DEL2 .EQ. ZERO)  GO TO 50
//          IF ( SIGN(DSAVE,DEL2) .LT. ZERO)  IERR = IERR + 1
//          DSAVE = DEL2
//          GO TO 50
// C
//    42    CONTINUE
//          IERR = IERR + 1
//          DSAVE = DEL2
//          GO TO 50
// C
// C        USE BRODLIE MODIFICATION OF BUTLAND FORMULA.
// C
//    45    CONTINUE
//          HSUMT3 = HSUM+HSUM+HSUM
//          W1 = (HSUM + H1)/HSUMT3
//          W2 = (HSUM + H2)/HSUMT3
//          DMAX = MAX( ABS(DEL1), ABS(DEL2) )
//          DMIN = MIN( ABS(DEL1), ABS(DEL2) )
//          DRAT1 = DEL1/DMAX
//          DRAT2 = DEL2/DMAX
//          D(1,I) = DMIN/(W1*DRAT1 + W2*DRAT2)
// C
//    50 CONTINUE
// C
// C  SET D(N) VIA NON-CENTERED THREE-POINT FORMULA, ADJUSTED TO BE
// C     SHAPE-PRESERVING.
// C
//       W1 = -H2/HSUM
//       W2 = (H2 + HSUM)/HSUM
//       D(1,N) = W1*DEL1 + W2*DEL2
//       IF ( SIGN(D(1,N),DEL2) .LE. ZERO)  THEN
//          D(1,N) = ZERO
//       ELSE IF ( SIGN(DEL1,DEL2) .LT. ZERO)  THEN
// C        NEED DO THIS CHECK ONLY IF MONOTONICITY SWITCHES.
//          DMAX = THREE*DEL2
//          IF (ABS(D(1,N)) .GT. ABS(DMAX))  D(1,N) = DMAX
//       ENDIF
// C
// C  NORMAL RETURN.
// C
//  5000 CONTINUE
//       RETURN
// C
// C  ERROR RETURNS.
// C
//  5001 CONTINUE
// C     N.LT.2 RETURN.
//       IERR = -1
//       CALL XERMSG ('SLATEC', 'DPCHIM',
//      +   'NUMBER OF DATA POINTS LESS THAN TWO', IERR, 1)
//       RETURN
// C
//  5002 CONTINUE
// C     INCFD.LT.1 RETURN.
//       IERR = -2
//       CALL XERMSG ('SLATEC', 'DPCHIM', 'INCREMENT LESS THAN ONE', IERR,
//      +   1)
//       RETURN
// C
//  5003 CONTINUE
// C     X-ARRAY NOT STRICTLY INCREASING.
//       IERR = -3
//       CALL XERMSG ('SLATEC', 'DPCHIM',
//      +   'X-ARRAY NOT STRICTLY INCREASING', IERR, 1)
//       RETURN
// C------------- LAST LINE OF DPCHIM FOLLOWS -----------------------------
//       END