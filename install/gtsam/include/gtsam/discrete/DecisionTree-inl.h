/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file    DecisionTree.h
 * @brief   Decision Tree for use in DiscreteFactors
 * @author  Frank Dellaert
 * @author  Can Erdogan
 * @date    Jan 30, 2012
 */

#pragma once

#include <gtsam/discrete/DecisionTree.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace gtsam {

  /****************************************************************************/
  // Node
  /****************************************************************************/
#ifdef DT_DEBUG_MEMORY
  template<typename L, typename Y>
  int DecisionTree<L, Y>::Node::nrNodes = 0;
#endif

  /****************************************************************************/
  // Leaf
  /****************************************************************************/
  template <typename L, typename Y>
  struct DecisionTree<L, Y>::Leaf : public DecisionTree<L, Y>::Node {
    /** constant stored in this leaf */
    Y constant_;

    /// Default constructor for serialization.
    Leaf() {}

    /// Constructor from constant
    Leaf(const Y& constant) : constant_(constant) {}

    /// Return the constant
    const Y& constant() const {
      return constant_;
    }

    /// Leaf-Leaf equality
    bool sameLeaf(const Leaf& q) const override {
      return constant_ == q.constant_;
    }

    /// polymorphic equality: is q a leaf and is it the same as this leaf?
    bool sameLeaf(const Node& q) const override {
      return (q.isLeaf() && q.sameLeaf(*this));
    }

    /// equality up to tolerance
    bool equals(const Node& q, const CompareFunc& compare) const override {
      if (!q.isLeaf()) return false;
      const Leaf* other = static_cast<const Leaf*>(&q);
      return compare(this->constant_, other->constant_);
    }

    /// print
    void print(const std::string& s, const LabelFormatter& labelFormatter,
               const ValueFormatter& valueFormatter) const override {
      std::cout << s << " Leaf " << valueFormatter(constant_) << std::endl;
    }

    /** Write graphviz format to stream `os`. */
    void dot(std::ostream& os, const LabelFormatter& labelFormatter,
             const ValueFormatter& valueFormatter,
             bool showZero) const override {
      const std::string value = valueFormatter(constant_);
      if (showZero || value.compare("0"))
        os << "\"" << this->id() << "\" [label=\"" << value
           << "\", shape=box, rank=sink, height=0.35, fixedsize=true]\n";
    }

    /** evaluate */
    const Y& operator()(const Assignment<L>& x) const override {
      return constant_;
    }

    /** apply unary operator */
    NodePtr apply(const Unary& op) const override {
      NodePtr f(new Leaf(op(constant_)));
      return f;
    }

    /// Apply unary operator with assignment
    NodePtr apply(const UnaryAssignment& op,
                  const Assignment<L>& assignment) const override {
      NodePtr f(new Leaf(op(assignment, constant_)));
      return f;
    }

    // Apply binary operator "h = f op g" on Leaf node
    // Note op is not assumed commutative so we need to keep track of order
    // Simply calls apply on argument to call correct virtual method:
    // fL.apply_f_op_g(gL) -> gL.apply_g_op_fL(fL) (below)
    // fL.apply_f_op_g(gC) -> gC.apply_g_op_fL(fL) (Choice)
    NodePtr apply_f_op_g(const Node& g, const Binary& op) const override {
      return g.apply_g_op_fL(*this, op);
    }

    // Applying binary operator to two leaves results in a leaf
    NodePtr apply_g_op_fL(const Leaf& fL, const Binary& op) const override {
      // fL op gL
      NodePtr h(new Leaf(op(fL.constant_, constant_)));
      return h;
    }

    // If second argument is a Choice node, call it's apply with leaf as second
    NodePtr apply_g_op_fC(const Choice& fC, const Binary& op) const override {
      return fC.apply_fC_op_gL(*this, op);  // operand order back to normal
    }

    /** choose a branch, create new memory ! */
    NodePtr choose(const L& label, size_t index) const override {
      return NodePtr(new Leaf(constant()));
    }

    bool isLeaf() const override { return true; }

   private:
    using Base = DecisionTree<L, Y>::Node;

#if GTSAM_ENABLE_BOOST_SERIALIZATION
    /** Serialization function */
    friend class boost::serialization::access;
    template <class ARCHIVE>
    void serialize(ARCHIVE& ar, const unsigned int /*version*/) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Base);
      ar& BOOST_SERIALIZATION_NVP(constant_);
    }
#endif
  };  // Leaf

  /****************************************************************************/
  // Choice
  /****************************************************************************/
  template<typename L, typename Y>
  struct DecisionTree<L, Y>::Choice: public DecisionTree<L, Y>::Node {
    /** the label of the variable on which we split */
    L label_;

    /** The children of this Choice node. */
    std::vector<NodePtr> branches_;

   private:
    /**
     * Incremental allSame.
     * Records if all the branches are the same leaf.
     */
    size_t allSame_;

    using ChoicePtr = std::shared_ptr<const Choice>;

   public:
    /// Default constructor for serialization.
    Choice() {}

    ~Choice() override {
#ifdef DT_DEBUG_MEMORY
      std::cout << Node::nrNodes << " destructing (Choice) " << this->id()
                     << std::endl;
#endif
    }

    /**
     * @brief Merge branches with equal leaf values for every choice node in a
     * decision tree. If all branches are the same (i.e. have the same leaf
     * value), replace the choice node with the equivalent leaf node.
     *
     * This function applies the branch merging (if enabled) recursively on the
     * decision tree represented by the root node passed in as the argument. It
     * recurses to the leaf nodes and merges branches with equal leaf values in
     * a bottom-up fashion.
     *
     * Thus, if all branches of a choice node `f` are the same,
     * just return a single branch at each recursion step.
     *
     * @param node The root node of the decision tree.
     * @return NodePtr
     */
    #ifdef GTSAM_DT_MERGING

    static NodePtr Unique(const NodePtr& node) {
      if (node->isLeaf()) return node;  // Leaf node, return as is

      auto choice = std::static_pointer_cast<const Choice>(node);
      // Choice node, we recurse!
      // Make non-const copy so we can update
      auto f = std::make_shared<Choice>(choice->label(), choice->nrChoices());

      // Iterate over all the branches
      for (const auto& branch : choice->branches_) {
        f->push_back(Unique(branch));
      }

      // If all the branches are the same, we can merge them into one
      if (f->allSame_) {
        assert(f->branches().size() > 0);
        auto f0 = std::static_pointer_cast<const Leaf>(f->branches_[0]);
        return std::make_shared<Leaf>(f0->constant());
      }

      return f;
    }

    #else

    static NodePtr Unique(const NodePtr& node) {
      // No-op when GTSAM_DT_MERGING is not defined
      return node;
    }

    #endif
    bool isLeaf() const override { return false; }

    /// Constructor, given choice label and mandatory expected branch count.
    Choice(const L& label, size_t count) :
      label_(label), allSame_(true) {
      branches_.reserve(count);
    }

    /// Construct from applying binary op to two Choice nodes.
    Choice(const Choice& f, const Choice& g, const Binary& op) :
      allSame_(true) {
      // Choose what to do based on label
      if (f.label() > g.label()) {
        // f higher than g
        label_ = f.label();
        size_t count = f.nrChoices();
        branches_.reserve(count);
        for (size_t i = 0; i < count; i++) {
          NodePtr newBranch = f.branches_[i]->apply_f_op_g(g, op);
          push_back(std::move(newBranch));
        }
      } else if (g.label() > f.label()) {
        // f lower than g
        label_ = g.label();
        size_t count = g.nrChoices();
        branches_.reserve(count);
        for (size_t i = 0; i < count; i++) {
          NodePtr newBranch = g.branches_[i]->apply_g_op_fC(f, op);
          push_back(std::move(newBranch));
        }
      } else {
        // f same level as g
        label_ = f.label();
        size_t count = f.nrChoices();
        branches_.reserve(count);
        for (size_t i = 0; i < count; i++) {
          NodePtr newBranch = f.branches_[i]->apply_f_op_g(*g.branches_[i], op);
          push_back(std::move(newBranch));
        }
      }
    }

    /// Return the label of this choice node.
    const L& label() const {
      return label_;
    }

    size_t nrChoices() const {
      return branches_.size();
    }

    const std::vector<NodePtr>& branches() const {
      return branches_;
    }

    std::vector<NodePtr>& branches() {
      return branches_;
    }

    /** add a branch: TODO merge into constructor */
    void push_back(NodePtr&& node) {
      // allSame_ is restricted to leaf nodes in a decision tree
      if (allSame_ && !branches_.empty()) {
        allSame_ = node->sameLeaf(*branches_.back());
      }
      branches_.push_back(std::move(node));
    }

    /// print (as a tree).
    void print(const std::string& s, const LabelFormatter& labelFormatter,
               const ValueFormatter& valueFormatter) const override {
      std::cout << s << " Choice(";
      std::cout << labelFormatter(label_) << ") " << std::endl;
      for (size_t i = 0; i < branches_.size(); i++) {
        branches_[i]->print(s + " " + std::to_string(i), labelFormatter, valueFormatter);
      }
    }

    /** output to graphviz (as a a graph) */
    void dot(std::ostream& os, const LabelFormatter& labelFormatter,
             const ValueFormatter& valueFormatter,
             bool showZero) const override {
      const std::string label = labelFormatter(label_);
      os << "\"" << this->id() << "\" [shape=circle, label=\"" << label
          << "\"]\n";
      size_t B = branches_.size();
      for (size_t i = 0; i < B; i++) {
        const NodePtr& branch = branches_[i];

        // Check if zero
        if (!showZero && branch->isLeaf()) {
            auto leaf = std::static_pointer_cast<const Leaf>(branch);
          if (valueFormatter(leaf->constant()).compare("0")) continue;
        }

        os << "\"" << this->id() << "\" -> \"" << branch->id() << "\"";
        if (B == 2 && i == 0) os << " [style=dashed]";
        os << std::endl;
        branch->dot(os, labelFormatter, valueFormatter, showZero);
      }
    }

    /// Choice-Leaf equality: always false
    bool sameLeaf(const Leaf& q) const override {
      return false;
    }

    /// polymorphic equality: if q is a leaf, could be...
    bool sameLeaf(const Node& q) const override {
      return (q.isLeaf() && q.sameLeaf(*this));
    }

    /// equality
    bool equals(const Node& q, const CompareFunc& compare) const override {
      if (q.isLeaf()) return false;
      const Choice* other = static_cast<const Choice*>(&q);
      if (this->label_ != other->label_) return false;
      if (branches_.size() != other->branches_.size()) return false;
      // we don't care about shared pointers being equal here
      for (size_t i = 0; i < branches_.size(); i++)
        if (!(branches_[i]->equals(*(other->branches_[i]), compare)))
          return false;
      return true;
    }

    /// evaluate
    const Y& operator()(const Assignment<L>& x) const override {
#ifndef NDEBUG
      typename Assignment<L>::const_iterator it = x.find(label_);
      if (it == x.end()) {
        std::cout << "Trying to find value for " << label_ << std::endl;
        throw std::invalid_argument(
            "DecisionTree::operator(): value undefined for a label");
      }
#endif
      size_t index = x.at(label_);
      NodePtr child = branches_[index];
      return (*child)(x);
    }

    /// Construct from applying unary op to a Choice node.
    Choice(const L& label, const Choice& f, const Unary& op) :
      label_(label), allSame_(true) {
      branches_.reserve(f.branches_.size());  // reserve space
      for (const NodePtr& branch : f.branches_) {
        push_back(branch->apply(op));
      }
    }

    /**
     * @brief Constructor which accepts a UnaryAssignment op and the
     * corresponding assignment.
     *
     * @param label The label for this node.
     * @param f The original choice node to apply the op on.
     * @param op Function to apply on the choice node. Takes Assignment and
     * value as arguments.
     * @param assignment The Assignment that will go to op.
     */
    Choice(const L& label, const Choice& f, const UnaryAssignment& op,
           const Assignment<L>& assignment)
        : label_(label), allSame_(true) {
      branches_.reserve(f.branches_.size());  // reserve space

      Assignment<L> assignment_ = assignment;

      for (size_t i = 0; i < f.branches_.size(); i++) {
        assignment_[label_] = i;  // Set assignment for label to i

        const NodePtr branch = f.branches_[i];
        push_back(branch->apply(op, assignment_));

        // Remove the assignment so we are backtracking
        auto assignment_it = assignment_.find(label_);
        assignment_.erase(assignment_it);
      }
    }

    /// apply unary operator.
    NodePtr apply(const Unary& op) const override {
      auto r = std::make_shared<Choice>(label_, *this, op);
      return Unique(r);
    }

    /// Apply unary operator with assignment
    NodePtr apply(const UnaryAssignment& op,
                  const Assignment<L>& assignment) const override {
      auto r = std::make_shared<Choice>(label_, *this, op, assignment);
      return Unique(r);
    }

    // Apply binary operator "h = f op g" on Choice node
    // Note op is not assumed commutative so we need to keep track of order
    // Simply calls apply on argument to call correct virtual method:
    // fC.apply_f_op_g(gL) -> gL.apply_g_op_fC(fC) -> (Leaf)
    // fC.apply_f_op_g(gC) -> gC.apply_g_op_fC(fC) -> (below)
    NodePtr apply_f_op_g(const Node& g, const Binary& op) const override {
      return g.apply_g_op_fC(*this, op);
    }

    // If second argument of binary op is Leaf node, recurse on branches
    NodePtr apply_g_op_fL(const Leaf& fL, const Binary& op) const override {
      auto h = std::make_shared<Choice>(label(), nrChoices());
      for (auto&& branch : branches_)
        h->push_back(fL.apply_f_op_g(*branch, op));
      return Unique(h);
    }

    // If second argument of binary op is Choice, call constructor
    NodePtr apply_g_op_fC(const Choice& fC, const Binary& op) const override {
      auto h = std::make_shared<Choice>(fC, *this, op);
      return Unique(h);
    }

    // If second argument of binary op is Leaf
    template<typename OP>
    NodePtr apply_fC_op_gL(const Leaf& gL, OP op) const {
      auto h = std::make_shared<Choice>(label(), nrChoices());
      for (auto&& branch : branches_)
        h->push_back(branch->apply_f_op_g(gL, op));
      return Unique(h);
    }

    /** choose a branch, recursively */
    NodePtr choose(const L& label, size_t index) const override {
      if (label_ == label) return branches_[index];  // choose branch

      // second case, not label of interest, just recurse
      auto r = std::make_shared<Choice>(label_, branches_.size());
      for (auto&& branch : branches_) {
        r->push_back(branch->choose(label, index));
      }

      return Unique(r);
    }

   private:
    using Base = DecisionTree<L, Y>::Node;

#if GTSAM_ENABLE_BOOST_SERIALIZATION
    /** Serialization function */
    friend class boost::serialization::access;
    template <class ARCHIVE>
    void serialize(ARCHIVE& ar, const unsigned int /*version*/) {
      ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Base);
      ar& BOOST_SERIALIZATION_NVP(label_);
      ar& BOOST_SERIALIZATION_NVP(branches_);
      ar& BOOST_SERIALIZATION_NVP(allSame_);
    }
#endif
  };  // Choice

  /****************************************************************************/
  // DecisionTree
  /****************************************************************************/
  template <typename L, typename Y>
  DecisionTree<L, Y>::DecisionTree() : root_(nullptr) {}

  template<typename L, typename Y>
  DecisionTree<L, Y>::DecisionTree(const NodePtr& root) :
    root_(root) {}

  /****************************************************************************/
  template<typename L, typename Y>
  DecisionTree<L, Y>::DecisionTree(const Y& y)  {
    root_ = NodePtr(new Leaf(y));
  }

  /****************************************************************************/
  template <typename L, typename Y>
  DecisionTree<L, Y>::DecisionTree(const L& label, const Y& y1, const Y& y2) {
    auto a = std::make_shared<Choice>(label, 2);
    NodePtr l1(new Leaf(y1)), l2(new Leaf(y2));
    a->push_back(std::move(l1));
    a->push_back(std::move(l2));
    root_ = Choice::Unique(std::move(a));
  }

  /****************************************************************************/
  template <typename L, typename Y>
  DecisionTree<L, Y>::DecisionTree(const LabelC& labelC, const Y& y1,
                                   const Y& y2) {
    if (labelC.second != 2) throw std::invalid_argument(
        "DecisionTree: binary constructor called with non-binary label");
    auto a = std::make_shared<Choice>(labelC.first, 2);
    NodePtr l1(new Leaf(y1)), l2(new Leaf(y2));
    a->push_back(std::move(l1));
    a->push_back(std::move(l2));
    root_ = Choice::Unique(std::move(a));
  }
  /****************************************************************************/
  template<typename L, typename Y>
  DecisionTree<L, Y>::DecisionTree(const std::vector<LabelC>& labelCs,
      const std::vector<Y>& ys) {
    // call recursive Create
    root_ = create(labelCs.begin(), labelCs.end(), ys.begin(), ys.end());
  }

  /****************************************************************************/
  template<typename L, typename Y>
  DecisionTree<L, Y>::DecisionTree(const std::vector<LabelC>& labelCs,
      const std::string& table) {
    // Convert std::string to values of type Y
    std::vector<Y> ys;
    std::istringstream iss(table);
    copy(std::istream_iterator<Y>(iss), std::istream_iterator<Y>(),
         back_inserter(ys));

    // now call recursive Create
    root_ = create(labelCs.begin(), labelCs.end(), ys.begin(), ys.end());
  }

  /****************************************************************************/
  template<typename L, typename Y>
  template<typename Iterator> DecisionTree<L, Y>::DecisionTree(
      Iterator begin, Iterator end, const L& label) {
    root_ = compose(begin, end, label);
  }

  /****************************************************************************/
  template<typename L, typename Y>
  DecisionTree<L, Y>::DecisionTree(const L& label,
      const DecisionTree& f0, const DecisionTree& f1)  {
    const std::vector<DecisionTree> functions{f0, f1};
    root_ = compose(functions.begin(), functions.end(), label);
  }

  /****************************************************************************/
  template <typename L, typename Y>
  DecisionTree<L, Y>::DecisionTree(const Unary& op,
                                   DecisionTree&& other) noexcept
      : root_(std::move(other.root_)) {
    // Apply the unary operation directly to each leaf in the tree
    if (root_) {
      // Define a helper function to traverse and apply the operation
      struct ApplyUnary {
        const Unary& op;
        void operator()(typename DecisionTree<L, Y>::NodePtr& node) const {
          if (node->isLeaf()) {
            // Apply the unary operation to the leaf's constant value
            auto leaf = std::static_pointer_cast<Leaf>(node);
            leaf->constant_ = op(leaf->constant_);
          } else {
            // Recurse into the choice branches
            auto choice = std::static_pointer_cast<Choice>(node);
            for (NodePtr& branch : choice->branches()) {
              (*this)(branch);
            }
          }
        }
      };

      ApplyUnary applyUnary{op};
      applyUnary(root_);
    }
    // Reset the other tree's root to nullptr to avoid dangling references
    other.root_ = nullptr;
  }

  /****************************************************************************/
  template <typename L, typename Y>
  template <typename X, typename Func>
  DecisionTree<L, Y>::DecisionTree(const DecisionTree<L, X>& other,
                                   Func Y_of_X) {
    root_ = convertFrom<X>(other.root_, Y_of_X);
  }

  /****************************************************************************/
  template <typename L, typename Y>
  template <typename M, typename X, typename Func>
  DecisionTree<L, Y>::DecisionTree(const DecisionTree<M, X>& other,
                                   const std::map<M, L>& map, Func Y_of_X) {
    auto L_of_M = [&map](const M& label) -> L { return map.at(label); };
    root_ = convertFrom<M, X>(other.root_, L_of_M, Y_of_X);
  }

  /****************************************************************************/
  // Called by two constructors above.
  // Takes a label and a corresponding range of decision trees, and creates a
  // new decision tree. However, the order of the labels needs to be respected,
  // so we cannot just create a root Choice node on the label: if the label is
  // not the highest label, we need a complicated/ expensive recursive call.
  template <typename L, typename Y>
  template <typename Iterator>
  typename DecisionTree<L, Y>::NodePtr DecisionTree<L, Y>::compose(
      Iterator begin, Iterator end, const L& label) {
    // find highest label among branches
    std::optional<L> highestLabel;
    size_t nrChoices = 0;
    for (Iterator it = begin; it != end; it++) {
      if (it->root_->isLeaf())
        continue;
      auto c = std::static_pointer_cast<const Choice>(it->root_);
      if (!highestLabel || c->label() > *highestLabel) {
        highestLabel = c->label();
        nrChoices = c->nrChoices();
      }
    }

    // if label is already in correct order, just put together a choice on label
    if (!nrChoices || !highestLabel || label > *highestLabel) {
      auto choiceOnLabel = std::make_shared<Choice>(label, end - begin);
      for (Iterator it = begin; it != end; it++) {
        NodePtr root = it->root_;
        choiceOnLabel->push_back(std::move(root));
      }
      // If no reordering, no need to call Choice::Unique
      return choiceOnLabel;
    } else {
      // Set up a new choice on the highest label
      auto choiceOnHighestLabel =
          std::make_shared<Choice>(*highestLabel, nrChoices);
      // now, for all possible values of highestLabel
      for (size_t index = 0; index < nrChoices; index++) {
        // make a new set of functions for composing by iterating over the given
        // functions, and selecting the appropriate branch.
        std::vector<DecisionTree> functions;
        for (Iterator it = begin; it != end; it++) {
          // by restricting the input functions to value i for labelBelow
          DecisionTree chosen = it->choose(*highestLabel, index);
          functions.push_back(chosen);
        }
        // We then recurse, for all values of the highest label
        NodePtr fi = compose(functions.begin(), functions.end(), label);
        choiceOnHighestLabel->push_back(std::move(fi));
      }
      return choiceOnHighestLabel;
    }
  }

  /****************************************************************************/
  // "build" is a bit of a complicated thing, but very useful.
  // It takes a range of labels and a corresponding range of values,
  // and builds a decision tree, as follows:
  // - if there is only one label, creates a choice node with values in leaves
  // - otherwise, it evenly splits up the range of values and creates a tree for
  //   each sub-range, and assigns that tree to first label's choices
  // Example:
  // build([B A],[1 2 3 4]) would call
  //   build([A],[1 2])
  //   build([A],[3 4])
  // and produce
  // B=0
  //  A=0: 1
  //  A=1: 2
  // B=1
  //  A=0: 3
  //  A=1: 4
  // Note, through the magic of "compose", create([A B],[1 3 2 4]) will produce
  // exactly the same tree as above: the highest label is always the root.
  // However, it will be *way* faster if labels are given highest to lowest.
  template<typename L, typename Y>
  template<typename It, typename ValueIt>
  typename DecisionTree<L, Y>::NodePtr DecisionTree<L, Y>::build(
      It begin, It end, ValueIt beginY, ValueIt endY) {
    // get crucial counts
    size_t nrChoices = begin->second;
    size_t size = endY - beginY;

    // Find the next key to work on
    It labelC = begin + 1;
    if (labelC == end) {
      // Base case: only one key left
      // Create a simple choice node with values as leaves.
      if (size != nrChoices) {
        std::cout << "Trying to create DD on " << begin->first << std::endl;
        std::cout << "DecisionTree::create: expected " << nrChoices
                  << " values but got " << size << " instead" << std::endl;
        throw std::invalid_argument("DecisionTree::create invalid argument");
      }
      auto choice = std::make_shared<Choice>(begin->first, endY - beginY);
      for (ValueIt y = beginY; y != endY; y++) {
        choice->push_back(NodePtr(new Leaf(*y)));
      }
      return choice;
    }

    // Recursive case: perform "Shannon expansion"
    // Creates one tree (i.e.,function) for each choice of current key
    // by calling create recursively, and then puts them all together.
    std::vector<DecisionTree> functions;
    functions.reserve(nrChoices);
    size_t split = size / nrChoices;
    for (size_t i = 0; i < nrChoices; i++, beginY += split) {
      NodePtr f = build<It, ValueIt>(labelC, end, beginY, beginY + split);
      functions.emplace_back(f);
    }
    return compose(functions.begin(), functions.end(), begin->first);
  }

  /****************************************************************************/
  // Top-level factory method, which takes a range of labels and a corresponding
  // range of values, and creates a decision tree.
  template<typename L, typename Y>
  template<typename It, typename ValueIt>
  typename DecisionTree<L, Y>::NodePtr DecisionTree<L, Y>::create(
      It begin, It end, ValueIt beginY, ValueIt endY) {
    auto node = build(begin, end, beginY, endY);
    return Choice::Unique(node);
  }

  /****************************************************************************/
  template <typename L, typename Y>
  template <typename X>
  typename DecisionTree<L, Y>::NodePtr DecisionTree<L, Y>::convertFrom(
      const typename DecisionTree<L, X>::NodePtr& f,
      std::function<Y(const X&)> Y_of_X) {
    using LXLeaf = typename DecisionTree<L, X>::Leaf;
    using LXChoice = typename DecisionTree<L, X>::Choice;

    // If leaf, apply unary conversion "op" and create a unique leaf.
    if (f->isLeaf()) {
      auto leaf = std::static_pointer_cast<LXLeaf>(f);
      return NodePtr(new Leaf(Y_of_X(leaf->constant())));
    }

    // Now a Choice!
    auto choice = std::static_pointer_cast<const LXChoice>(f);

    // Create a new Choice node with the same label
    auto newChoice = std::make_shared<Choice>(choice->label(), choice->nrChoices());

    // Convert each branch recursively
    for (auto&& branch : choice->branches()) {
      newChoice->push_back(convertFrom<X>(branch, Y_of_X));
    }

    return Choice::Unique(newChoice);
  }

  /****************************************************************************/
  template <typename L, typename Y>
  template <typename M, typename X>
  typename DecisionTree<L, Y>::NodePtr DecisionTree<L, Y>::convertFrom(
      const typename DecisionTree<M, X>::NodePtr& f,
      std::function<L(const M&)> L_of_M, std::function<Y(const X&)> Y_of_X) {
    using LY = DecisionTree<L, Y>;
    using MXLeaf = typename DecisionTree<M, X>::Leaf;
    using MXChoice = typename DecisionTree<M, X>::Choice;

    // If leaf, apply unary conversion "op" and create a unique leaf.
    if (f->isLeaf()) {
      auto leaf = std::static_pointer_cast<const MXLeaf>(f);
      return NodePtr(new Leaf(Y_of_X(leaf->constant())));
    }

    // Now is Choice!
    auto choice = std::static_pointer_cast<const MXChoice>(f);

    // get new label
    const M oldLabel = choice->label();
    const L newLabel = L_of_M(oldLabel);

    // Shannon expansion in this context involves:
    // 1. Creating separate subtrees (functions) for each possible value of the new label.
    // 2. Combining these subtrees using the 'compose' method, which implements the expansion.
    // This approach guarantees that the resulting tree maintains the correct variable ordering
    // based on the new labels (L) after translation from the old labels (M).
    // Simply creating a Choice node here would not work because it wouldn't account for the
    // potentially new ordering of variables resulting from the label translation,
    // which is crucial for maintaining consistency and efficiency in the converted tree.
    std::vector<LY> functions;
    for (auto&& branch : choice->branches()) {
      functions.emplace_back(convertFrom<M, X>(branch, L_of_M, Y_of_X));
    }
    return Choice::Unique(
        LY::compose(functions.begin(), functions.end(), newLabel));
  }

  /****************************************************************************/
  /**
   * Functor performing depth-first visit to each leaf with the leaf value as
   * the argument.
   *
   * NOTE: We differentiate between leaves and assignments. Concretely, a 3
   * binary variable tree will have 2^3=8 assignments, but based on pruning, it
   * can have less than 8 leaves. For example, if a tree has all assignment
   * values as 1, then pruning will cause the tree to have only 1 leaf yet 8
   * assignments.
   */
  template <typename L, typename Y>
  struct Visit {
    using F = std::function<void(const Y&)>;
    explicit Visit(F f) : f(f) {}  ///< Construct from folding function.
    F f;                           ///< folding function object.

    /// Do a depth-first visit on the tree rooted at node.
    void operator()(const typename DecisionTree<L, Y>::NodePtr& node) const {
      using Leaf = typename DecisionTree<L, Y>::Leaf;
      using Choice = typename DecisionTree<L, Y>::Choice;

      if (node->isLeaf()) {
        auto leaf = std::static_pointer_cast<const Leaf>(node);
        return f(leaf->constant());
      }

      auto choice = std::static_pointer_cast<const Choice>(node);
      for (auto&& branch : choice->branches()) (*this)(branch);  // recurse!
    }
  };

  template <typename L, typename Y>
  template <typename Func>
  void DecisionTree<L, Y>::visit(Func f) const {
    Visit<L, Y> visit(f);
    visit(root_);
  }

  /****************************************************************************/
  /**
   * Functor performing depth-first visit to each leaf with the Leaf object
   * passed as an argument.
   *
   * NOTE: We differentiate between leaves and assignments. Concretely, a 3
   * binary variable tree will have 2^3=8 assignments, but based on pruning, it
   * can have <8 leaves. For example, if a tree has all assignment values as 1,
   * then pruning will cause the tree to have only 1 leaf yet 8 assignments.
   */
  template <typename L, typename Y>
  struct VisitLeaf {
    using F = std::function<void(const typename DecisionTree<L, Y>::Leaf&)>;
    explicit VisitLeaf(F f) : f(f) {}  ///< Construct from folding function.
    F f;                           ///< folding function object.

    /// Do a depth-first visit on the tree rooted at node.
    void operator()(const typename DecisionTree<L, Y>::NodePtr& node) const {
      using Leaf = typename DecisionTree<L, Y>::Leaf;
      using Choice = typename DecisionTree<L, Y>::Choice;

      if (node->isLeaf()) {
        auto leaf = std::static_pointer_cast<const Leaf>(node);
        return f(*leaf);
      }

      auto choice = std::static_pointer_cast<const Choice>(node);
      for (auto&& branch : choice->branches()) (*this)(branch);  // recurse!
    }
  };

  template <typename L, typename Y>
  template <typename Func>
  void DecisionTree<L, Y>::visitLeaf(Func f) const {
    VisitLeaf<L, Y> visit(f);
    visit(root_);
  }

  /****************************************************************************/
  /**
   * Functor performing depth-first visit to each leaf with the leaf's
   * `Assignment<L>` and value passed as arguments.
   *
   * NOTE: Follows the same pruning semantics as `visit`.
   */
  template <typename L, typename Y>
  struct VisitWith {
    using F = std::function<void(const Assignment<L>&, const Y&)>;
    explicit VisitWith(F f) : f(f) {}  ///< Construct from folding function.
    Assignment<L> assignment;  ///< Assignment, mutating through recursion.
    F f;                       ///< folding function object.

    /// Do a depth-first visit on the tree rooted at node.
    void operator()(const typename DecisionTree<L, Y>::NodePtr& node) {
      using Leaf = typename DecisionTree<L, Y>::Leaf;
      using Choice = typename DecisionTree<L, Y>::Choice;

      if (node->isLeaf()) {
        auto leaf = std::static_pointer_cast<const Leaf>(node);
        return f(assignment, leaf->constant());
      }



      auto choice = std::static_pointer_cast<const Choice>(node);
      for (size_t i = 0; i < choice->nrChoices(); i++) {
        assignment[choice->label()] = i;  // Set assignment for label to i

        (*this)(choice->branches()[i]);  // recurse!

        // Remove the choice so we are backtracking
        auto choice_it = assignment.find(choice->label());
        assignment.erase(choice_it);
      }
    }
  };

  template <typename L, typename Y>
  template <typename Func>
  void DecisionTree<L, Y>::visitWith(Func f) const {
    VisitWith<L, Y> visit(f);
    visit(root_);
  }

  /****************************************************************************/
  template <typename L, typename Y>
  size_t DecisionTree<L, Y>::nrLeaves() const {
    size_t total = 0;
    visit([&total](const Y& node) { total += 1; });
    return total;
  }

  /****************************************************************************/
  // fold is just done with a visit
  template <typename L, typename Y>
  template <typename Func, typename X>
  X DecisionTree<L, Y>::fold(Func f, X x0) const {
    visit([&](const Y& y) { x0 = f(y, x0); });
    return x0;
  }

  /****************************************************************************/
  /**
   * Get (partial) labels by performing a visit.
   *
   * This method performs a depth-first search to go to every leaf and records
   * the keys assignment which leads to that leaf. Since the tree can be pruned,
   * there might be a leaf at a lower depth which results in a partial
   * assignment (i.e. not all keys are specified).
   *
   * E.g. given a tree with 3 keys, there may be a branch where the 3rd key has
   * the same values for all the leaves. This leads to the branch being pruned
   * so we get a leaf which is arrived at by just the first 2 keys and their
   * assignments.
   */
  template <typename L, typename Y>
  std::set<L> DecisionTree<L, Y>::labels() const {
    std::set<L> unique;
    auto f = [&](const Assignment<L>& assignment, const Y&) {
      for (auto&& kv : assignment) {
        unique.insert(kv.first);
      }
    };
    visitWith(f);
    return unique;
  }

/****************************************************************************/
  template <typename L, typename Y>
  bool DecisionTree<L, Y>::equals(const DecisionTree& other,
                                  const CompareFunc& compare) const {
    return root_->equals(*other.root_, compare);
  }

  template <typename L, typename Y>
  void DecisionTree<L, Y>::print(const std::string& s,
                                 const LabelFormatter& labelFormatter,
                                 const ValueFormatter& valueFormatter) const {
    root_->print(s, labelFormatter, valueFormatter);
  }

  template<typename L, typename Y>
  bool DecisionTree<L, Y>::operator==(const DecisionTree& other) const {
    return root_->equals(*other.root_);
  }

  /****************************************************************************/
  template<typename L, typename Y>
  const Y& DecisionTree<L, Y>::operator()(const Assignment<L>& x) const {
    if (root_ == nullptr)
      throw std::invalid_argument(
          "DecisionTree::operator() called on empty tree");
    return root_->operator ()(x);
  }

  /****************************************************************************/
  template<typename L, typename Y>
  DecisionTree<L, Y> DecisionTree<L, Y>::apply(const Unary& op) const {
    // It is unclear what should happen if tree is empty:
    if (empty()) {
      throw std::runtime_error(
          "DecisionTree::apply(unary op) undefined for empty tree.");
    }
    return DecisionTree(root_->apply(op));
  }

  /****************************************************************************/
  /// Apply unary operator with assignment
  template <typename L, typename Y>
  DecisionTree<L, Y> DecisionTree<L, Y>::apply(
      const UnaryAssignment& op) const {
    // It is unclear what should happen if tree is empty:
    if (empty()) {
      throw std::runtime_error(
          "DecisionTree::apply(unary op) undefined for empty tree.");
    }
    Assignment<L> assignment;
    return DecisionTree(root_->apply(op, assignment));
  }

  /****************************************************************************/
  template<typename L, typename Y>
  DecisionTree<L, Y> DecisionTree<L, Y>::apply(const DecisionTree& g,
      const Binary& op) const {
    // It is unclear what should happen if either tree is empty:
    if (empty() || g.empty()) {
      throw std::runtime_error(
          "DecisionTree::apply(binary op) undefined for empty trees.");
    }
    // apply the operaton on the root of both diagrams
    NodePtr h = root_->apply_f_op_g(*g.root_, op);
    // create a new class with the resulting root "h"
    DecisionTree result(h);
    return result;
  }

  /****************************************************************************/
  // The way this works:
  // We have an ADT, picture it as a tree.
  // At a certain depth, we have a branch on "label".
  // The function "choose(label,index)" will return a tree of one less depth,
  // where there is no more branch on "label": only the subtree under that
  // branch point corresponding to the value "index" is left instead.
  // The function below get all these smaller trees and "ops" them together.
  // This implements marginalization in Darwiche09book, pg 330
  template<typename L, typename Y>
  DecisionTree<L, Y> DecisionTree<L, Y>::combine(const L& label,
      size_t cardinality, const Binary& op) const {
    DecisionTree result = choose(label, 0);
    for (size_t index = 1; index < cardinality; index++) {
      DecisionTree chosen = choose(label, index);
      result = result.apply(chosen, op);
    }
    return result;
  }

  /****************************************************************************/
  template <typename L, typename Y>
  void DecisionTree<L, Y>::dot(std::ostream& os,
                               const LabelFormatter& labelFormatter,
                               const ValueFormatter& valueFormatter,
                               bool showZero) const {
    os << "digraph G {\n";
    root_->dot(os, labelFormatter, valueFormatter, showZero);
    os << " [ordering=out]}" << std::endl;
  }

  template <typename L, typename Y>
  void DecisionTree<L, Y>::dot(const std::string& name,
                               const LabelFormatter& labelFormatter,
                               const ValueFormatter& valueFormatter,
                               bool showZero) const {
    std::ofstream os((name + ".dot").c_str());
    dot(os, labelFormatter, valueFormatter, showZero);
    int result =
        system(("dot -Tpdf " + name + ".dot -o " + name + ".pdf >& /dev/null")
                   .c_str());
    if (result == -1)
      throw std::runtime_error("DecisionTree::dot system call failed");
  }

  template <typename L, typename Y>
  std::string DecisionTree<L, Y>::dot(const LabelFormatter& labelFormatter,
                                      const ValueFormatter& valueFormatter,
                                      bool showZero) const {
    std::stringstream ss;
    dot(ss, labelFormatter, valueFormatter, showZero);
    return ss.str();
  }

  /******************************************************************************/
  template <typename L, typename Y>
  template <typename A, typename B>
  std::pair<DecisionTree<L, A>, DecisionTree<L, B>> DecisionTree<L, Y>::split(
      std::function<std::pair<A, B>(const Y&)> AB_of_Y) const {
    using AB = std::pair<A, B>;
    const DecisionTree<L, AB> ab(*this, AB_of_Y);
    const DecisionTree<L, A> a(ab, [](const AB& p) { return p.first; });
    const DecisionTree<L, B> b(ab, [](const AB& p) { return p.second; });
    return {a, b};
  }

  /******************************************************************************/

  }  // namespace gtsam
