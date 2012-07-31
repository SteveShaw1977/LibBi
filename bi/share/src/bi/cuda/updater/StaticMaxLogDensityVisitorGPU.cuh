/**
 * @file
 *
 * @author Lawrence Murray <lawrence.murray@csiro.au>
 * $Rev$
 * $Date$
 */
#ifndef BI_CUDA_UPDATER_STATICMAXLOGDENSITYVISITORGPU_CUH
#define BI_CUDA_UPDATER_STATICMAXLOGDENSITYVISITORGPU_CUH

namespace bi {
/**
 * Visitor for static maximum log-density updates, on device.
 *
 * @tparam B Model type.
 * @tparam S Action type list.
 * @tparam PX Parents type.
 * @tparam OX Output type.
 */
template<class B, class S, class PX, class OX>
class StaticMaxLogDensityVisitorGPU {
public:
  /**
   * Update.
   *
   * @tparam T1 Scalar type.
   *
   * @param p Trajectory id.
   * @param i Variable id.
   * @param pax Parents.
   * @param[out] x Output.
   * @param[in,out] lp Log-density.
   */
  template<class T1>
  static CUDA_FUNC_DEVICE void accept(const int p, const int i,
      const PX& pax, OX& x, T1& lp);
};

/**
 * @internal
 *
 * Base case of StaticMaxLogDensityVisitorGPU.
 */
template<class B, class PX, class OX>
class StaticMaxLogDensityVisitorGPU<B,empty_typelist,PX,OX> {
public:
  template<class T1>
  static CUDA_FUNC_DEVICE void accept(const int p, const int i,
      const PX& pax, OX& x, T1& lp) {
    //
  }
};

}

#include "../../typelist/front.hpp"
#include "../../typelist/pop_front.hpp"

template<class B, class S, class PX, class OX>
template<class T1>
inline void bi::StaticMaxLogDensityVisitorGPU<B,S,PX,OX>::accept(const int p,
    const int i, const PX& pax, OX& x, T1& lp) {
  typedef typename front<S>::type front;
  typedef typename pop_front<S>::type pop_front;
  typedef typename front::target_type target_type;
  typedef typename target_type::coord_type coord_type;
  const int size = var_size<target_type>::value;

  if (i < size) {
    coord_type cox;
    cox.setIndex(i);
    front::maxLogDensities(p, i, cox, pax, x, lp);
  } else {
    StaticMaxLogDensityVisitorGPU<B,pop_front,PX,OX>::accept(p, i - size, pax, x, lp);
  }
}

#endif