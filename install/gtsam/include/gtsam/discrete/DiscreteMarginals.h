/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file DiscreteMarginals.h
 * @brief A class for computing marginals in a DiscreteFactorGraph
 * @author Abhijit Kundu
 * @author Richard Roberts
 * @author Frank Dellaert
 * @date June 4, 2012
 */

#pragma once

#include <gtsam/base/Vector.h>
#include <gtsam/discrete/DiscreteBayesTree.h>
#include <gtsam/discrete/DiscreteFactorGraph.h>

namespace gtsam {

/**
 * A class for computing marginals of variables in a DiscreteFactorGraph
 * @ingroup discrete
 */
class DiscreteMarginals {
 protected:
  DiscreteBayesTree::shared_ptr bayesTree_;

 public:
  DiscreteMarginals() {}

  /** Construct a marginals class.
   * @param graph The factor graph defining the full joint 
   * distribution on all variables.
   */
  DiscreteMarginals(const DiscreteFactorGraph& graph) {
    bayesTree_ = graph.eliminateMultifrontal();
  }

  /** Compute the marginal of a single variable */
  DiscreteFactor::shared_ptr operator()(Key variable) const {
    // Compute marginal
    DiscreteFactor::shared_ptr marginalFactor =
        bayesTree_->marginalFactor(variable, &EliminateDiscrete);
    return marginalFactor;
  }

  /** Compute the marginal of a single variable
   *   @param key DiscreteKey of the Variable
   *   @return Vector of marginal probabilities
   */
  Vector marginalProbabilities(const DiscreteKey& key) const {
    // Compute marginal
    DiscreteFactor::shared_ptr marginalFactor = this->operator()(key.first);

    // Create result
    Vector vResult(key.second);
    for (size_t state = 0; state < key.second; ++state) {
      DiscreteValues values;
      values[key.first] = state;
      vResult(state) = (*marginalFactor)(values);
    }
    return vResult;
  }
};

} /* namespace gtsam */
