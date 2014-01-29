/**
 * @file
 *
 * @author Anthony Lee
 * @author Lawrence Murray <lawrence.murray@csiro.au>
 */
#ifndef BI_STOPPER_STOPPER_HPP
#define BI_STOPPER_STOPPER_HPP

#include "../math/scalar.hpp"

namespace bi {
/**
 * Stopper for fixed number of particles.
 *
 * @ingroup method_stopper
 *
 * Used by AdaptiveParticleFilter to determine when a sufficient number of
 * particles have been propagated. Call #stop() any number of times with
 * additional weights of new particles, then #reset() again before reuse.
 */
class Stopper {
public:
  /**
   * Constructor.
   *
   * @param threshold Threshold value.
   * @param maxP Maximum number of particles.
   * @param blockP Number of particles per block.
   * @param T Number of observations.
   */
  Stopper(const real threshold, const int maxP, const int blockP,
      const int T);

  /**
   * Stop?
   *
   * @tparam V1 Vector type.
   *
   * @param lws New log-weights.
   * @param maxlw Maximum log-weight.
   */
  template<class V1>
  bool stop(const V1 lws, const real maxlw);

  /**
   * Reset for reuse.
   */
  void reset();

  /**
   * Get maximum number of particles.
   */
  int getMaxParticles() const;

  /**
   * Get number of particles per block.
   */
  int getBlockSize() const;

protected:
  /**
   * Threshold value.
   */
  const real threshold;

  /**
   * Maximum number of particles.
   */
  const int maxP;

  /**
   * Number of particles per block.
   */
  const int blockP;

  /**
   * Number of observations.
   */
  const int T;

  /**
   * Number of particles.
   */
  int P;
};
}

inline bi::Stopper::Stopper(const real threshold, const int maxP,
    const int blockP, const int T) :
    threshold(threshold), maxP(std::max(maxP, blockP)), blockP(blockP), T(T), P(
        0) {
  //
}

template<class V1>
bool bi::Stopper::stop(const V1 lws, const real maxlw) {
  return lws.size() >= threshold;
}

inline void bi::Stopper::reset() {
  P = 0;
}

inline int bi::Stopper::getMaxParticles() const {
  return maxP;
}

inline int bi::Stopper::getBlockSize() const {
  return blockP;
}

#endif