/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *     Vincent Barichard <Vincent.Barichard@univ-angers.fr>
 *
 *  Copyright:
 *     Christian Schulte, 2004
 *     Vincent Barichard, 2012
 *
 *  Last modified:
 *     $Date$ by $Author$
 *     $Revision$
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

namespace Gecode { namespace Float { namespace Rel {

  /*
   * Disequality
   *
   */
  template<class View0, class View1>
  forceinline
  Nq<View0,View1>::Nq(Home home, View0 x0, View1 x1)
    : MixBinaryPropagator<View0,PC_FLOAT_BND,View1,PC_FLOAT_BND>(home,x0,x1) {}

  template<class View0, class View1>
  ExecStatus
  Nq<View0,View1>::post(Home home, View0 x0, View1 x1){
    if (x0.assigned()) {
      GECODE_ME_CHECK(x1.nq(home,x0.val()));
    } else if (x1.assigned()) {
      GECODE_ME_CHECK(x0.nq(home,x1.val()));
    } else if (same(x0,x1)) {
      return ES_FAILED;
    } else {
      (void) new (home) Nq<View0,View1>(home,x0,x1);
    }
    return ES_OK;
  }

  template<class View0, class View1>
  forceinline
  Nq<View0,View1>::Nq(Space& home, bool share, Nq<View0,View1>& p)
    : MixBinaryPropagator<View0,PC_FLOAT_BND,View1,PC_FLOAT_BND>(home,share,p) {}

  template<class View0, class View1>
  Actor*
  Nq<View0,View1>::copy(Space& home, bool share) {
    return new (home) Nq<View0,View1>(home,share,*this);
  }

  template<class View0, class View1>
  ExecStatus
  Nq<View0,View1>::propagate(Space& home, const ModEventDelta&) {
    if (x0.assigned()) {
      GECODE_ME_CHECK(x1.nq(home,x0.val()));
    } else {
      GECODE_ME_CHECK(x0.nq(home,x1.val()));
    }
    return ES_FIX;
  }



}}}

// STATISTICS: float-prop
