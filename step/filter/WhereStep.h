#pragma once

#define WHERE_STEP 0x45

#include "step/TraversalStep.h"
#include "traversal/P.h"
#include "traversal/Traverser.h"
#include <unordered_map>
#include <string>
#include <boost/any.hpp>

class GraphTraversal;

class WhereStep: public TraversalStep {
    private:
        std::string label;
        P predicate = P(P::Comparison::EQ, boost::any());

    public:
        WhereStep(std::string label, P predicate);

        inline std::string getLabel() { return this->label; }
        inline P getPredicate() { return this->predicate; }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);
};


