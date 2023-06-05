#pragma once

#define ORDER_STEP 0x47

#include <string>
#include <boost/any.hpp>

#include "step/TraversalStep.h"
#include "traversal/GraphTraversal.h"
#include "traversal/Traverser.h"
#include "step/modulate/ByModulating.h"

namespace gremlinxx {
    
    // In the future this may get optimized away for most traversals by moving
    // the barrier to the left of the step and testing each element upon appearance
    class OrderStep: public TraversalStep, virtual public ByModulating {
        private:
            GraphTraversal* order_traversal = nullptr; // TODO make this do something

        public:
            // This is a barrier step
            OrderStep();

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            virtual std::string getInfo();

            virtual void modulate_by(boost::any arg);
    };

}