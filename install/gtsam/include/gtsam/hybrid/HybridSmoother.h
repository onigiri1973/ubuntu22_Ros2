/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file    HybridSmoother.h
 * @brief   An incremental smoother for hybrid factor graphs
 * @author  Varun Agrawal
 * @date    October 2022
 */

#include <gtsam/discrete/DiscreteFactorGraph.h>
#include <gtsam/hybrid/HybridBayesNet.h>
#include <gtsam/hybrid/HybridGaussianFactorGraph.h>

#include <optional>

namespace gtsam {

class GTSAM_EXPORT HybridSmoother {
 private:
  HybridBayesNet hybridBayesNet_;

  /// The threshold above which we make a decision about a mode.
  std::optional<double> marginalThreshold_;
  DiscreteValues fixedValues_;

 public:
  /**
   * @brief Constructor
   *
   * @param removeDeadModes Flag indicating whether to remove dead modes.
   * @param marginalThreshold The threshold above which a mode gets assigned a
   * value and is considered "dead". 0.99 is a good starting value.
   */
  HybridSmoother(const std::optional<double> marginalThreshold = {})
      : marginalThreshold_(marginalThreshold) {}

  /// Return fixed values:
  const DiscreteValues& fixedValues() const { return fixedValues_; }

  /**
   * Re-initialize the smoother from a new hybrid Bayes Net.
   */
  void reInitialize(HybridBayesNet&& hybridBayesNet);

  /**
   * Re-initialize the smoother from
   * a new hybrid Bayes Net (non rvalue version).
   */
  void reInitialize(HybridBayesNet& hybridBayesNet);

  /**
   * Given new factors, perform an incremental update.
   * The relevant densities in the `hybridBayesNet` will be added to the input
   * graph (fragment), and then eliminated according to the `ordering`
   * presented. The remaining factor graph contains hybrid Gaussian factors
   * that are not connected to the variables in the ordering, or a single
   * discrete factor on all discrete keys, plus all discrete factors in the
   * original graph.
   *
   * \note If maxNrLeaves is given, we look at the discrete factor resulting
   * from this elimination, and prune it and the Gaussian components
   * corresponding to the pruned choices.
   *
   * @param graph The new factors, should be linear only
   * @param maxNrLeaves The maximum number of leaves in the new discrete factor,
   * if applicable
   * @param given_ordering The (optional) ordering for elimination, only
   * continuous variables are allowed
   */
  void update(const HybridGaussianFactorGraph& graph,
              std::optional<size_t> maxNrLeaves = {},
              const std::optional<Ordering> given_ordering = {});

  /**
   * @brief Get an elimination ordering which eliminates continuous
   * and then discrete.
   *
   * Expects `factors` to already have the necessary conditionals
   * which were connected to the variables in the newly added factors.
   * Those variables should be in `newFactorKeys`.
   *
   * @param factors All the new factors and connected conditionals.
   * @param newFactorKeys The keys/variables in the newly added factors.
   * @return Ordering
   */
  Ordering getOrdering(const HybridGaussianFactorGraph& factors,
                       const KeySet& newFactorKeys);

  /**
   * @brief Add conditionals from previous timestep as part of liquefication.
   *
   * @param graph The new factor graph for the current time step.
   * @param hybridBayesNet The hybrid bayes net containing all conditionals so
   * far.
   * @param ordering The elimination ordering.
   * @return std::pair<HybridGaussianFactorGraph, HybridBayesNet>
   */
  std::pair<HybridGaussianFactorGraph, HybridBayesNet> addConditionals(
      const HybridGaussianFactorGraph& graph,
      const HybridBayesNet& hybridBayesNet) const;

  /**
   * @brief Get the hybrid Gaussian conditional from
   * the Bayes Net posterior at `index`.
   *
   * @param index Indexing value.
   * @return HybridGaussianConditional::shared_ptr
   */
  HybridGaussianConditional::shared_ptr gaussianMixture(size_t index) const;

  /// Return the Bayes Net posterior.
  const HybridBayesNet& hybridBayesNet() const;

  /// Optimize the hybrid Bayes Net, taking into accound fixed values.
  HybridValues optimize() const;
};

}  // namespace gtsam
