#pragma once

#define INJECT_STEP 0x74

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include <vector>
#include <boost/any.hpp>

namespace gremlinxx {

class GraphTraversal;

    class InjectStep : public TraversalStep {
        private:
            std::vector<boost::any> objects;
            
        public:
            InjectStep(std::vector<boost::any>& injects);

            InjectStep(boost::any& b);

            virtual void apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers);
    };

}