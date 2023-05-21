#pragma once

#define IS_STEP 0x46

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/P.h"
#include <unordered_map>
#include <string>

namespace gremlinxx {

    class GraphTraversal;

    class IsStep: public TraversalStep {
        private:
            P predicate = P(P::Comparison::EQ, boost::any());

        public:
            IsStep(P predicate);

            inline P getPredicate() { return this->predicate; }

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);
            
            using TraversalStep::getInfo;
            virtual std::string getInfo();
    };

}